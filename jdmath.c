#include "jdmath.h"
#include <stdlib.h>
#include <string.h>

static const double PI = 3.14159265358979323846;

//subtract vec4s
jd_vec4 jd_sub_vec4( jd_vec4 a, jd_vec4 b){
  jd_vec4 out;

  out.m[0] = a.m[0] - b.m[0];
  out.m[1] = a.m[1] - b.m[1];
  out.m[2] = a.m[2] - b.m[2];

  return out;

}

//subtract vec3s
jd_vec3 jd_sub_vec3( jd_vec3 a, jd_vec3 b){
  jd_vec3 out;

  out.m[0] = a.m[0] - b.m[0];
  out.m[1] = a.m[1] - b.m[1];
  out.m[2] = a.m[2] - b.m[2];

  return out;
}

//Multiplies two 4x4 matrices 
jd_matrix jd_mult_mat4(jd_matrix* m1, jd_matrix* m2) {
  jd_matrix out = IDENTITY_MATRIX;
  unsigned int row, column, row_offset;

  for (row = 0, row_offset = row * 4; row < 4; ++row, row_offset = row * 4)
    for (column = 0; column < 4; ++column)
      out.m[row_offset + column] =
	(m1->m[row_offset + 0] * m2->m[column + 0]) +
	(m1->m[row_offset + 1] * m2->m[column + 4]) +
	(m1->m[row_offset + 2] * m2->m[column + 8]) +
	(m1->m[row_offset + 3] * m2->m[column + 12]);

  return out;
}

//Normalizes a vec4
void jd_normalize_vec4(jd_vec4* v) {
  float sqr = v->m[0] * v->m[0] + v->m[1] * v->m[1] + v->m[2] * v->m[2];
  if(sqr == 1 || sqr == 0)
    return;
  float invrt = 1.f/sqrt(sqr);
  v->m[0] *= invrt;
  v->m[1] *= invrt;
  v->m[2] *= invrt;
}

//Normalizes a vec3
void jd_normalize_vec3(jd_vec3* v) {
  float sqr = v->m[0] * v->m[0] + v->m[1] * v->m[1] + v->m[2] * v->m[2];
  if(sqr == 1 || sqr == 0)
    return;
  float invrt = 1.f/sqrt(sqr);
  v->m[0] *= invrt;
  v->m[1] *= invrt;
  v->m[2] *= invrt;
}

//Does dot product on two vec4s 
float jd_dot_vec4(jd_vec4 v1, jd_vec4 v2) {
  return v1.m[0] * v2.m[0] + v1.m[1] * v2.m[1] + v1.m[2] * v2.m[2] + v1.m[3] * v2.m[3];
}

//Does cross product on two vec4s
jd_vec4 jd_cross_vec4(jd_vec4 v1, jd_vec4 v2) {
  jd_vec4 out = {{0}};
  out.m[0] = v1.m[1]*v2.m[2] - v1.m[2]*v2.m[1];
  out.m[1] = v1.m[2]*v2.m[0] - v1.m[0]*v2.m[2];
  out.m[2] = v1.m[0]*v2.m[1] - v1.m[1]*v2.m[0];
  return out;
}

//Does dot product on two vec3s 
float jd_dot_vec3(jd_vec3 v1, jd_vec3 v2) {
  return v1.m[0] * v2.m[0] + v1.m[1] * v2.m[1] + v1.m[2] * v2.m[2];
}

//Does cross product on two vec3s
jd_vec3 jd_cross_vec3(jd_vec3 v1, jd_vec3 v2) {
  jd_vec3 out = {{0}};
  out.m[0] = v1.m[1]*v2.m[2] - v1.m[2]*v2.m[1];
  out.m[1] = v1.m[2]*v2.m[0] - v1.m[0]*v2.m[2];
  out.m[2] = v1.m[0]*v2.m[1] - v1.m[1]*v2.m[0];
  return out;
}

//Scales a matrix
void jd_scale(jd_matrix* m, float x, float y, float z) {
  jd_matrix scale = IDENTITY_MATRIX;
  jd_matrix temp_matrix;

  scale.m[0] = x;
  scale.m[5] = y;
  scale.m[10] = z;

  temp_matrix = jd_mult_mat4(m, &scale);
  memcpy(m->m, temp_matrix.m, sizeof(m->m));
}


//Translates a matrix
void jd_translate(jd_matrix* m, float x, float y, float z) {
  jd_matrix translation = IDENTITY_MATRIX;
  jd_matrix temp_matrix;

  translation.m[12] = x;
  translation.m[13] = y;
  translation.m[14] = z;

  temp_matrix = jd_mult_mat4(m, &translation);
  memcpy(m->m, translation.m, sizeof(m->m));
}


void jd_rotateX(jd_matrix* m, float angle) {
  jd_matrix rotation = IDENTITY_MATRIX;
  jd_matrix temp_matrix;
  float sine = (float)sin(angle);
  float cosine = (float)cos(angle);

  rotation.m[5] = cosine;
  rotation.m[6] = -sine;
  rotation.m[9] = sine;
  rotation.m[10] = cosine;

  temp_matrix = jd_mult_mat4(m, &rotation);
  memcpy(m->m, temp_matrix.m, sizeof(m->m));
}
void jd_rotateY(jd_matrix* m, float angle) {
  jd_matrix rotation = IDENTITY_MATRIX;
  jd_matrix temp_matrix;
  float sine = (float)sin(angle);
  float cosine = (float)cos(angle);

  rotation.m[0] = cosine;
  rotation.m[8] = sine;
  rotation.m[2] = -sine;
  rotation.m[10] = cosine;

  temp_matrix = jd_mult_mat4(m, &rotation);
  memcpy(m->m, temp_matrix.m, sizeof(m->m));
}
void jd_rotateZ(jd_matrix* m, float angle) {
  jd_matrix rotation = IDENTITY_MATRIX;
  jd_matrix temp_matrix;
  float sine = (float)sin(angle);
  float cosine = (float)cos(angle);

  rotation.m[0] = cosine;
  rotation.m[1] = -sine;
  rotation.m[4] = sine;

  rotation.m[5] = cosine;

  temp_matrix = jd_mult_mat4(m, &rotation);
  memcpy(m->m, temp_matrix.m, sizeof(m->m));
}

jd_matrix jd_look_at(jd_vec4 pos, jd_vec4 dir) {
  jd_vec4 f = dir;
  jd_normalize_vec4(&f);
  jd_vec4 u = {{0, 1, 0, 0}};
  jd_vec4 s = jd_cross_vec4(f, u);
  jd_normalize_vec4(&s);
  u = jd_cross_vec4(s, f);

  jd_matrix out = IDENTITY_MATRIX;
  out.m[0] = s.x;
  out.m[4] = s.y;
  out.m[8] = s.z;

  out.m[1] = u.x;
  out.m[5] = u.y;
  out.m[9] = u.z;

  out.m[2] = -f.x;
  out.m[6] = -f.y;
  out.m[10] = -f.z;

  out.m[12] = -jd_dot_vec4(s, pos);
  out.m[13] = -jd_dot_vec4(u, pos);
  out.m[14] =  jd_dot_vec4(f, pos);
  return out;
}

jd_matrix jd_perspective(float fovy, float aspect_ratio, float near_plane, float far_plane) {
	jd_matrix out = { { 0 } };

	const float
		y_scale = (float)(1/cos(fovy * PI / 360)),
		x_scale = y_scale / aspect_ratio,
		frustum_length = far_plane - near_plane;

	out.m[0] = x_scale;
	out.m[5] = y_scale;
	out.m[10] = -((far_plane + near_plane) / frustum_length);
	out.m[11] = -1;
	out.m[14] = -((2 * near_plane * far_plane) / frustum_length);

	return out;
}

jd_matrix jd_fpcamera(jd_vec4 eye, float pitch, float yaw){
  float cos_pitch = cos(pitch);
  float sin_pitch = sin(pitch);
  float cos_yaw = cos(yaw);
  float sin_yaw = sin(yaw);
  jd_vec4 xaxis = {cos_yaw, 0, -sin_yaw, 0.0};
  jd_vec4 yaxis = {(sin_yaw * sin_pitch), cos_pitch, (cos_yaw * sin_pitch), 0.0};  
  jd_vec4 zaxis = {(sin_yaw * cos_pitch), -sin_pitch, (cos_pitch * cos_yaw), 0.0};

  jd_matrix out = {{
    xaxis.x, yaxis.x, zaxis.x, 0,
    xaxis.y, yaxis.y, zaxis.y, 0,
    xaxis.z, yaxis.z, zaxis.z, 0,
    -jd_dot_vec4(xaxis, eye), -jd_dot_vec4(yaxis, eye), -jd_dot_vec4(zaxis, eye), 1}};

  return out;
    
}
