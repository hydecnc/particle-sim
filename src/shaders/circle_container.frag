#version 320 es

precision mediump float;

in vec4 color;
out vec4 FragColor;

void main() {
    // Convert point coord to center origin (-1 to +1)
    vec2 coord = gl_PointCoord * 2.0 - 1.0;
    float borderSize = 0.01;
    coord /= 1.0 - borderSize;
    float r = dot(coord, coord);

    float alpha = smoothstep(1.0 -  borderSize, 1.0, r) * (1.0 - smoothstep(1.0, 1.0 + borderSize, r));

    FragColor = vec4(color.rgb, alpha * color.a);
}
