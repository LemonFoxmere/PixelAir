#version 440
layout(location = 0) in vec2 fragPosition;
layout(location = 0) out vec4 fragColor;

vec2 v0 = vec2(0.0, 0.0);
vec2 v1 = vec2(1.0, 0.0);
vec2 v2 = vec2(0.0, 1.0);

void main(void)
{
    float t = (v1.y - v2.y) * (v0.x - v2.x) + (v2.x - v1.x) * (v0.y - v2.y);
    float b0 = ((v1.y - v2.y) * (fragPosition.x - v2.x) + (v2.x - v1.x) * (fragPosition.y - v2.y)) / t;
    float b1 = ((v2.y - v0.y) * (fragPosition.x - v2.x) + (v0.x - v2.x) * (fragPosition.y - v2.y)) / t;
    float b2 = 1.0 - b0 - b1;

    float m0 = (b0 > 0.5) ? 1 : (cos(2 * 3.1415 * b0) / -2 + 0.5);
    float m1 = (b1 > 0.5) ? 1 : (cos(2 * 3.1415 * b1) / -2 + 0.5);
    float m2 = (b2 > 0.5) ? 1 : (cos(2 * 3.1415 * b2) / -2 + 0.5);

    vec4 r = vec4(1.0, 0.0, 0.0, 1.0);
    vec4 g = vec4(0.0, 1.0, 0.0, 1.0);
    vec4 b = vec4(0.0, 0.0, 1.0, 1.0);

    fragColor = m0 * r + m1 * g + m2 * b;
}
