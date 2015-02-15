/*
 * Yet another attempt at a rendering engine
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
/* Using the GLUT library for the base windowing setup */
#include <GL/freeglut.h>


GLuint scr_width = 800;
GLuint scr_height = 600;

//program is a handle for all sorts of information? (logs, shaders, etc.)
GLuint program;

int init_resources()
{

  GLint link_ok = GL_FALSE;

  program = glCreateProgram();

  GLuint vertex_shader, fragment_shader;

  vertex_shader = createShader("shader.v.glsl", GL_VERTEX_SHADER);
  glAttachShader(program, vertex_shader);

  fragment_shader = createShader("shader.f.glsl", GL_FRAGMENT_SHADER);
  glAttachShader(program, fragment_shader);

  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if(!link_ok){
    fprintf(stderr, "Error! glLinkProgram:");
    printLog(program);
    return 0;
  }

  /*TODO: bind uniforms for matricies*/

  return 1;
}

//Idle, just redisplay
void onIdle()
{
  glutPostRedisplay();
}

//Resize, change perspective
void onReshape(int width_new, int height_new)
{
  scr_width = width_new;
  scr_height = height_new;
  glViewport(0, 0, scr_width, scr_height);
}

void freeResources()
{
  glDeleteProgram(program);
}


void onDisplay()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glUseProgram(program);

  /*TODO: rendering*/

  glutSwapBuffers();

}

int main(int argc, char *argv[])
{

  glutInit(&argc,argv);
  glutInitContextVersion(2,0);
  glutInitDisplayMode(GLUT_RGBA|GLUT_ALPHA|GLUT_DOUBLE|GLUT_DEPTH);
  glutInitWindowSize(scr_width, scr_height);
  glutCreateWindow("RenderEngine 4");

  GLenum glew_status = glewInit();
  if(glew_status != GLEW_OK){
    fprintf(stderr, "glewInit(): error: %s\n", glewGetErrorString(glew_status));
    return 1;
  }

  if(!GLEW_VERSION_2_0) {
    fprintf(stderr, "Error: your graphic card does not support OpenGL 2.0\n");
    return 1;
  }

  //initialize resources
  if(!init_resources())
    return 1;

  glutDisplayFunc(onDisplay);
  glutReshapeFunc(onReshape);
  glutIdleFunc(onIdle);
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glutMainLoop();

  freeResources();
  return 0;
}
