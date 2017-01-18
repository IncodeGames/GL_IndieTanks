#version 130

in vec3 vertexPosition;
in vec4 vertexColor;

in vec2 texCoord;
in vec3 normal;

out vec3 fragmentPosition;
out vec4 fragmentColor;

out vec2 texCoord0;
out vec3 normal0;

uniform mat4 mvpMatrix;
uniform mat4 Normal;

void main()
{
    gl_Position = mvpMatrix * vec4(vertexPosition, 1.0f);
    
    fragmentPosition = vertexPosition;
    
    fragmentColor = vertexColor;
    
    texCoord0 = texCoord;
    normal0 = (Normal * vec4(normal, 0.0f)).xyz;
}