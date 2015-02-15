/* read and compile shaders */

#include <stdio.h>
#include <stdlib.h>
/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
/* Using the GLUT library for the base windowing setup */
#include <GL/freeglut.h>

/** read the whole file */
char* fileRead(const char *filename)
{
  FILE* input = fopen(filename, "rb");
  if(!input)
    return NULL;

  //Get the total size of the file 
  if(fseek(input, 0, SEEK_END == -1))
    return NULL;
  size_t size = (size_t)ftell(input);  
  if(size == -1)
    return NULL;
  if(fseek(input, 0, SEEK_SET) == -1)
    return NULL;

  char *content = (char*)malloc(size+1);
  if(!content)
    return NULL;

  fread(content, 1, size, input);
  if(ferror(input)){
    free(content);
    return NULL;
  }

  fclose(input);
  content[size] = '\0';
  return content;
}



/**Display shader compile errors */
void printLog(GLuint object)
{
  GLint log_length =0;
  if(glIsShader(object))
    glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
  else if(glIsProgram(object))
    glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
  else {
    fprintf(stderr, "printLog: Not a shader or program\n");
    return;
  }

  char *log = (char*)malloc(log_length);

  if(glIsShader(object))
    glGetShaderInfoLog(object, log_length, NULL, log);
  else if (glIsProgram(object))
    glGetProgramInfoLog(object, log_length, NULL, log);

  fprintf(stderr, "%s", log);
  free(log);
}

GLuint createShader(const char *filename,  GLenum type)
{
  const GLchar *source = fileRead(filename);
  if(source == NULL){
    fprintf(stderr, "Error opening file %s: ", filename);
    perror("");
    return 0;
  }

  GLuint res = glCreateShader(type);
  glShaderSource(res, 1, &source, NULL);
  free((void*)source);

  glCompileShader(res);
  GLint compile_ok = GL_FALSE;
  glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
  if (compile_ok == GL_FALSE) {
    fprintf(stderr, "%s:", filename);
    printLog(res);
    glDeleteShader(res);
    return 0;
  }
 
  return res;
}
