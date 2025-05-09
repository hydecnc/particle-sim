#version 320 es
layout(location = 0) in float aRadius;
layout(location = 1) in vec2 aPos;
layout(location = 2) in vec4 aColor;

out vec4 color;

void main() {
    gl_Position = vec4(aPos.xy, 0.0f, 1.0f);
    gl_PointSize = aRadius;
    color = aColor;
}
