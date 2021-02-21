#version 400 core

uniform mat4 modelMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 projMatrix = mat4(1.0f);

uniform sampler2D 	mainTex;

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;

out Vertex{
	vec4 colour;
	vec2 texCoord;
	mat4 mvp;
	vec3 worldPos;
	vec3 normal;
} OUT;

void main(void) {
	vec4 worldPos = modelMatrix * vec4(position, 1.0);

	gl_Position = (projMatrix * viewMatrix) * worldPos;

	OUT.texCoord = texCoord;
	OUT.worldPos = worldPos.xyz;

	mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));

	OUT.normal = normalize(normalMatrix * normalize(normal));

	//other
	mat4 mvp 		= (projMatrix * viewMatrix * modelMatrix);

	//gl_Position		= mvp * vec4(position, 1.0);

	//OUT.texCoord	= texCoord;
	OUT.colour		= colour;
}