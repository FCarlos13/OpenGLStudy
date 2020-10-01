#include "Shader.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <iostream>

class Light
{
private:
	glm::vec3 direction;
	glm::vec3 position;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float cutOff;
	float outerCutOff;
public:
	//¹¹Ôìº¯Êý
	//DirLight
	Light(glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular):
		direction(dir), ambient(ambient), diffuse(diffuse), specular(specular){ }
	//PointLight
	Light(glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, 
			float constant, float linear, float quadratic):
		position(pos), ambient(ambient), diffuse(diffuse), specular(specular), constant(constant), 
		linear(linear), quadratic(quadratic) { }
	//SpotLight
	Light(glm::vec3 dir, glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, 
			float constant, float linear, float quadratic, float cutOff, float outerCutOff):
		direction(dir), position(pos), ambient(ambient), diffuse(diffuse), specular(specular), 
		constant(constant), linear(linear), quadratic(quadratic), cutOff(cutOff), outerCutOff(outerCutOff){ }

	~Light() = default;

	//Read Only function
	glm::vec3 getDirection(){ return direction; }
	glm::vec3 getPosition() { return position; }
	glm::vec3 getAmbient()  { return ambient; }
	glm::vec3 getDiffuse()  { return diffuse; }
	glm::vec3 getSpecular() { return specular; }
	float getConstant()     { return constant; }
	float getLinear()		{ return linear; }
	float getQuadratic()	{ return quadratic; }
	float getCutOff()		{ return cutOff; }
	float getOuterCutOff()	{ return outerCutOff; }
};


