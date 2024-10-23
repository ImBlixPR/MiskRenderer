#version 400 

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform sampler2D specTexture;
uniform vec3 lightPos;
uniform vec3 viewPos;



void main()
{
	vec3 normal = normalize(Normal);
	
	vec3 lightDiff = vec3(0.2);
	vec3 lightAmb = vec3(0.5);
	vec3 lightSpec = vec3(1.0);
	
	//ambient light
	float ambientStringth = 0.1;
	vec3 ambient = lightAmb * vec3(texture(ourTexture, TexCoords));
	
	//diffuse light
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(normal, lightDir),0.0);
	vec3 diffuse =  lightDiff * diff *  vec3(texture(ourTexture, TexCoords));
	
	//specular light
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, normal); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	//vec3 specular = specularStrength * spec * lightSpec;  
	vec3 specular = lightSpec * (spec * vec3(texture(specTexture, TexCoords))) ;  
	
	
	
	
	
	vec3 texColor = (ambient + diffuse + specular );
	
	FragColor = vec4(texColor, 1.0);
	//FragColor += vec4(normal, 1.0);

}