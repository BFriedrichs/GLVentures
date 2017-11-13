
#include <iostream>

#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <GLFW/glfw3.h>
#include <png.h>

#include <string> 
#include <vector>

#include "applicationStore.h"

#include "text.h"
#include "game.h"

const double maxFPS = 60.0;
const double maxPeriod = 1.0 / maxFPS;
double lastTime = 0.0;

double frameTime = glfwGetTime();
int frames = 0;
Text* fpsFactory(int fps);

ApplicationStore* _STORE = ApplicationStore::getInstance();
Game* g;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  g->keyUpdate(window, key, scancode, action, mods);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
  g->cursorUpdate(window, xpos, ypos);
}

int main(int argc, char* argv[]) {

  if (!glfwInit()) {
    fprintf (stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 
  
  // Open a window and create its OpenGL context
  GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
  window = glfwCreateWindow(_STORE->windowWidth, _STORE->windowHeight, "Test", NULL, NULL);
  if( window == NULL ){
      fprintf( stderr, "Failed to open GLFW window.\n" );
      glfwTerminate();
      return -1;
  }

  glfwMakeContextCurrent(window); // Initialize GLEW
  glewExperimental = GL_TRUE; // Needed in core profile
  if (glewInit() != GLEW_OK) {
      fprintf(stderr, "Failed to initialize GLEW\n");
      return -1;
  }

  glClearColor(0.4f, 0.4f, 0.4f, 0.0f);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  g = new Game();

  glfwSetCursorPosCallback(window, cursor_position_callback);
  glfwSetKeyCallback(window, key_callback);

  /*
  image->generatePNGBuffer(&rowed);

  png_structp png_ptr;
  png_infop info_ptr;
  const char* file_name = "test.png";
  FILE *fp = fopen(file_name, "wb");
  if (!fp)
    std::cout << "[write_png_file] File could not be opened for writing" << std::endl;


  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
          std::cout << "[write_png_file] png_create_write_struct failed" << std::endl;

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
          std::cout << "[write_png_file] png_create_info_struct failed"<< std::endl;

  if (setjmp(png_jmpbuf(png_ptr)))
  std::cout << "[write_png_file] Error during init_io"<< std::endl;

  png_init_io(png_ptr, fp);


  if (setjmp(png_jmpbuf(png_ptr)))
  std::cout << "[write_png_file] Error during writing header"<< std::endl;

  int x, y;
  png_byte color_type = PNG_COLOR_TYPE_RGB_ALPHA;
  png_byte bit_depth = 8;
  png_set_IHDR(png_ptr, info_ptr, width, height,
               bit_depth, color_type, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);


  if (setjmp(png_jmpbuf(png_ptr)))
  std::cout << "[write_png_file] Error during writing bytes"<< std::endl;

  png_write_image(png_ptr, rowed);

  if (setjmp(png_jmpbuf(png_ptr)))
  std::cout << "[write_png_file] Error during end of write"<< std::endl;

  png_write_end(png_ptr, NULL);

  fclose(fp);
  */
  
  Text* fpsCounter = fpsFactory(60);

  while(!glfwWindowShouldClose(window)) {
    double time = glfwGetTime();
    double deltaTime = time - lastTime;

    // main tick
    glfwPollEvents();
    if(deltaTime >= maxPeriod) {
      // fps
      frames++;
      if(time - frameTime >= 1.0) {
        delete fpsCounter;
        fpsCounter = fpsFactory(frames);

        frames = 0;
        frameTime = time;
      }

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
      g->update(deltaTime);
      g->render();
      fpsCounter->render();
      
      glfwSwapBuffers(window);
      lastTime = time;
    }
  }
  
  return 0;
}

Text* fpsFactory(int fps) {
  return new Text(10, 10, ("fps: " + std::to_string(frames)).c_str(), 8);
}