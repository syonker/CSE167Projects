#version 330 core

// Note that you do not have access to the vertex shader's default output, gl_Position.
in vec3 Normal;
in vec3 FragPos;
in vec4 ShadowCoord;


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

uniform sampler2DShadow shadowMap;
uniform vec3 viewPos;
uniform Light light;
uniform vec3 kd;
uniform vec3 ks;
uniform vec3 ka;
uniform float p;
uniform mat4 model;
uniform int toon;
uniform int shadowsOn;
uniform int beenShot;


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

	else if (beenShot == 1) {
	
	
		color = vec4(0.0,0.0,0.0,1.0);
	
	}

	else {


		//float bias = 0.005;

		//float bias = 0.005*tan(acos(cosTheta)); // cosTheta is dot( n,l ), clamped between 0 and 1
		//bias = clamp(bias, 0,0.01);

		//float visibility = texture( shadowMap, vec3(ShadowCoord.x,ShadowCoord.y,ShadowCoord.z), bias );

		//float visibility = texture( shadowMap, vec3(ShadowCoord.xy, (ShadowCoord.z)/ShadowCoord.w), bias );

		//float visibility = 1.0;

		//float visibility = textureProj( shadowMap, ShadowCoord, bias );


		//float bias = 0.005;
	//float visibility = 1.0;
	//if ( texture( shadowMap, ShadowCoord.xy ).z  <  ShadowCoord.z-bias){
		//visibility = 0.5;
	//}

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

			/*

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
		
			*/
		
		}


		//useful initializations
		vec3 norm = newNormal;
		vec3 viewDir = normalize(newFragPos - viewPos);

		vec3 Lnorm = normalize(L);

		//cL = normalize(cL);

		//increment for toon shading
		float inc = 0.4;

		
		//diffuse
		vec3 diffuse = cL*kd*(max(dot(norm, Lnorm), 0.0));

		if (toon == 1) {

			for (float i = inc; i <= 1.0; i+=inc) {

				if ((diffuse.x < i) && (diffuse.x > i-inc)) {
				
					diffuse.x = ((i + (i-inc))/2.0);
				
				}

				if ((diffuse.y < i) && (diffuse.y > i-inc)) {
				
					diffuse.y = ((i + (i-inc))/2.0);
				
				}

				if ((diffuse.z < i) && (diffuse.z > i-inc)) {
				
					diffuse.z = ((i + (i-inc))/2.0);
				
				}

			}


		}


		//specualr
		//vec3 reflectDir = ((2.0f)*max(dot(norm, Lnorm), 0.0)*norm)-Lnorm;


		vec3 reflectDir = reflect(-L,norm);



		float spec = pow(max(dot(reflectDir, -viewDir), 0.0), p);

		vec3 specular = ks*cL*spec;









		if (toon == 1) {

			for (float i = inc; i <= 1.0; i+=inc) {

				if ((specular.x < i) && (specular.x > i-inc)) {
				
					specular.x = ((i + (i-inc))/2.0);
				
				}

				if ((specular.y < i) && (specular.y > i-inc)) {
				
					specular.y = ((i + (i-inc))/2.0);
				
				}

				if ((specular.z < i) && (specular.z > i-inc)) {
				
					specular.z = ((i + (i-inc))/2.0);
				
				}

			}

		}

		//ambient
		vec3 ambient = cL*ka;

		float cosTheta = clamp(dot(norm,L),0.0,1.0);
		float bias = 0.005*tan(acos(cosTheta)); // cosTheta is dot( n,l ), clamped between 0 and 1
		bias = clamp(bias, 0,0.01);


		//bias = .005;

		float visibility = texture( shadowMap, vec3(ShadowCoord.xy, (ShadowCoord.z-bias)/ShadowCoord.w));

		if (shadowsOn == 0) {
		
			visibility = 1;
		
		}

		//visibility = 1.0;



		//final result
		color = vec4((visibility*diffuse + ambient + visibility*specular), 1.0);

		//color = vec4(ambient, 1.0);

		vec3 saveColor;

		
		float whiteCutoff = 0.85;
		
		if (toon == 2) {

			if ((color.x > whiteCutoff) && (color.y > whiteCutoff) && (color.z > whiteCutoff)) {
			
				//keep white
				

			} 
			
			else {

				for (float i = inc; i <= 1.0; i+=inc) {

					if ((color.x < i) && (color.x > i-inc)) {
				
						saveColor.x = ((i + (i-inc))/2.0);
				
					}

					if ((color.y < i) && (color.y > i-inc)) {
				
						saveColor.y = ((i + (i-inc))/2.0);
				
					}

					if ((color.z < i) && (color.z > i-inc)) {
				
						saveColor.z = ((i + (i-inc))/2.0);
				
					}

				}

				color = vec4(saveColor, 1.0);

			}


		}





		float edge = max(0,dot(norm,-viewDir));

		if ((toon == 1) && (edge < 0.25)) {
		
			color = vec4(0.0,0.0,0.0,1.0);
		
		}




	
	}

	
/*
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
		vec3 viewDir = normalize(FragPos - viewPos);

		
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
	*/
}

