#version 400 core

uniform sampler2D mainTex;
uniform sampler2D secondTex;

uniform float time;

in Vertex{
	smooth vec4 colour;
	smooth vec2 texCoord;
	mat4 mvp;
} IN;

out vec4 fragColor;

void main(void) {
	

	vec4 normTex = texture2D(mainTex, IN.texCoord);

	float timeFrac = time;
	float timeFade = 1 - (time / 15);

	if (time < 1){
		fragColor = mix(vec4(0, 0, 0, 0), normTex, timeFrac);
	}

	if (time >= 1){
		fragColor = mix(vec4(0, 0, 0, 0), normTex, timeFade);
	}

	
	
}