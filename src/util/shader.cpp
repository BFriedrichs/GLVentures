// http://www.nexcius.net/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c/

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "shader.h"

std::string readFile(const char *filePath) {
  std::string content;
  std::ifstream fileStream(filePath, std::ios::in);

  if(!fileStream.is_open()) {
      std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
      return "";
  }

  std::string line = "";
  while(!fileStream.eof()) {
      std::getline(fileStream, line);
      content.append(line + "\n");
  }

  fileStream.close();
  return content;
}

#define SHADER_VERSION "#version 400"

void updateShaderWithMixins(std::string& shaderString, std::vector<std::string> mixins) {
  std::string mixinShader = SHADER_VERSION "\n";

  //load main shader
  std::string mainShader = readFile("assets/shader files/main.frag");  

  for(auto const& mixin: mixins) {
    std::string path = "assets/shader files/mixins/" + mixin + ".frag";
    std::string currMixin = readFile(path.c_str());

    mixinShader += currMixin;
  }

  shaderString = mixinShader + shaderString + mainShader;
}

GLuint LoadShader(const char *vertex_path, const char *fragment_path, std::vector<std::string> mixins) {
  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  GLuint fragShader2 = glCreateShader(GL_FRAGMENT_SHADER);

  // Read shaders
  std::string vertShaderStr = readFile(vertex_path);
  std::string fragShaderStr = readFile(fragment_path);

  updateShaderWithMixins(fragShaderStr, mixins);

  const char *vertShaderSrc = vertShaderStr.c_str();
  const char *fragShaderSrc = fragShaderStr.c_str();

  GLint result = GL_FALSE;
  int logLength;

  // Compile vertex shader
  glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
  glCompileShader(vertShader);

  // Check vertex shader
  glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
  glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
  if(logLength > 1)
    std::cout << &vertShaderError[0] << std::endl;

  // Compile fragment shader
  glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
  glCompileShader(fragShader);

  // Check fragment shader
  glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
  glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
  if(logLength > 1)
    std::cout << &fragShaderError[0] << std::endl;

  GLuint program = glCreateProgram();
  glAttachShader(program, vertShader);
  glAttachShader(program, fragShader);
  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &result);
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<char> programError( (logLength > 1) ? logLength : 1 );
  glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
  if(logLength > 1)
    std::cout << &programError[0] << std::endl;

  glDeleteShader(vertShader);
  glDeleteShader(fragShader);

  return program;
}