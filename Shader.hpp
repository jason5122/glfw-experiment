#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
public:
    unsigned int id;

    Shader(const char* vertex_path, const char* fragment_path) {
        std::string vertex_code;
        std::string fragment_code;
        std::ifstream vshader_file;
        std::ifstream fshader_file;

        vshader_file.exceptions(std::ifstream::failbit |
                                std::ifstream::badbit);
        fshader_file.exceptions(std::ifstream::failbit |
                                std::ifstream::badbit);
        try {
            vshader_file.open(vertex_path);
            fshader_file.open(fragment_path);
            std::stringstream vshader_stream, fshader_stream;

            vshader_stream << vshader_file.rdbuf();
            fshader_stream << fshader_file.rdbuf();

            vshader_file.close();
            fshader_file.close();

            vertex_code = vshader_stream.str();
            fragment_code = fshader_stream.str();
        } catch (std::ifstream::failure& e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: "
                      << e.what() << std::endl;
        }
        const char* vshader_code = vertex_code.c_str();
        const char* fshader_code = fragment_code.c_str();

        unsigned int vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vshader_code, NULL);
        glCompileShader(vertex);
        check_compile_errors(vertex, "VERTEX");

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fshader_code, NULL);
        glCompileShader(fragment);
        check_compile_errors(fragment, "FRAGMENT");

        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);
        check_compile_errors(id, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void use() {
        glUseProgram(id);
    }

private:
    void check_compile_errors(unsigned int shader, std::string type) {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: "
                          << type << "\n"
                          << infoLog
                          << "\n -- "
                             "------------------------------------------------"
                             "--- -- "
                          << std::endl;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type
                          << "\n"
                          << infoLog
                          << "\n -- "
                             "------------------------------------------------"
                             "--- -- "
                          << std::endl;
            }
        }
    }
};
#endif
