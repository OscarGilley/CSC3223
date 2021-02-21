#version 400 core

uniform sampler2D mainTex;
uniform sampler2D secondTex;

uniform float time;

in Vertex{
	smooth vec4 colour;
	smooth vec2 texCoord;
} IN;

out vec4 fragColor;

void main(void) {
	

	vec4 normTex = texture2D(mainTex, IN.texCoord);

	float timeFrac = 1 - (time / 1.5);

	fragColor = mix(vec4(0, 0, 0, 0), normTex, timeFrac);

	
}