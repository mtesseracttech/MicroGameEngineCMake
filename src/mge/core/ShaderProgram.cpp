#include "mge/core/ShaderProgram.hpp"
#include <iostream>
#include <fstream>

ShaderProgram::ShaderProgram():_programId(0), _shaderIds() {
    //why does opengl use glCreateProgram and not glGenProgram (1, &_programID)? Who knows:) *shrugs*
    _programId = glCreateProgram();
    cout << endl << "Program created with id:" << _programId << endl;
}

ShaderProgram::~ShaderProgram() {}

void ShaderProgram::addShader (GLuint pShaderType, const string &pShaderPath) {
    std::string shaderCode = _readFile(pShaderPath);
    GLuint shaderId = _compileShader(pShaderType, shaderCode);

    if (shaderId != 0) {
        _shaderIds.push_back (shaderId);
    }
}

void ShaderProgram::use()
{
    glUseProgram(_programId);
}

GLuint ShaderProgram::getUniformLocation (const string& pName) {
    return glGetUniformLocation (_programId, pName.c_str());
}

GLuint ShaderProgram::getAttribLocation (const string& pName) {
    return glGetAttribLocation (_programId, pName.c_str());
}

void ShaderProgram::finalize() {
    for (size_t i = 0; i < _shaderIds.size();++i) {
        glAttachShader(_programId, _shaderIds[i]);
    }

    glLinkProgram(_programId);

    // Check the program
    GLint linkResult = GL_FALSE;
    glGetProgramiv( _programId, GL_LINK_STATUS, &linkResult);

    if ( linkResult ) {
        cout << "Program linked ok." << endl << endl;
    } else { // error, show message
        cout << "Program error:" << endl;

        int infoLogLength;
        glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* errorMessage = new char[infoLogLength+1];
        glGetProgramInfoLog(_programId,infoLogLength,NULL,errorMessage);
        cout << errorMessage << endl << endl;
        delete[] errorMessage;
    }

    for (size_t i = 0; i < _shaderIds.size();++i) {
        glDeleteShader(_shaderIds[i]);
    }
}

string ShaderProgram::_readFile(const string& pShaderPath)
{
	string contents;
	ifstream file (pShaderPath, ios::in);
	if(file.is_open()){
		cout << "Reading shader file... " << pShaderPath << endl;
		string line = "";
		while(getline(file, line)) contents += "\n" + line;
		file.close();
	} else {
		cout << "Error reading shader " << pShaderPath << endl;
		contents = "";
	}
	return contents;
}

// compile the code, and detect errors.
GLuint ShaderProgram::_compileShader(GLuint pShaderType, const string& pShaderSource)
{
	cout << "Compiling shader... " << endl;
	const char * sourcePointer = pShaderSource.c_str();
	GLuint shaderId = glCreateShader(pShaderType);
	glShaderSource(shaderId, 1, &sourcePointer, NULL );
	glCompileShader( shaderId);

	GLint compilerResult = GL_FALSE;
	glGetShaderiv( shaderId, GL_COMPILE_STATUS, &compilerResult);

	if (compilerResult) {
		cout << "Shader compiled ok." << endl;
		return shaderId;
	} else { // get error message
	    cout << "Shader error:" << endl;
		int infoLogLength;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* errorMessage = new char[ infoLogLength+1 ];
		glGetShaderInfoLog( shaderId, infoLogLength, NULL, errorMessage);
		cout << errorMessage << endl << endl;
		delete[] errorMessage;
		return 0;
	}
}
