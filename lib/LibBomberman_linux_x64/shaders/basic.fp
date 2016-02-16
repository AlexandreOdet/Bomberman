#version 120

uniform	mat4 projection;
uniform	mat4 view;
uniform	mat4 model;
uniform vec4 myColor;

uniform sampler2D fTexture0;

varying vec4 fColor;
varying vec4 fNormal;
varying vec2 fUv;

void main(void)
{
  vec4 texColor = texture2D(fTexture0, fUv) * fColor;
  if (texColor != vec4(0, 0, 0, 1))
     gl_FragColor = texColor;
  else
     gl_FragColor = myColor;
}
