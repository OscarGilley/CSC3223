#version 430 core

uniform sampler2D tex;

uniform mat4 modelMatrix 	= mat4(1.0f);
uniform mat4 viewMatrix 	= mat4(1.0f);
uniform mat4 projMatrix 	= mat4(1.0f);

uniform float particleSize = 1.0f;
uniform float time;


layout(triangles) in;
layout(triangle_strip, max_vertices = 24) out;

in Vertex {
	vec4 colour;
	vec2 texCoord;
	mat4 mvp;
} IN[];
out Vertex{
	vec4 colour;
	vec2 texCoord;
	mat4 mvp;
} OUT;


void main() {

	mat4 mvp = (projMatrix * viewMatrix * modelMatrix);

	for (int i = 0; i < gl_in.length(); i++){

		//1
		gl_Position = mvp * (gl_in[i].gl_Position + vec4(-particleSize, -particleSize, particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(1,0);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(-particleSize, particleSize, particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(0,0);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(particleSize, -particleSize, particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(1,1);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(particleSize, particleSize, particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(0,1);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		//2

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(particleSize, particleSize, particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(1,0);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(particleSize, particleSize, -particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(0,0);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(particleSize, -particleSize, particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(1,1);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(particleSize, -particleSize, -particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(0,1);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		//3

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(particleSize, -particleSize, -particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(1,0);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(particleSize, -particleSize, particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(0,0);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(-particleSize, -particleSize, -particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(1,1);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(-particleSize, -particleSize, particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(0,1);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		//4

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(-particleSize, -particleSize, particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(1,0);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(-particleSize, -particleSize, -particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(0,0);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(-particleSize, particleSize, particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(1,1);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(-particleSize, particleSize, -particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(0,1);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		//5

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(-particleSize, particleSize, -particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(1,0);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(-particleSize, particleSize, particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(0,0);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(particleSize, particleSize, -particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(1,1);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(particleSize, particleSize, particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(0,1);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);

		EmitVertex();


		//6

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(particleSize, particleSize, -particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(1,0);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);

		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(-particleSize, particleSize, -particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(0,0);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);

		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(particleSize, -particleSize, -particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(1,1);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);

		EmitVertex();

		gl_Position = mvp * (gl_in[i].gl_Position + vec4(-particleSize, -particleSize, -particleSize, 0.5));
		OUT.colour = vec4(1,1,1,1);
		OUT.texCoord = vec2(0,1);
		//gl_Position = gl_Position * vec4(sin(time), cos(time), 1,1);
		EmitVertex();

		
		
		
		
		EndPrimitive();

	}

	
	/*
	vec3 normal = GetNormal();

	gl_Position = explode(gl_in[0].gl_Position, normal);
	EmitVertex();

	gl_Position = explode(gl_in[1].gl_Position, normal);
	EmitVertex();

	gl_Position = explode(gl_in[2].gl_Position, normal);
	EmitVertex();
	*/
	
}