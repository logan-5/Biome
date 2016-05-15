#ifdef GL_ES
precision mediump float;
#endif

float  iGlobalTime = CC_Time[1];
varying vec2 v_texCoord;
varying vec4 v_fragmentColor;
uniform sampler2D u_texture;
uniform vec3 u_fogColor;
uniform float u_distanceFactor;
uniform float u_fogThickness;

void main() {
    vec4 color = texture2D(u_texture, v_texCoord); // get the base texture color
    vec3 foggedColor = mix( color.rgb, u_fogColor, u_distanceFactor*u_fogThickness ); // mix the texture with the fog color, with a factor of the fog thickness and distance from camera
    foggedColor *= color.a; // premultiply alpha, so the transparent parts of the sprite stay transparent
    
    gl_FragColor = vec4(foggedColor, color.a); // use the alpha channel from the original texture
}