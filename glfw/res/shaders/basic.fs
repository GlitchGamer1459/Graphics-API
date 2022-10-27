#shader vertex
#version 330 core

layout(location = 0) in vec4 bPosition;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_bMVP;

void main() {

   gl_Position = u_bMVP * bPosition;
   v_TexCoord = texCoord;

};

#shader fragment
#version 330 core

layout(location = 0) out vec4 bColor;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main() {

   vec4 texColor = texture(u_Texture, v_TexCoord);
   bColor = texColor;

};