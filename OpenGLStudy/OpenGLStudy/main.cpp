
//glad
#include <glad/glad.h>

//glfw, "#define..." can avoid the conflict caused by uncorrect sequence call of glad and glfw.
//#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"

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
	
	//creat shader program
	Shader ourShader("Resources/Shaders/shader.vs", "Resources/Shaders/shader.frag");
	
	//顶点数据
	//SINGLE TRANGLE TEST AND RECTANGLE TEST
	float vertices[] = 
	{
		-0.5f, -0.5f, 0.0f,		//左下
		 0.5f, -0.5f, 0.0f,		//右下
		 0.0f,  0.5f, 0.0f,		//右上
//		-0.5f,  0.5f, 0.0f		//左上
	};

	//TWO TRANGLES TEST
	//float vertices[] = 
	//{
 //       // first triangle
	//	-0.9f, -0.5f, 0.0f,  // left 
	//	-0.0f, -0.5f, 0.0f,  // right
	//	-0.45f, 0.5f, 0.0f,  // top 
	//	// second triangle
	//	0.0f, -0.5f, 0.0f,  // left
	//	0.9f, -0.5f, 0.0f,  // right
	//	0.45f, 0.5f, 0.0f   // top 
	//};

	unsigned int indices[] = 
	{			 // 注意索引从0开始! 
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	//VBO VAO
	unsigned int VBO, VAO; //EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//应用顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//解绑VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//解绑VAO，防止误操作
	glBindVertexArray(0);

	//以线条绘制
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Render loop
	while (!glfwWindowShouldClose(window))
	{
		//Input:
		//check if press esc
		processInput(window);

		//Render construction
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();
		//ourShader.setUniFloat("xOffset", 0.5f);
		glBindVertexArray(VAO); 
		glDrawArrays(GL_TRIANGLES, 0, 3);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);		//不需要每次都解绑

		//检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);

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