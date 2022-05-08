#pragma once

#include <iostream>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

#include "../src/vendor/stb_image/stb_image.h"

class Texture
{
public:
    Texture();
    Texture(const std::string &path);
    virtual ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    inline int get_width() const {return m_Width;}
    inline int get_height() const {return m_Height;}
private:
    unsigned int m_ID;
    std::string m_Filepath;
    unsigned char *m_LocalBuffer; // Local storage for our texture
    int m_Width, m_Height;
    int m_BPP; // Bits per pixel
};