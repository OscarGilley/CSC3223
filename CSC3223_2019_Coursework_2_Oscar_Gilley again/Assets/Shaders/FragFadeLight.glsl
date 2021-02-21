#version 400 core

uniform vec3 cameraPos;

uniform sampler2D mainTex;
uniform sampler2D secondTex;

uniform float time;

uniform vec3 lightColour;
uniform vec3 lightPos;
uniform float lightRadius;

in Vertex{
	mat4 mvp;
	vec4 colour;
	vec2 texCoord;
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
	fragColor = vec4(ambient + diffuse + specular, texCol.a);
	vec4 normTex = texture2D(mainTex, IN.texCoord);


	//vec4 normTex = texture2D(mainTex, IN.texCoord);

	float timeFrac = time;
	float timeFade = 1 - (time / 15);

	if (time < 1){
		fragColor = mix(vec4(0,0,0,0), vec4(ambient + diffuse + specular, texCol.a), timeFrac);
	}

	if (time >= 1){
		fragColor = mix(vec4(0,0,0,0), vec4(ambient + diffuse + specular, texCol.a), timeFade);
	}

	
	
}