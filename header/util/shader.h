#ifndef SHADER_H
#define SHADER_H

#include "GL/glew.h"

GLuint LoadShader(const char *vertex_path, const char *fragment_path, std::vector<std::string> requiredAttributes);

#endif