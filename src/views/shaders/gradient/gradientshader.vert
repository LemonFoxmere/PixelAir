#version 440
layout(location = 0) in vec4 qt_Vertex;
layout(location = 1) in vec2 qt_TexCoord0;
layout(set = 0, binding = 0) uniform UniformBlock {
    mat4 qt_ModelViewProjectionMatrix;
};

layout(location = 0) out vec2 fragPosition;

void main(void)
{
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
    fragPosition = qt_TexCoord0.xy;
}
