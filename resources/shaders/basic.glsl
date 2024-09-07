//shader vertex
#version 330

layout (location = 0) in vec3 positions;
layout (location = 1) in vec3 colors;
layout (location = 2) in vec2 texture_coordinates;

out vec3 ourColor;
out vec2 ourTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(positions, 1.0f);
    ourColor = colors;
    ourTexCoord = texture_coordinates;
}

//shader fragment
#version 330 core
out vec4 color;

in vec3 ourColor;
in vec2 ourTexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    color = mix(texture(texture1, ourTexCoord), texture(texture2, ourTexCoord), 0.2);
}
