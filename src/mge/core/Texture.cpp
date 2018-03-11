#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include "mge/core/Texture.hpp"

std::map<std::string, Texture*> Texture::m_textures; // for static texturs var

Texture::Texture() : m_id()
{
    glGenTextures(1, &m_id);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

GLuint Texture::getId()
{
    return m_id;
}

// importer for textures
Texture* Texture::load(std::string p_texturePath)
{
    Texture* texture = nullptr;

    //try to locate texture
    auto textureIterator = m_textures.find(p_texturePath);

    if (textureIterator == m_textures.end())
    {
        texture = loadFromFile(p_texturePath);
        std::cout << "Texture " << p_texturePath << " with id " << texture->getId() << " loaded." << std::endl;
        std::cout << "Caching texture." << std::endl;
        m_textures[p_texturePath] = texture;
    }
    else
    {
        std::cout << "Returning cached texture " << p_texturePath << std::endl;
        texture = textureIterator->second;
    }

    return texture;
}

Texture* Texture::loadFromFile(std::string p_texturePath)
{
    // load from file and store in cache
    sf::Image image;
    if (image.loadFromFile(p_texturePath))
    {
        //normal image 0,0 is top left, but opengl uv 0,0 is bottom left, so we flip the image internally
        image.flipVertically();
        //create a wrapper for the id (texture is nothing more than that) and
        //load corresponding data into opengl using this id
        auto* texture = new Texture();
        glBindTexture(GL_TEXTURE_2D, texture->getId());
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     image.getPixelsPtr());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        return texture;
    }
    else
    {
        return nullptr;
    }
}










