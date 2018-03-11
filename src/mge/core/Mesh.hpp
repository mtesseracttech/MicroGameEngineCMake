#ifndef MESH_H
#define MESH_H

#include <vector>
#include <GL/glew.h>
#include <glm.hpp>

class World;

/**
 * A mesh represents an .OBJ file. It knows how it is constructed, how its data should be buffered to OpenGL
 * and how it should be streamed to OpenGL
 */
class Mesh
{
public:
    explicit Mesh(std::string p_id);

    virtual ~Mesh();

    /**
     * Loads a mesh from an .obj file. The file has to have:
     * vertexes, uvs, normals and face indexes. See load source
     * for more format information.
     */
    static Mesh* load(std::string p_filename);

    /**
     * Streams the mesh to opengl using the given indexes for the different attributes
     */
    void streamToOpenGL(GLint p_verticesAttrib, GLint p_normalsAttrib, GLint p_uvsAttrib);

    /**
     * Draws debug info (normals) for the mesh using the given matrices)
     */
    void
    drawDebugInfo(const glm::mat4& p_modelMatrix, const glm::mat4& p_viewMatrix, const glm::mat4& p_projectionMatrix);

protected:

    std::string m_id;

    //OpenGL id's for the different buffers created for this mesh
    GLuint m_indexBufferId;
    GLuint m_vertexBufferId;
    GLuint m_normalBufferId;
    GLuint m_uvBufferId;

    //the actual data
    std::vector<glm::vec3> m_vertices;       //vec3 with 3d coords for all vertices
    std::vector<glm::vec3> m_normals;        //vec3 with 3d normal data
    std::vector<glm::vec2> m_uvs;            //vec2 for uv

    //references to the vertices/normals & uvs in previous vectors
    std::vector<unsigned> m_indices;

    //buffer vertices, normals, and uv's
    void buffer();

    //Please read the "load" function documentation on the .obj file format first.
    //FaceVertexTriplet  is a helper class for loading and converting to obj file to
    //indexed arrays.
    //If we list all the unique v/uv/vn triplets under the faces
    //section in an object file sequentially and assign them a number
    //it would be a map of FaceVertexTriplet. Each FaceVertexTriplet refers
    //to an index with the originally loaded vertex list, normal list and uv list
    //and is only used during conversion (unpacking) of the facevertextriplet list
    //to a format that OpenGL can handle.
    //So for a vertex index a FaceVertexTriplet contains the index for uv and n as well.
    struct FaceIndexTriplet
    {
        unsigned v; //vertex
        unsigned uv;//uv
        unsigned n; //normal
        FaceIndexTriplet(unsigned p_vertex, unsigned p_uv, unsigned p_normal)
                : v(p_vertex), uv(p_uv), n(p_normal)
        {
        }

        //needed for use as key in map
        bool operator<(const FaceIndexTriplet p_other) const
        {
            return memcmp((void*) this, (void*) &p_other, sizeof(FaceIndexTriplet)) > 0;
        }
    };

};

#endif // MESH_H
