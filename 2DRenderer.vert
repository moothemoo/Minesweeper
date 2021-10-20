#version 330 core

layout (location = 0) in vec4 aTexPos;

out vec2 TexCoord;

uniform mat4 camera;
uniform mat4 model;

void main()
{
    gl_Position = camera * model * vec4(aTexPos.x, aTexPos.y, 0.0, 1.0f);
    TexCoord = vec2(aTexPos.z, aTexPos.w);
}
