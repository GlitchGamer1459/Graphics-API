#shader vertex
#version 330 core

layout(location = 0) in vec4 rPosition;
layout(location = 1) in vec4 inColor;

out vec4 v_Color;

void main() {

    gl_Position = rPosition;
    v_Color = inColor;

};

#shader fragment
#version 330 core

layout(location = 0) out vec4 DQColor;

in vec4 v_Color;

uniform vec4 u_DQColor;

void main() {

    DQColor = v_Color;

};