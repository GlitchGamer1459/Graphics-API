#shader vertex
#version 330 core

layout(location = 0) in vec4 rPosition;

void main() {

    gl_Position = rPosition;

};

#shader fragment
#version 330 core

layout(location = 0) out vec4 DQColor;

uniform vec4 u_DQColor;

void main() {

    DQColor = u_DQColor;

};