
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#define  GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "error.h"
#include "oglTools.h"



int main(int argc, char *argv[]) {
  float videoSize_px2[2] = {800, 600}; // pixels
  
  SDL_Window   *window    = NULL;
  SDL_GLContext GlContext = NULL;
  SDL_Init(SDL_INIT_VIDEO);_sdlec
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  window = SDL_CreateWindow(
    "GlPersistentMapTest",     //const char* title,
    SDL_WINDOWPOS_UNDEFINED,   //int         x,
    SDL_WINDOWPOS_UNDEFINED,   //int         y,
    videoSize_px2[0],          //int         w,
    videoSize_px2[1],          //int         h,
    SDL_WINDOW_OPENGL          //Uint32      flags
  );_sdlec
  GlContext = SDL_GL_CreateContext(window);_sdlec
  SDL_GL_SetSwapInterval(1);_sdlec
  
  glewExperimental = GL_TRUE;
  {
    GLenum r = glewInit();
    if (r != GLEW_OK) {
      printf("GLEW error: %s\n", glewGetErrorString(r));
      exit(1);
    }
    // There's an OpenGL error 1280 here for some reason, just flush it...
    while (glGetError() != GL_NO_ERROR) {};
  }
  printf("OpenGL version: %s\n\n", glGetString(GL_VERSION));_glec
  
  
  int curFrame = 0;
  bool running = true;
  
	while (running) {
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT: running = false; break;
      }
    }
    
    
    
    SDL_GL_SwapWindow(window);_sdlec
    curFrame++;
  }
  
  return 0;
}
