//shader vertex
#version 330

layout (location = 0) in vec3 positions;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(positions, 1.0f);
    TexCoord = aTexCoord;
}

//shader fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D Texture;

void main()
{
    FragColor = texture(Texture, TexCoord);
}
