#include "mge/core/Mesh.hpp"
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <utility>

Mesh::Mesh(std::string p_id)
        : m_id(std::move(p_id)), m_indexBufferId(0), m_vertexBufferId(0), m_normalBufferId(0), m_uvBufferId(0),
          m_vertices(), m_normals(), m_uvs(), m_indices()
{
    //ctor
}

Mesh::~Mesh()
{
    //dtor
}

/**
 * Load reads the obj data into a new mesh using C++ combined with c style coding.
 * The result is an indexed mesh for use with glDrawElements.
 * Expects a obj file with following layout v/vt/vn/f eg
 *
 * For example the obj file for a simple plane describes two triangles, based on
 * four vertices, with 4 uv's all having the same vertex normals (NOT FACE NORMALS!)
 *
 * v 10.000000 0.000000 10.000000              //vertex 1
 * v -10.000000 0.000000 10.000000             //vertex 2
 * v 10.000000 0.000000 -10.000000             //vertex 3
 * v -10.000000 0.000000 -10.000000            //vertex 4
 * vt 0.000000 0.000000                        //uv 1
 * vt 1.000000 0.000000                        //uv 2
 * vt 1.000000 1.000000                        //uv 3
 * vt 0.000000 1.000000                        //uv 4
 * vn 0.000000 1.000000 -0.000000              //normal 1 (normal for each vertex is same)
 * s off
 *
 * Using these vertices, uvs and normals we can construct faces, made up of 3 triplets (vertex, uv, normal)
 * f 2/1/1 1/2/1 3/3/1                         //face 1 (triangle 1)
 * f 4/4/1 2/1/1 3/3/1                         //face 2 (triangle 2)
 *
 * So although this is a good format for blender and other tools reading .obj files, this is
 * not an index mechanism that OpenGL supports out of the box.
 * The reason is that OpenGL supports only one indexbuffer, and the value at a certain point in the indexbuffer, eg 3
 * refers to all three other buffers (v, vt, vn) at once,
 * eg if index[0] = 5, opengl will stream vertexBuffer[5], uvBuffer[5], normalBuffer[5] into the shader.
 *
 * So what we have to do after reading the file with all vertices, is construct unique indexes for
 * all pairs that are described by the faces in the object file, eg if you have
 * f 2/1/1 1/2/1 3/3/1                         //face 1 (triangle 1)
 * f 4/4/1 2/1/1 3/3/1                         //face 2 (triangle 2)
 *
 * v/vt/vn[0] will represent 2/1/1
 * v/vt/vn[1] will represent 1/2/1
 * v/vt/vn[2] will represent 3/3/1
 * v/vt/vn[3] will represent 4/4/1
 *
 * and that are all unique pairs, after which our index buffer can contain:
 *
 * 0,1,2,3,0,2
 *
 * So the basic process is, read ALL data into separate arrays, then use the faces to
 * create unique entries in a new set of arrays and create the indexbuffer to go along with it.
 *
 * Note that loading this mesh isn't cached like we do with texturing, this is an exercise left for the students.
 */
Mesh* Mesh::load(std::string p_filename)
{
    std::cout << "Loading " << p_filename << "...";

    Mesh* mesh = new Mesh(p_filename);

    std::ifstream file(p_filename, std::ios::in);

    if (file.is_open())
    {
        //these three vectors will contains data as taken from the obj file
        //in the order it is encountered in the object file
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uvs;

        //in addition we create a map to store the triplets found under the f(aces) section in the
        //object file and map them to an index for our index buffer (just number them sequentially
        //as we encounter them and store references to the pack
        std::map<FaceIndexTriplet, unsigned int> mappedTriplets;

        std::string line; // to store each line in
        while (getline(file, line))
        {

            // c-type string to store cmd read from obj file (cmd is v, vt, vn, f)
            char cmd[10];
            cmd[0] = 0;

            //get the first string in the line of max 10 chars (c-style)
            sscanf(line.c_str(), "%10s", cmd);

            //note that although the if statements below seem to imply that we can
            //read these different line types (eg vertex, normal, uv) in any order,
            //this is just convenience coding for us (instead of multiple while loops)
            //we assume the obj file to list ALL v lines first, then ALL vt lines,
            //then ALL vn lines and last but not least ALL f lines last

            //so... start processing lines
            //are we reading a vertex line? straightforward copy into local vertices vector
            if (strcmp(cmd, "v") == 0)
            {
                glm::vec3 vertex;
                sscanf(line.c_str(), "%10s %f %f %f ", cmd, &vertex.x, &vertex.y, &vertex.z);
                vertices.push_back(vertex);

                //or are we reading a normal line? straightforward copy into local normal vector
            }
            else if (strcmp(cmd, "vn") == 0)
            {
                glm::vec3 normal;
                sscanf(line.c_str(), "%10s %f %f %f ", cmd, &normal.x, &normal.y, &normal.z);
                normals.push_back(normal);

                //or are we reading a uv line? straightforward copy into local uv vector
            }
            else if (strcmp(cmd, "vt") == 0)
            {
                glm::vec2 uv;
                sscanf(line.c_str(), "%10s %f %f ", cmd, &uv.x, &uv.y);
                uvs.push_back(uv);

                //this is where it gets nasty. After having read all vertices, normals and uvs into
                //their own buffer
            }
            else if (strcmp(cmd, "f") == 0)
            {

                //an f lines looks like
                //f 2/1/1 1/2/1 3/3/1
                //in other words
                //f v1/u1/n1 v2/u2/n2 v3/u3/n3
                //for each triplet like that we need to check whether we already encountered it
                //and update our administration based on that
                glm::ivec3 vertexIndex;
                glm::ivec3 normalIndex;
                glm::ivec3 uvIndex;
                int        count = sscanf(line.c_str(), "%10s %d/%d/%d %d/%d/%d %d/%d/%d", cmd, &vertexIndex[0],
                                          &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                          &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

                //Have we read exactly 10 elements?
                if (count == 10)
                {

                    //process 3 triplets, one for each vertex (which is first element of the triplet)
                    for (int i = 0; i < 3; ++i)
                    {
                        //create key out of the triplet and check if we already encountered this before
                        FaceIndexTriplet triplet(
                                static_cast<unsigned int>(vertexIndex[i]),
                                static_cast<unsigned int>(uvIndex[i]),
                                static_cast<unsigned int>(normalIndex[i]));

                        auto found = mappedTriplets.find(triplet);

                        //if iterator points at the end, we haven't found it
                        if (found == mappedTriplets.end())
                        {
                            //so create a new index value, and map our triplet to it
                            unsigned int index = static_cast<unsigned int>(mappedTriplets.size());
                            mappedTriplets[triplet] = index;

                            //now record this index
                            mesh->m_indices.push_back(index);
                            //and store the corresponding vertex/normal/uv values into our own buffers
                            //note the -1 is required since all values in the f triplets in the .obj file
                            //are 1 based, but our vectors are 0 based
                            mesh->m_vertices.push_back(vertices[vertexIndex[i] - 1]);
                            mesh->m_normals.push_back(normals[normalIndex[i] - 1]);
                            mesh->m_uvs.push_back(uvs[uvIndex[i] - 1]);
                        }
                        else
                        {
                            //if the key was already present, get the index value for it
                            unsigned int index = found->second;
                            //and update our index buffer with it
                            mesh->m_indices.push_back(index);
                        }
                    }
                }
                else
                {
                    //If we read a different amount, something is wrong
                    std::cout << "Error reading obj, needing v,vn,vt" << std::endl;
                    delete mesh;
                    return nullptr;
                }
            }

        }

        file.close();
        mesh->buffer();

        std::cout << "Mesh loaded and buffered:" << (mesh->m_indices.size() / 3.0f) << " triangles." << std::endl;
        return mesh;
    }
    else
    {
        std::cout << "Could not read " << p_filename << std::endl;
        delete mesh;
        return nullptr;
    }
}

void Mesh::buffer()
{
    glGenBuffers(1, &m_indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_normalBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalBufferId);
    glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3), &m_normals[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_uvBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_uvBufferId);
    glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(glm::vec2), &m_uvs[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::streamToOpenGL(GLint p_verticesAttrib, GLint p_normalsAttrib, GLint p_uvsAttrib)
{
    if (p_verticesAttrib != -1)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
        glEnableVertexAttribArray(static_cast<GLuint>(p_verticesAttrib));
        glVertexAttribPointer(static_cast<GLuint>(p_verticesAttrib), 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

    if (p_normalsAttrib != -1)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_normalBufferId);
        glEnableVertexAttribArray(static_cast<GLuint>(p_normalsAttrib));
        glVertexAttribPointer(static_cast<GLuint>(p_normalsAttrib), 3, GL_FLOAT, GL_TRUE, 0, 0);
    }

    if (p_uvsAttrib != -1)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_uvBufferId);
        glEnableVertexAttribArray(static_cast<GLuint>(p_uvsAttrib));
        glVertexAttribPointer(static_cast<GLuint>(p_uvsAttrib), 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, (GLvoid*) 0);

    // no current buffer, to avoid mishaps, very important for performance

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //fix for serious performance issue
    if (p_uvsAttrib != -1) glDisableVertexAttribArray(static_cast<GLuint>(p_uvsAttrib));
    if (p_normalsAttrib != -1) glDisableVertexAttribArray(static_cast<GLuint>(p_normalsAttrib));
    if (p_verticesAttrib != -1) glDisableVertexAttribArray(static_cast<GLuint>(p_verticesAttrib));
}

void
Mesh::drawDebugInfo(const glm::mat4& p_modelMatrix, const glm::mat4& p_viewMatrix, const glm::mat4& p_projectionMatrix)
{
    //demo of how to render some debug info using the good ol' direct rendering mode...
    glUseProgram(0);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(p_projectionMatrix));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(p_viewMatrix * p_modelMatrix));

    glBegin(GL_LINES);
    //for each index draw the normal starting at the corresponding vertex
    for (unsigned int index : m_indices)
    {
        //draw normal for vertex
        glm::vec3 normal = m_normals[index];
        glColor3fv(glm::value_ptr(normal));
        glm::vec3 normalStart = m_vertices[index];
        glVertex3fv(glm::value_ptr(normalStart));
        glm::vec3 normalEnd = normalStart + normal * 0.2f;
        glVertex3fv(glm::value_ptr(normalEnd));
    }
    glEnd();
}