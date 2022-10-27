#shader vertex
#version 330 core

layout(location = 0) in vec4 rPosition;

uniform mat4 u_rMVP;

void main() {

    gl_Position = u_rMVP * rPosition;

};

#shader fragment
#version 330 core

layout(location = 0) out vec4 rColor;

uniform vec4 u_rColor;

void main() {

    rColor = u_rColor;

};