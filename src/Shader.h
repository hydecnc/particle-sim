#pragma once
#include <glad/glad.h>
#include <string_view>

class Shader {
private:
  void checkCompileErrors(GLuint shader, std::string_view type) const;

public:
  GLuint programId{};
  Shader() = default;
  Shader(std::string_view vertexPath, std::string_view fragmentPath);
  void use() const;

  void setFloat(const char *name, float value) const;
};
