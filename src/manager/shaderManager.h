#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <map>
#include <string>

#include "GL/glew.h"

class ShaderManager {
public: 
  ShaderManager();
  void LoadAllShaders();
  GLuint getShader(std::string shader);

private:
  std::map<std::string, GLuint> _SHADERS;
  void updateShaderWithMixins(std::string& shaderString);
  std::string readFile(const char *filePath);

  GLuint LoadShader(const char *vertex_path, const char *fragment_path);
};

#endif