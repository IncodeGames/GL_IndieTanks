#version 130

in vec3 vertexPosition;
in vec4 vertexColor;

out vec3 fragmentPosition;
out vec4 fragmentColor;

uniform mat4 mvpMatrix;

void main()
{
    gl_Position = vec4(vertexPosition, 1.0f) * mvpMatrix;
    
    fragmentPosition = vertexPosition;
    
    fragmentColor = vertexColor;
}