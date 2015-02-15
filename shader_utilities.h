#ifndef _SHADER_UTILS_H
#define _SHADER_UTILS_H
#include <GL/glew.h>
char *fileRead(const char *filename);
void printLog(GLuint object);
GLuint createShader(const char *filename, GLenum type);
#endif
