#version 320 es

precision mediump float;

in vec4 color;
out vec4 FragColor;

vec2 tile(in vec2 _st, in float _zoom) {
  _st *= _zoom;
  return fract(_st);
}

float box(in vec2 _st, in vec2 _size){
    _size = vec2(0.5) - _size*0.5;
    vec2 uv = smoothstep(_size,
                        _size+vec2(0.001),
                        _st);
    uv *= smoothstep(_size,
                    _size+vec2(0.001),
                    vec2(1.0)-_st);
    return uv.x*uv.y;
}

void main() {
    // Convert point coord to center origin (-1 to +1)
    vec2 coord = gl_PointCoord * 2.0 - 1.0;
    vec2 st = tile(gl_PointCoord, 1.0);

    float r = dot(coord, coord);

    float result = box(st, vec2(0.75, 0.25));
    result += box(st, vec2(0.25, 0.75));

    float alpha = smoothstep(1.0, 0.98, r);

    FragColor = vec4(result * color.rgb, alpha * color.a);
}
