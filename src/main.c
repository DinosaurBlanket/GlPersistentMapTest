
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#define  GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "error.h"
#include "oglTools.h"


typedef struct {
  float   x;
  float   y;
  float   z;
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t o;
} vert;



int main(int argc, char *argv[]) {
  
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
    720,                       //int         w,
    720,                       //int         h,
    SDL_WINDOW_OPENGL          //Uint32      flags
  );_sdlec
  GlContext = SDL_GL_CreateContext(window);_sdlec
  SDL_GL_SetSwapInterval(ENABLE_VSYNC);_sdlec
  
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
  
  
  
  GLuint vao;
  glGenVertexArrays(1, &vao);_glec
  glBindVertexArray(vao);_glec
  glClearColor(0,0,0,0);
  
  GLuint vbo;
  uint32_t triArrayW = 32;
  uint32_t triArrayH = 32;
  uint32_t triCount  = triArrayW * triArrayH;
  uint32_t vertCount = triCount * 3;
  uint32_t vboSize   = vertCount * sizeof(vert);
  glGenBuffers(1, &vbo);_glec
  glBindBuffer(GL_ARRAY_BUFFER, vbo);_glec
  GLbitfield bufferStorageFlags = 
    GL_MAP_WRITE_BIT      | 
    GL_MAP_PERSISTENT_BIT | 
    GL_MAP_COHERENT_BIT
  ;
  glBufferStorage(
    GL_ARRAY_BUFFER,    // GLenum        target
    vboSize,            // GLsizeiptr    size​
    0,                  // const GLvoid *data​
    bufferStorageFlags  // GLbitfield    flags​
  );_glec
  vert *triData = glMapBufferRange(
    GL_ARRAY_BUFFER,    // GLenum     target​
    0,                  // GLintptr   offset​
    vboSize,            // GLsizeiptr length​
    bufferStorageFlags  // GLbitfield access
  );_glec
  
  
  
  GLuint shaderProgram = createShaderProgram(
    "src/vert.glsl", 
    "src/frag.glsl", 
    "shaderProgram"
  );
  if (!shaderProgram) return __LINE__;
  glUseProgram(shaderProgram);_glec
  
  GLint attr_pos   = glGetAttribLocation(shaderProgram, "pos"  );_glec
  GLint attr_color = glGetAttribLocation(shaderProgram, "color");_glec
  glEnableVertexAttribArray(attr_pos  );_glec
  glEnableVertexAttribArray(attr_color);_glec
  glVertexAttribPointer(
    attr_pos,   3, GL_FLOAT,         GL_FALSE, 16, (const GLvoid*)  0
  );_glec
  glVertexAttribPointer(
    attr_color, 4, GL_UNSIGNED_BYTE, GL_TRUE,  16, (const GLvoid*) 12
  );_glec
  
  
  
  
  int curFrame = 0;
  bool running = true;
  while (running) {
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT: running = false; break;
      }
    }
    
    for (uint32_t i = 0; i < vertCount; i += 3) {
      triData[i].x =  0.0;
      triData[i].y =  0.5;
      triData[i].z =  0.0;
      triData[i].r = 0xFF;
      triData[i].g = 0x00;
      triData[i].b = 0x00;
      triData[i].o = 0xFF;
      
      triData[i+1].x =  0.3;
      triData[i+1].y = -0.2;
      triData[i+1].z =  0.0;
      triData[i+1].r = 0x00;
      triData[i+1].g = 0xFF;
      triData[i+1].b = 0x00;
      triData[i+1].o = 0xFF;
      
      triData[i+2].x = -0.3;
      triData[i+2].y = -0.2;
      triData[i+2].z =  0.0;
      triData[i+2].r = 0x00;
      triData[i+2].g = 0x00;
      triData[i+2].b = 0xFF;
      triData[i+2].o = 0xFF;
    }
    
    glDrawArrays(GL_TRIANGLES, 0, vertCount);_glec
    
    SDL_GL_SwapWindow(window);_sdlec
    glClear(GL_COLOR_BUFFER_BIT);_glec
    curFrame++;
  }
	
	SDL_GL_DeleteContext(GlContext);_sdlec
	SDL_Quit();_sdlec
  return 0;
}
