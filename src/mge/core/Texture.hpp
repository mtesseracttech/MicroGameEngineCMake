#ifndef TEXTURE_H
#define TEXTURE_H

#include <map>
#include <string>
#include <GL/glew.h>

class Texture
{
protected:
    //OpenGL id for texture buffer
    GLuint m_id;

    //all previously loaded meshes;
    static std::map<std::string, Texture*> m_textures;

public:
    static Texture* load(std::string p_texturePath);

    virtual ~Texture();

    GLuint getId();

protected:
    static Texture* loadFromFile(std::string p_texturePath);

    Texture();

};

#endif // TEXTURE_H
