#type vertex
#version 330
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

out vec2 TexCoord;

void main()
{
    TexCoord = aUV;
    gl_Position = vec4(aPos.xy, 0.0, 1.0);
}

#type fragment
#version 330

uniform sampler2D gTexture;
out vec4 FragColour;

in vec2 TexCoord;

void main()
{
    FragColour = vec4(texture(gTexture, TexCoord).rgb, 1.0);
}