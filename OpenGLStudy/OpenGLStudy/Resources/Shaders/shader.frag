#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct Light {

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
    float linear;
    float quadratic;

	vec3  position;
    vec3  direction;
    float cutOff;
	float outerCutOff;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 tP;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{

    vec3 lightDir = normalize(light.position - FragPos);

	float theta = dot(lightDir, normalize(-light.direction));						//计算当前手电筒的扩散角度

	

	// ambient
	vec3 ambient = light.ambient * texture(material.diffuse, tP).rgb;
        
    // diffuse 
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, tP).rgb;  
        
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, tP).rgb;  

	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); 
	diffuse  *= intensity;
	specular *= intensity;

	float distance    = length(light.position - FragPos);							//计算片段距光源距离
	float attenuation = 1.0 / (light.constant + light.linear * distance +			//衰减系数
							light.quadratic * (distance * distance));
	diffuse   *= attenuation;
    specular  *= attenuation;

            
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
	

    // ambient
    /* vec3 ambient = light.ambient * texture(material.diffuse, tP).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);;
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, tP).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, tP).rgb;  
	
	ambient  *= attenuation; 
	diffuse  *= attenuation;
	specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);*/
} 