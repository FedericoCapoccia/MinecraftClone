//shader vertex
#version 330

layout (location = 0) in vec3 positions;
layout (location = 1) in vec3 colors;
out vec3 ourColor;

void main()
{
    gl_Position = vec4(positions, 1.0);
    ourColor = colors;
}

//shader fragment
#version 330 core

layout (location = 0) out vec4 color;
in vec3 ourColor;

void main()
{
    color = vec4(ourColor, 1.0f);
}
