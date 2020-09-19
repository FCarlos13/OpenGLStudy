
//glad
#include <glad/glad.h>

//glfw, "#define..." can avoid the conflict caused by uncorrect sequence call of glad and glfw.
//#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

const GLuint WIDTH = 800, HEIGHT = 600;

//function prototype
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
	//Begin with my project.
	std::cout << "hello world." << std::endl;

	//Initialize glfw
	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw." << std::endl;
		return -1;
	}
	
	//Creat window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);							//This make the window size changeable.

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Initialize glad
	//WARNING HERE: glad init must be after making window current.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//创建视窗
	glViewport(0, 0, WIDTH, HEIGHT);

	//Render loop
	while (!glfwWindowShouldClose(window))
	{
		//Input:
		//check if press esc
		processInput(window);

		//Render construction
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}