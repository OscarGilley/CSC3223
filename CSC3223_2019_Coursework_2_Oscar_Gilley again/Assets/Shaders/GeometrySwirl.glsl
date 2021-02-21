#version 430 core

uniform sampler2D mainTex;

uniform mat4 modelMatrix 	= mat4(1.0f);
uniform mat4 viewMatrix 	= mat4(1.0f);
uniform mat4 projMatrix 	= mat4(1.0f);

uniform float particleSize = 1.0f;
uniform float time;


layout(triangles) in;
layout(triangle_strip, max_vertices = 24) out;

in Vertex {
	
	vec2 texCoord;
	
} IN[];
out Vertex{
	
	vec2 texCoord;
	
} OUT;
//these two methods were adapted from an online resource
//https://learnopengl.com/Advanced-OpenGL/Geometry-Shader
vec3 getNormal(){
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a,b));
}

vec4 swirl(vec4 position, vec3 normal){
	vec3 direction = normal * (-(time * time) + (3 * time) + 0);
	return position + vec4(direction, 0.0);
}


void main() {
	
	vec3 normal = getNormal();
	//vec4 normTex = texture2D(mainTex, IN.texCoord);

	gl_Position = swirl(gl_in[0].gl_Position, normal);
	OUT.texCoord = IN[0].texCoord;
	EmitVertex();

	gl_Position = swirl(gl_in[1].gl_Position, normal);
	OUT.texCoord = IN[1].texCoord;
	EmitVertex();

	gl_Position = swirl(gl_in[2].gl_Position, normal);
	OUT.texCoord = IN[2].texCoord;
	EmitVertex();
	
	
}