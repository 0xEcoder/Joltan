#include <GL/glew.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "include/camera.h"
#include "include/render.h"

// Shader sources
const char *vertSrc =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 MVP;\n"
    "void main() {\n"
    "    gl_Position = MVP * vec4(aPos, 1.0);\n"
    "}\n";

const char *fragOrange =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "    FragColor = vec4(0.5, 0.5, 0.2, 0.65);\n"
    "}\n";

// Set matrix to identity
void identity(float m[16])
{
    memset(m, 0, 16 * sizeof(float));
    m[0] = m[5] = m[10] = m[15] = 1.0f;
}

// Column-major matrix multiply: out = a * b
void multiply(float out[16], const float a[16], const float b[16])
{
    float tmp[16];
    for (int col = 0; col < 4; col++)
        for (int row = 0; row < 4; row++) {
            float sum = 0.0f;
            for (int k = 0; k < 4; k++)
                sum += a[k * 4 + row] * b[col * 4 + k];
            tmp[col * 4 + row] = sum;
        }
    memcpy(out, tmp, 16 * sizeof(float));
}

// Perspective projection (column-major)
void perspective(float m[16], float fovDeg, float aspect, float near, float far)
{
    memset(m, 0, 16 * sizeof(float));
    float f = 1.0f / tanf(fovDeg * 0.5f * (float)M_PI / 180.0f);
    m[0]  = f / aspect;
    m[5]  = f;
    m[10] = (far + near) / (near - far);
    m[11] = -1.0f;
    m[14] = (2.0f * far * near) / (near - far);
}

// LookAt view matrix (column-major)
void lookAt(float m[16], float eye[3], float center[3], float up[3])
{
    float f[3], s[3], u[3];

    // forward = normalize(center - eye)
    f[0] = center[0] - eye[0];
    f[1] = center[1] - eye[1];
    f[2] = center[2] - eye[2];
    float fn = sqrtf(f[0]*f[0] + f[1]*f[1] + f[2]*f[2]);
    f[0] /= fn; f[1] /= fn; f[2] /= fn;

    // side = normalize(forward x up)
    s[0] = f[1]*up[2] - f[2]*up[1];
    s[1] = f[2]*up[0] - f[0]*up[2];
    s[2] = f[0]*up[1] - f[1]*up[0];
    float sn = sqrtf(s[0]*s[0] + s[1]*s[1] + s[2]*s[2]);
    s[0] /= sn; s[1] /= sn; s[2] /= sn;

    // up = side x forward
    u[0] = s[1]*f[2] - s[2]*f[1];
    u[1] = s[2]*f[0] - s[0]*f[2];
    u[2] = s[0]*f[1] - s[1]*f[0];

    memset(m, 0, 16 * sizeof(float));
    // Column-major layout
    m[0]  =  s[0]; m[4]  =  s[1]; m[8]  =  s[2];
    m[1]  =  u[0]; m[5]  =  u[1]; m[9]  =  u[2];
    m[2]  = -f[0]; m[6]  = -f[1]; m[10] = -f[2];
    m[12] = -(s[0]*eye[0] + s[1]*eye[1] + s[2]*eye[2]);
    m[13] = -(u[0]*eye[0] + u[1]*eye[1] + u[2]*eye[2]);
    m[14] =  (f[0]*eye[0] + f[1]*eye[1] + f[2]*eye[2]);
    m[15] = 1.0f;
}
