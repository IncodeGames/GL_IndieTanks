#version 130
//Input vertex color
in vec3 fragmentPosition;
in vec4 fragmentColor;

out vec4 color;

uniform float time;

void main()
{
    color = vec4((fragmentColor.r * cos(fragmentPosition.x + time) + 1.0) * 0.5,
                 (fragmentColor.g * cos(fragmentPosition.y + time) + 1.0) * 0.5,
                 (fragmentColor.b * cos(fragmentPosition.z * 0.5 + time) + 1.0) * 0.5, 
                 fragmentColor.a);
}