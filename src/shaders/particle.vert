#version 320 es
layout(location = 0) in float aRadius;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aPos;

out vec4 color;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f);
    gl_PointSize = aRadius;
    color = aColor;
}
