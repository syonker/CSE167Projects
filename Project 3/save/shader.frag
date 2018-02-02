#version 330 core
// This is a sample fragment shader. 460?

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
in vec3 Normal;
in vec3 FragPos;


struct Light
{

	int normalColoring;

	int type;

	vec3 color;
	vec3 direction;
	
	vec3 position;

	float consAtt;
	float linearAtt;
	float quadAtt;

	float cutoffAngle;
	float exponent;

};

uniform vec3 viewPos;
uniform Light light;
uniform vec3 kd;
uniform vec3 ks;
uniform vec3 ka;
uniform float p;
//uniform int isSphere;


// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 color;

void main()
{

	if (light.normalColoring == 1) {

		color = vec4(Normal.x, Normal.y, Normal.z, 1.0f);

	}

	else {

		//will change depending on our lights type
		vec3 lightColor;
		vec3 lightDir;
		float denom;
		vec3 temp;

		//directional
		if (light.type == 1) {
		
			lightColor = light.color;

			lightDir = normalize(-light.direction);
		

		//point
		} else if (light.type == 2) {

			temp = light.position - FragPos;

			denom = sqrt((temp.x*temp.x)+(temp.y*temp.y)+(temp.z*temp.z));

			lightColor = light.color/(light.linearAtt*denom);
			
			lightDir = (light.position - FragPos)/denom;
		
		
		//spot
		} else {

			temp = light.position - FragPos;
			denom = sqrt((temp.x*temp.x)+(temp.y*temp.y)+(temp.z*temp.z));

			lightDir = (light.position - FragPos)/denom;


			if (dot(-lightDir,light.direction) <= cos(light.cutoffAngle)) {
			
				lightColor.x = 0.0f;
				lightColor.y = 0.0f;
				lightColor.z = 0.0f;
			
			} else {
			
				lightColor = light.color*pow(dot(-lightDir,light.direction),light.exponent);
			
			}

			//float brightness = dot(Normal, temp) / (length(temp) * length(Normal));
			//brightness = clamp(brightness, 0, 1);
			//lightColor = {brightness * light.color * surfaceColor.rgb, surfaceColor.a};
		
		
		}


		//useful initializations
		vec3 norm = normalize(Normal);
		vec3 viewDir = normalize(viewPos - FragPos);

		
		//diffuse
		vec3 diffuse = lightColor*kd*(max(dot(norm, lightDir), 0.0));


		//specualr
		vec3 reflectDir = 2*max(dot(norm, lightDir), 0.0)*norm-lightDir;

		float spec = pow(max(dot(viewDir, reflectDir), 0.0), p);

		vec3 specular = lightColor*ks*spec;


		//ambient
		vec3 ambient = lightColor*ka;

		//final result
		color = vec4((diffuse + ambient + specular), 1.0);

	
	}
}

