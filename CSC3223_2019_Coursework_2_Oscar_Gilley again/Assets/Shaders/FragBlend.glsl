#version 400 core

uniform sampler2D mainTex;
uniform sampler2D secondTex;

uniform vec3 cameraPos;

uniform mat4 modelMatrix 	= mat4(1.0f);
uniform mat4 viewMatrix 	= mat4(1.0f);
uniform mat4 projMatrix 	= mat4(1.0f);


uniform vec3 lightColour;
uniform vec3 lightPos;
uniform float lightRadius;

uniform float time;

in Vertex{
	vec4 colour;
	vec2 texCoord;
	mat4 mvp;
	vec3 worldPos;
	vec3 normal;
} IN;

out vec4 fragColor;

void main(void) {

	//lighting
	vec3 incident = normalize(lightPos - IN.worldPos);
	vec3 viewDir = normalize(cameraPos - IN.worldPos);
	vec3 halfDir = normalize(incident + viewDir);
	float dist = length(lightPos - IN.worldPos);
	float atten = 1.0 - clamp(dist / lightRadius, 0.0, 1.0);

	float lambert = max(0.0, dot(incident, IN.normal));

	float rFactor = max(0.0, dot(halfDir, normalize(IN.normal)));
	float sFactor = pow(rFactor, 50.0);

	vec4 texCol = texture(mainTex, IN.texCoord);
	vec3 ambient = texCol.rgb * lightColour * 0.1;
	vec3 diffuse = texCol.rgb * lightColour * lambert * atten;
	vec3 specular = lightColour * sFactor * atten;
	vec4 fragTexa = vec4(ambient + diffuse + specular, texCol.a);

	vec4 texColb = texture(secondTex, IN.texCoord);
	ambient = texColb.rgb * lightColour * 0.1;
	diffuse = texColb.rgb * lightColour * lambert * atten;
	specular = lightColour * sFactor * atten;
	vec4 fragTexb = vec4(ambient + diffuse + specular, texColb.a);
	


	vec4 normTex = texture2D(mainTex, IN.texCoord);
	vec4 destroyedTex = texture2D(secondTex, IN.texCoord);

	float pct = abs(sin(time/3));
	
	
	fragColor = mix(fragTexa, fragTexb, pct);

	
	
	
	
}