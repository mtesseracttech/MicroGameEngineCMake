#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include "mge/core/Texture.hpp"

std::map<std::string, Texture*> Texture::_textures; // for static texturs var

Texture::Texture(): _id() {
    glGenTextures (1, &_id);
}

Texture::~Texture()
{
	glDeleteTextures(1, &_id);
}

GLuint Texture::getId() {
	return _id;
}

// importer for textures
Texture* Texture::load(std::string pName)
{
    Texture* texture = 0;

    //try to locate texture
   	std::map<std::string, Texture*>::iterator textureIterator = _textures.find(pName);

   	if (textureIterator == _textures.end()) {
        texture = _loadFromFile(pName);
        std::cout << "Texture " << pName << " with id " << texture->getId() << " loaded." << std::endl;
        std::cout << "Caching texture." << std::endl;
        _textures[pName] = texture;
    } else {
        std::cout << "Returning cached texture " << pName << std::endl;
        texture = textureIterator->second;
    }

    return texture;
}

Texture* Texture::_loadFromFile(std::string pName) {
    // load from file and store in cache
    sf::Image image;
    if (image.loadFromFile(pName))
    {
        //normal image 0,0 is top left, but opengl uv 0,0 is bottom left, so we flip the image internally
        image.flipVertically();
        //create a wrapper for the id (texture is nothing more than that) and
        //load corresponding data into opengl using this id
        Texture * texture = new Texture();
        glBindTexture (GL_TEXTURE_2D, texture->getId());
        glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        return texture;
    } else {
        return 0;
    }
}










