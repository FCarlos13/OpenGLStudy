#version 330 core

//in vec2 tP;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

//uniform sampler2D texture1;
//uniform sampler2D texture2;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
	vec3 norm = normalize(Normal);					//法向量标准化
	vec3 lightDir = normalize(lightPos - FragPos);	//计算光线向量
	float diff = max(dot(norm, lightDir), 0.0);		//漫反射向量
	vec3 diffuse = diff * lightColor;				//漫反射光照

	float ambientStrength = 0.1;					//环境光照数值
    vec3 ambient = ambientStrength * lightColor;	//环境光照

	vec3 result = (ambient + diffuse) * objectColor;
	FragColor = vec4(result, 1.0);

//	color = texture(texture1, tP);// * vec4(ourColor, 1.0f) // 乘上顶点颜色可以将两者混合
//	color = mix(texture(texture1, tP), texture(texture2, vec2(1.0f - tP.x, tP.y)), 0.2);
//	FragColor = vec4(objectColor * lightColor, 1.0);
}