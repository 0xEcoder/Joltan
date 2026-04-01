#ifndef MATS_H
#define MATS_H

extern const char *vertSrc;
extern const char *fragOrange;

void identity(float m[16]);
void multiply(float out[16], const float a[16], const float b[16]);
void perspective(float m[16], float fovDeg, float aspect, float near, float far);
void lookAt(float m[16], float eye[3], float center[3], float up[3]);

#endif
