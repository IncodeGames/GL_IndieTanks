#version 130
//Input vertex color
in vec3 fragmentPosition;
in vec4 fragmentColor;

in vec2 texCoord0;
in vec3 normal0;

out vec4 color;
out vec4 texture;

uniform sampler2D sampler;
uniform vec3 lightDirection;

uniform float time;

void main()
{
    color = vec4((fragmentColor.r * cos(fragmentPosition.x + time / 60) + 1.0) * 0.5,
                 (fragmentColor.g * cos(fragmentPosition.y + time / 60) + 1.0) * 0.5,
                 (fragmentColor.b * cos(fragmentPosition.z * 0.5 + time / 60) + 1.0) * 0.5, 
                 fragmentColor.a);
                 
    texture = texture2D(sampler, texCoord0) * clamp(dot(-lightDirection, normal0), 0.0, 1.0);
}