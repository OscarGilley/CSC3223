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
	vec2 texCoord;
} OUT;

void main(void)
{
	mat4 mvp = (projMatrix * viewMatrix * modelMatrix);

	float timeFrac = time / 15;

	

	//gl_Position = mvp * vec4(position + vec3(0, 0, 2), 1.0);

 	gl_Position = mvp * vec4(position + vec3(time * cos(time * time), time * sin(time * time), 0), 1);
	//gl_Position		= mvp * vec4(position, 1.0);
	//gl_Position = mvp * vec4(position + vec3(0, 0, 0), 1.0);

	

	OUT.texCoord = texCoord;
	OUT.colour = colour;
}