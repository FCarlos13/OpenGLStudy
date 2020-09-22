#version 330 core

//in vec3 ourColor;
in vec2 tP;

out vec4 color;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
//	color = texture(texture1, tP);// * vec4(ourColor, 1.0f) // 乘上顶点颜色可以将两者混合
	color = mix(texture(texture1, tP), texture(texture2, vec2(1.0f - tP.x, tP.y)), 0.2);
}