
//glad
#include <glad/glad.h>

//glfw, "#define..." can avoid the conflict caused by uncorrect sequence call of glad and glfw.
//#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	//�����Ӵ�
	glViewport(0, 0, WIDTH, HEIGHT);
	


	//creat shader program
	Shader ourShader("Resources/Shaders/shader.vs", "Resources/Shaders/shader.frag");
	
	
	/*
				DATA
	*/


	//��������
	//SINGLE TRANGLE TEST AND RECTANGLE TEST
	float vertices[] = 
	{	//position				//texture
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		//����
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		//����
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,		//����
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f		//����
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
	{			 // ע��������0��ʼ! 
		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};
	


	/*
				VBO VAO
	*/



	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Ӧ�ö�������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//���VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//���VAO����ֹ�����
	glBindVertexArray(0);

	//����������
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	/*
			TEXTURE CODE
	*/


	//Generate texture

	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	//texture1
	glBindTexture(GL_TEXTURE_2D, texture1);
	// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ���ز���������
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);			//�Զ�����������Ҫ�Ķ༶��Զ����
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	//texture2
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ���ز���������
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);


	//load fragment shader's uniform
	ourShader.use();
	////glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // �ֶ�����
	ourShader.setUniInt("texture1", 0);
	ourShader.setUniInt("texture2", 3); // ����ʹ����ɫ��������
	//Shader.setUniInt("xxxx", value);
	//�����value��GL_TEXTURE0 + value ����Ӧ��active texture


	/*
				GLM TRANSFORM MATRIX
	*/

	glm::mat4 model, view, projection; //		vclip = vproj * vview * vmodel *vlocal
	model		= glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
	view		= glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));						// ע�⣬���ǽ�����������Ҫ�����ƶ������ķ������ƶ�
	projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

	int transUniChange;



	/*
				RENDER LOOP
	*/


	while (!glfwWindowShouldClose(window))
	{
		//Input:
		//check if press esc
		processInput(window);

		//Render construction
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, texture2);

		transUniChange = glGetUniformLocation(ourShader.ID, "model");
		glUniformMatrix4fv(transUniChange, 1, GL_FALSE, glm::value_ptr(model));
		transUniChange = glGetUniformLocation(ourShader.ID, "view");
		glUniformMatrix4fv(transUniChange, 1, GL_FALSE, glm::value_ptr(view));
		transUniChange = glGetUniformLocation(ourShader.ID, "projection");
		glUniformMatrix4fv(transUniChange, 1, GL_FALSE, glm::value_ptr(projection));

		ourShader.use();
		//ourShader.setUniFloat("xOffset", 0.5f);
		glBindVertexArray(VAO); 
//		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);		//����Ҫÿ�ζ����

		//��鲢�����¼�����������
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteTextures(1, &texture1);
	glDeleteTextures(1, &texture2);

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