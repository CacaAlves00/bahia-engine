#include "../include/Shader.h"

Shader::Shader()
{
}

Shader::Shader(const std::string &vertexFilepath, const std::string &fragmentFilepath)
    : m_vertexFilepath(vertexFilepath), m_fragmentFilepath(fragmentFilepath), m_ID(0)
{
    ShaderProgramSource source = parse_shader();
    m_ID = create_shader(source.VertexSource, source.FragmentSource);
}
Shader::~Shader()
{
    glDeleteProgram(m_ID);
}

ShaderProgramSource Shader::parse_shader()
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(m_vertexFilepath);
        fShaderFile.open(m_fragmentFilepath);
        std::stringstream vShaderStream, fShaderStream;
        // read file’s buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    // ShaderProgramSource s = { ss[0].str(), ss[1].str()};
    return {vertexCode, fragmentCode};
}

unsigned int Shader::compile_shader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();

    // The id of the shader (id), how many strings we're passing as source code (1),
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error handling
    int success;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(id, 512, NULL, infoLog);

        std::cout << "Failed to compile shader\n";
        std::cout << infoLog << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::create_shader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragmentShader);

    // Attaching shaders to OpenGL
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    int success;
    char infoLog[512];
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::bind() const
{
    glUseProgram(m_ID);
}
void Shader::unbind() const
{
    glUseProgram(0);
}

void Shader::set_uniform1i(const std::string &name, int value)
{
    glUniform1i(get_uniform_location(name), value);
}

void Shader::set_uniform3f(const std::string &name, float v0, float v1, float v2)
{
    glUniform3f(get_uniform_location(name), v0, v1, v2);
}

void Shader::set_uniform4f(const std::string &name, float v0, float v1, float v2, float v3)
{
    glUniform4f(get_uniform_location(name), v0, v1, v2, v3);
}

void Shader::set_uniform1f(const std::string &name, float value)
{
    glUniform1f(get_uniform_location(name), value);
}

void Shader::set_uniformMat4f(const std::string &name, const glm::mat4 &matrix)
{
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::get_uniform_location(const std::string &name)
{
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];

    int location = glGetUniformLocation(m_ID, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist!\n";

    m_uniformLocationCache[name] = location;

    return location;
}