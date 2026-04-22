#version 330 core

// Vertex inputs
layout (location = 0) in vec3 aPos;    // vertex position
layout (location = 1) in vec3 aNormal; // vertex normal

// Uniforms
uniform mat4 model;   // model matrix
uniform mat4 MVP;     // combined projection * view * model

// Outputs to fragment shader
out vec3 FragPos;
out vec3 Normal;

void main()
{
    // Transform vertex position to world space
    FragPos = vec3(model * vec4(aPos, 1.0));

    // Transform normal to world space correctly
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // Compute clip space position
    gl_Position = MVP * vec4(aPos, 1.0);
}