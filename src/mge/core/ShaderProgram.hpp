#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <vector>
#include <string>
using namespace std;
#include <GL/glew.h>

/**
 * Generic shader program to which you can add separate shaders.
 * Nice exercise for the reader: make it possible to add shaders by passing in the code as a string instead of through a file.
 *
 * Usage:
 *  create shader program
 *  add shaders
 *  finalize shader program
 *  use shader program
 */
class ShaderProgram
{
    public:
		ShaderProgram();
		virtual ~ShaderProgram();

        //add a specific shader
		void addShader(GLuint pShaderType, const string& pShaderPath);
		//link and compile all added shaders
		void finalize();
		//tell opengl this is now the current shader
		void use();

        //get access to uniforms of the shader
		GLuint getUniformLocation (const string& pName);
		//get access to attributes of the shader
		GLuint getAttribLocation (const string& pName);

	private:
	    GLint _programId;

	    vector<GLuint> _shaderIds;

		string _readFile(const string &pShaderPath);
		GLuint _compileShader (GLuint pShaderType, const string &pShaderSource);
};

#endif // SHADERPROGRAM_H

