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
uniform mat4 model;
//uniform int isSphere;


// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 color;

void main()
{

	// calculate normal in world coordinates
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 newNormal = normalize(normalMatrix * Normal);

	// calculate the location of this fragment (pixel) in world coordinates
	vec3 newFragPos = vec3(model * vec4(FragPos, 1));


	if (light.normalColoring == 1) {

		color = vec4(newNormal.x, newNormal.y, newNormal.z, 1.0f);

	}

	else {

		//will change depending on our lights type
		vec3 cL;
		vec3 L;
		float denom;
		vec3 temp;



		
		//directional
		if (light.type == 1) {
		
			cL = light.color;

			L = normalize(-light.direction);
		

		//point
		} else if (light.type == 2) {

			temp = light.position - newFragPos;

			denom = sqrt((temp.x*temp.x)+(temp.y*temp.y)+(temp.z*temp.z));

			cL = light.color/(light.linearAtt*denom);
			
			L = (light.position - newFragPos)/denom;
		
		
		//spot
		} else {

			

			temp = light.position - newFragPos;
			denom = sqrt((temp.x*temp.x)+(temp.y*temp.y)+(temp.z*temp.z));

			L = (light.position - newFragPos)/denom;


			if (dot(-L,light.direction) <= cos(light.cutoffAngle)) {
			
				cL.x = 0.0f;
				cL.y = 0.0f;
				cL.z = 0.0f;
			
			} else {
			
				cL = light.color*pow(dot(-L,light.direction),light.exponent);
			
			}

			//float brightness = dot(Normal, temp) / (length(temp) * length(Normal));
			//brightness = clamp(brightness, 0, 1);
			//lightColor = {brightness * light.color * surfaceColor.rgb, surfaceColor.a};
		
			
		
		}





		//useful initializations
		vec3 norm = newNormal;
		vec3 viewDir = normalize(newFragPos - viewPos);

		vec3 Lnorm = normalize(L);

		
		//diffuse
		vec3 diffuse = cL*kd*(max(dot(norm, Lnorm), 0.0));


		//specualr
		vec3 reflectDir = reflect(-L,norm);

		float spec = pow(max(dot(reflectDir, -viewDir), 0.0), p);

		vec3 specular = ks*cL*spec;


		//ambient
		vec3 ambient = cL*ka;



		//final result
		color = vec4((diffuse + ambient + specular), 1.0);

	
	}
}

