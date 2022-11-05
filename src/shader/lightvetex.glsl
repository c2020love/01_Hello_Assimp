#version 330 core
    layout (location = 0) in vec3 aPoos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 project;

void main()
{
    gl_Position = project * view * model * vec4(aPoos , 1.0f);
}