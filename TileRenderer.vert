#version 330 core

layout (location = 0) in vec4 aTexPos;

out vec2 TexCoord;

uniform mat4 camera;

void main()
{
    gl_Position = camera * vec4(aTexPos.x, aTexPos.y, 0.0, 1.0f);
    TexCoord = vec2(aTexPos.z, aTexPos.w);
}