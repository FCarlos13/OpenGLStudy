
//glad
#include <glad/glad.h>
//glfw, "#define..." can avoid the conflict caused by uncorrect sequence call of glad and glfw.
//#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

#include <iostream>

//Settings
const GLuint WIDTH = 800, HEIGHT = 600;

// camera
Camera ourCamera(glm::vec3(0.0f, 0.0f, 3.0f));//相机位置在 (0,0,3)的位置，相机类里默认是世界原点
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//global light setting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

//function prototype
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(char const * path);

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

	/*
			GLFW SETTINGS
	*/

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/*
			GLAD INITIALIZING
	*/

	//WARNING HERE: glad init must be after making window current.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//创建视窗
	glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_DEPTH_TEST);

	/*
			CREAT SHADER PROJECT
	*/

	Shader lightingShader("Resources/Shaders/shader.vs", "Resources/Shaders/shader.frag");
	Shader lampShader("Resources/Shaders/light_cube.vs", "Resources/Shaders/light_cube.frag");

	/*
				DATA
	*/


	float vertices[] = 
	{
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = 
	{
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::vec3 pointLightPositions[] = 
	{
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
	};

	/*
				VBO objectVAO
	*/

	unsigned int VBO, objectVAO;// EBO;
	glGenVertexArrays(1, &objectVAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(objectVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	//bind lightVAO
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//解绑VBO
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//解绑objectVAO，防止误操作
	//glBindVertexArray(0);

	//以线条绘制
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/*
			TEXTURE CODE
	*/

	//Generate texture

	unsigned int diffuseMap = loadTexture("container2.png");
	unsigned int specularMap = loadTexture("container2_specular.png");
	//stbi_set_flip_vertically_on_load(true);

	lightingShader.use();
	lightingShader.setUniInt("material.diffuse", 0);
	lightingShader.setUniInt("material.specular", 1);


	/*
				RENDER LOOP
	*/


	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Input:
		//check if press esc
		processInput(window);

		//Render construction
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

		// be sure to activate shader when setting uniforms/drawing objects

		lightingShader.use(); 
		//lightingShader.setUniVec3("light.direction", 0.0f, 0.0f, -1.0f);
		//lightingShader.setUniVec3("light.position", lightPos);
		lightingShader.setUniVec3("viewPos", ourCamera.Position);
		lightingShader.setUniFloat("material.shininess", 64.0f);

		// directional light
		lightingShader.setUniVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		lightingShader.setUniVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setUniVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		lightingShader.setUniVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
		// point light 1
		lightingShader.setUniVec3("pointLights[0].position", pointLightPositions[0]);
		lightingShader.setUniVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setUniVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setUniVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setUniFloat("pointLights[0].constant", 1.0f);
		lightingShader.setUniFloat("pointLights[0].linear", 0.09);
		lightingShader.setUniFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		lightingShader.setUniVec3("pointLights[1].position", pointLightPositions[1]);
		lightingShader.setUniVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setUniVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setUniVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setUniFloat("pointLights[1].constant", 1.0f);
		lightingShader.setUniFloat("pointLights[1].linear", 0.09);
		lightingShader.setUniFloat("pointLights[1].quadratic", 0.032);
		// point light 3
		lightingShader.setUniVec3("pointLights[2].position", pointLightPositions[2]);
		lightingShader.setUniVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setUniVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setUniVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setUniFloat("pointLights[2].constant", 1.0f);
		lightingShader.setUniFloat("pointLights[2].linear", 0.09);
		lightingShader.setUniFloat("pointLights[2].quadratic", 0.032);
		// point light 4
		lightingShader.setUniVec3("pointLights[3].position", pointLightPositions[3]);
		lightingShader.setUniVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setUniVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setUniVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setUniFloat("pointLights[3].constant", 1.0f);
		lightingShader.setUniFloat("pointLights[3].linear", 0.09);
		lightingShader.setUniFloat("pointLights[3].quadratic", 0.032);
		// spotLight
		lightingShader.setUniVec3("spotLight.position", ourCamera.Position);
		lightingShader.setUniVec3("spotLight.direction", ourCamera.Front);
		lightingShader.setUniVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		lightingShader.setUniVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		lightingShader.setUniVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setUniFloat("spotLight.constant", 1.0f);
		lightingShader.setUniFloat("spotLight.linear", 0.09);
		lightingShader.setUniFloat("spotLight.quadratic", 0.032);
		lightingShader.setUniFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		lightingShader.setUniFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(ourCamera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = ourCamera.GetViewMatrix();
		lightingShader.setUniMat4("projection", projection);
		lightingShader.setUniMat4("view", view);

		// world transformation
		//glm::mat4 model = glm::mat4(1.0f);
		//lightingShader.setUniMat4("model", model);

		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			lightingShader.setUniMat4("model", model);

			glBindVertexArray(objectVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}



		// also draw the lamp object
		lampShader.use();
		lampShader.setUniMat4("projection", projection);
		lampShader.setUniMat4("view", view);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lampShader.setUniMat4("model", model);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);



		//检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &objectVAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	/*glDeleteTextures(1, &texture1);
	glDeleteTextures(1, &texture2);*/

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;
	ourCamera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	ourCamera.ProcessMouseScroll(yoffset);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		ourCamera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		ourCamera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		ourCamera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		ourCamera.ProcessKeyboard(RIGHT, deltaTime);
}

unsigned int loadTexture(GLchar const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	return textureID;
}