//***

#include <iostream>

//glad
#include <glad/glad.h>

//glfw, "#define..." can avoid the conflict caused by uncorrect sequence call of glad and glfw.
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

int main()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw." << std::endl;
	}
	std::cout << "hello world." << std::endl;
	return 0;
}