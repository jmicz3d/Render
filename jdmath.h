#include <math.h>

#define JDMATH

typedef struct jd_matrix {
  float m[16];
} jd_matrix;

typedef union jd_vec4 {
  float m[4];
  struct {
    float x, y, z, w;
  };
} jd_vec4;

typedef union jd_vec3 {
  float m[3];
  struct {
    float x, y, z;
  };
} jd_vec3;

typedef union jd_vec3_short {
  float m[3];
  struct {
    unsigned short x, y, z;
  };
} jd_vec3_short;


static const jd_vec4 X_AXIS = {{1, 0, 0, 0}};
static const jd_vec4 Y_AXIS = {{0, 1, 0, 0}};
static const jd_vec4 Z_AXIS = {{0, 0, 1, 0}};
static const jd_vec4 INV_X_AXIS = {{-1, 0, 0, 0}};
static const jd_vec4 INV_Y_AXIS = {{0, -1, 0, 0}};
static const jd_vec4 INV_Z_AXIS = {{0, 0, -1, 0}};

static const jd_matrix IDENTITY_MATRIX = {{
	1, 0, 0, 0, 
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
}};

jd_vec4 jd_sub_vec4( jd_vec4 a, jd_vec4 b);
jd_matrix jd_mult_mat4(jd_matrix* m1, jd_matrix* m2);
void jd_normalize_vec4(jd_vec4* v);
float jd_dot_vec4(jd_vec4 v1, jd_vec4 v2);
jd_vec4 jd_cross_vec4(jd_vec4 v1, jd_vec4 v2);
jd_vec3 jd_sub_vec3( jd_vec3 a, jd_vec3 b);
void jd_normalize_vec3(jd_vec3* v);
float jd_dot_vec3(jd_vec3 v1, jd_vec3 v2);
jd_vec3 jd_cross_vec3(jd_vec3 v1, jd_vec3 v2);
void jd_scale(jd_matrix* m, float x, float y, float z);
void jd_translate(jd_matrix* m, float x, float y, float z);
void jd_rotateX(jd_matrix* m, float angle);
void jd_rotateY(jd_matrix* m, float angle);
void jd_rotateZ(jd_matrix* m, float angle);
jd_matrix jd_look_at(jd_vec4 pos, jd_vec4 dir);
jd_matrix jd_perspective(float fovy, float aspect_ratio, float near_plane, float far_plane);
jd_matrix jd_fpcamera(jd_vec4 eye, float pitch, float yaw);
