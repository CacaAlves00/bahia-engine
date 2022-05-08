#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

// GLM header file
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct ShaderProgramSource
{
    std::string VertexSource;   // is called 3 times per frame
    std::string FragmentSource; // is called millions of times per frame
};

class Shader
{
public:
    Shader();
    Shader(const std::string &vertexFilepath, const std::string &fragmentFilepath);
    virtual ~Shader();

    void bind() const;
    void unbind() const;

    // Set uniforms
    void set_uniform1i(const std::string &name, int value);
    void set_uniform1f(const std::string &name, float value);
    void set_uniform3f(const std::string &name, float v0, float v1, float v2);
    void set_uniform4f(const std::string &name, float v0, float v1, float v2, float v3);
    void set_uniformMat4f(const std::string &name, const glm::mat4 &matrix);

private:
    unsigned int m_ID;
    std::string m_vertexFilepath;
    std::string m_fragmentFilepath;
    std::unordered_map<std::string, int> m_uniformLocationCache;

    int get_uniform_location(const std::string &name);
    ShaderProgramSource parse_shader();
    unsigned int compile_shader(unsigned int type, const std::string &source);
    unsigned int create_shader(const std::string &vertexShader, const std::string &fragmentShader);
};