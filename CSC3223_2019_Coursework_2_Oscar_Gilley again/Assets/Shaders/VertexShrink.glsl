#version 400 core

uniform mat4 modelMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 projMatrix = mat4(1.0f);

uniform float time = 0.0f;

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec2 texCoord;
out Vertex
{
	vec4 colour;
	mat4 mvp;
	vec3 worldPos;
	vec2 texCoord;
	vec3 normal;
} OUT;

void main(void)
{

	
	mat4 mvp = (projMatrix * viewMatrix * modelMatrix);

	gl_Position = mvp * vec4(position + vec3(0, 0, 0), 1.0);

	if (time > 1) {
		gl_Position = mvp * vec4(position + vec3(0, 0, 0), time * time / 1);
	}

	if (time > 8) {
		gl_Position = mvp * vec4(position + vec3(0, 0, 0), 0);
	}
	

	//gl_Position = mvp * vec4(position + vec3())

	
	

	OUT.texCoord = texCoord;
	OUT.colour = colour;
}