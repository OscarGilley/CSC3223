#version 400 core

uniform sampler2D mainTex;
uniform sampler2D secondTex;

uniform float time;

in Vertex{
	vec4 colour;
	vec2 texCoord;
	mat4 mvp;
} IN;

out vec4 fragColor;

void main(void) {

	vec4 normTex = texture2D(mainTex, IN.texCoord);
	
	fragColor = normTex;

	
	
	
	
}