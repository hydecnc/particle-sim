#include "Shader.h"
#include <SDL3/SDL_log.h>
#include <fstream>
#include <iostream>
#include <sstream>

void Shader::checkCompileErrors(GLuint shader, std::string_view type) const {
  GLint success{};
  GLchar infoLog[1024]{};
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
      SDL_Log("ERROR::SHADER_COMPILATION_ERROR of type: %s \n %s", type.data(),
              infoLog);
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
      SDL_Log("ERROR::PROGRAM_LINKING_ERROR of type: %s \n %s", type.data(),
              infoLog);
    }
  }
}

Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath) {
  std::string vertexCode{};
  std::string fragmentCode{};

  std::ifstream vShaderFile{};
  std::ifstream fShaderFile{};

  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    vShaderFile.open(vertexPath.data());
    fShaderFile.open(fragmentPath.data());
    std::stringstream vShaderStream{}, fShaderStream{};
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  } catch (std::ifstream::failure &e) {
    SDL_Log("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: %s", e.what());
  }

  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();

  unsigned int vertex{}, fragment{};
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, nullptr);
  glCompileShader(vertex);
  checkCompileErrors(vertex, "VERTEX");

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, nullptr);
  glCompileShader(fragment);
  checkCompileErrors(fragment, "FRAGMENT");

  programId = glCreateProgram();
  glAttachShader(programId, vertex);
  glAttachShader(programId, fragment);
  glLinkProgram(programId);
  checkCompileErrors(programId, "PROGRAM");

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::use() const { glUseProgram(programId); }

void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}
