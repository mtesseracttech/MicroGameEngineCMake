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
		Mesh(std::string pId);
		virtual ~Mesh();

        /**
         * Loads a mesh from an .obj file. The file has to have:
         * vertexes, uvs, normals and face indexes. See load source
         * for more format information.
         */
		static Mesh* load(std::string pFileName);

        /**
         * Streams the mesh to opengl using the given indexes for the different attributes
         */
        void streamToOpenGL(GLint pVerticesAttrib, GLint pNormalsAttrib, GLint pUVsAttrib);

        /**
         * Draws debug info (normals) for the mesh using the given matrices)
         */
        void drawDebugInfo(const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix);

	protected:

	    std::string _id;

        //OpenGL id's for the different buffers created for this mesh
		GLuint _indexBufferId;
		GLuint _vertexBufferId;
		GLuint _normalBufferId;
		GLuint _uvBufferId;

	    //the actual data
		std::vector<glm::vec3> _vertices;       //vec3 with 3d coords for all vertices
		std::vector<glm::vec3> _normals;        //vec3 with 3d normal data
		std::vector<glm::vec2> _uvs;            //vec2 for uv

		//references to the vertices/normals & uvs in previous vectors
		std::vector<unsigned> _indices;

        //buffer vertices, normals, and uv's
		void _buffer();

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
		class FaceIndexTriplet {
			public:
				unsigned v; //vertex
				unsigned uv;//uv
				unsigned n; //normal
				FaceIndexTriplet( unsigned pV, unsigned pUV, unsigned pN )
				:	v(pV),uv(pUV),n(pN) {
				}
				//needed for use as key in map
				bool operator<(const FaceIndexTriplet other) const{
					return memcmp((void*)this, (void*)&other, sizeof(FaceIndexTriplet))>0;
				}
		};

};

#endif // MESH_H
