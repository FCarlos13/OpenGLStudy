#pragma once
#include"glheader.h"
#include"Light.h"


//==================================
//				DATA
//==================================


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

class helloComposition
{
private:
	Shader lightingShader;
	Shader lampShader;

	Camera myCamera;

};


















//三盏light
Light dirLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.05f, 0.05f, 0.05f),
	glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.5f, 0.5f, 0.5f));
Light pointLight[4] =
{
	Light(pointLightPositions[0], glm::vec3(0.05f, 0.05f, 0.05f),
			glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f),
			1.0f, 0.09, 0.032),
	Light(pointLightPositions[1], glm::vec3(0.05f, 0.05f, 0.05f),
			glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f),
			1.0f, 0.09, 0.032),
	Light(pointLightPositions[2], glm::vec3(0.05f, 0.05f, 0.05f),
			glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f),
			1.0f, 0.09, 0.032),
	Light(pointLightPositions[3], glm::vec3(0.05f, 0.05f, 0.05f),
			glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f),
			1.0f, 0.09, 0.032)
};
Light spotLight(myCamera.Front, myCamera.Position, glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
	1.0f, 0.09, 0.032, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)));
/*
			CREAT SHADER PROJECT
*/

Shader lightingShader("Resources/Shaders/shader.vs", "Resources/Shaders/shader.frag");
Shader lampShader("Resources/Shaders/light_cube.vs", "Resources/Shaders/light_cube.frag");
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


//以线条绘制
//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

/*
		TEXTURE CODE
*/

//Generate texture

unsigned int diffuseMap = loadTexture("../External Sources/pics/container2.png");
unsigned int specularMap = loadTexture("../External Sources/pics/container2_specular.png");
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
	lightingShader.setUniVec3("viewPos", myCamera.Position);
	lightingShader.setUniFloat("material.shininess", 64.0f);

	// directional light
	lightingShader.setUniVec3("dirLight.direction", dirLight.getDirection());
	lightingShader.setUniVec3("dirLight.ambient", dirLight.getAmbient());
	lightingShader.setUniVec3("dirLight.diffuse", dirLight.getDiffuse());
	lightingShader.setUniVec3("dirLight.specular", dirLight.getSpecular());
	// point light 1
	lightingShader.setUniVec3("pointLights[0].position", pointLight[0].getPosition());
	lightingShader.setUniVec3("pointLights[0].ambient", pointLight[0].getAmbient());
	lightingShader.setUniVec3("pointLights[0].diffuse", pointLight[0].getDiffuse());
	lightingShader.setUniVec3("pointLights[0].specular", pointLight[0].getSpecular());
	lightingShader.setUniFloat("pointLights[0].constant", pointLight[0].getConstant());
	lightingShader.setUniFloat("pointLights[0].linear", pointLight[0].getLinear());
	lightingShader.setUniFloat("pointLights[0].quadratic", pointLight[0].getQuadratic());
	// point light 2
	lightingShader.setUniVec3("pointLights[1].position", pointLight[1].getPosition());
	lightingShader.setUniVec3("pointLights[1].ambient", pointLight[1].getAmbient());
	lightingShader.setUniVec3("pointLights[1].diffuse", pointLight[1].getDiffuse());
	lightingShader.setUniVec3("pointLights[1].specular", pointLight[1].getSpecular());
	lightingShader.setUniFloat("pointLights[1].constant", pointLight[1].getConstant());
	lightingShader.setUniFloat("pointLights[1].linear", pointLight[1].getLinear());
	lightingShader.setUniFloat("pointLights[1].quadratic", pointLight[1].getQuadratic());
	// point light 3
	lightingShader.setUniVec3("pointLights[2].position", pointLight[2].getPosition());
	lightingShader.setUniVec3("pointLights[2].ambient", pointLight[2].getAmbient());
	lightingShader.setUniVec3("pointLights[2].diffuse", pointLight[2].getDiffuse());
	lightingShader.setUniVec3("pointLights[2].specular", pointLight[2].getSpecular());
	lightingShader.setUniFloat("pointLights[2].constant", pointLight[2].getConstant());
	lightingShader.setUniFloat("pointLights[2].linear", pointLight[2].getLinear());
	lightingShader.setUniFloat("pointLights[2].quadratic", pointLight[2].getQuadratic());
	//// point light 4
	lightingShader.setUniVec3("pointLights[3].position", pointLight[3].getPosition());
	lightingShader.setUniVec3("pointLights[3].ambient", pointLight[3].getAmbient());
	lightingShader.setUniVec3("pointLights[3].diffuse", pointLight[3].getDiffuse());
	lightingShader.setUniVec3("pointLights[3].specular", pointLight[3].getSpecular());
	lightingShader.setUniFloat("pointLights[3].constant", pointLight[3].getConstant());
	lightingShader.setUniFloat("pointLights[3].linear", pointLight[3].getLinear());
	lightingShader.setUniFloat("pointLights[3].quadratic", pointLight[3].getQuadratic());
	// spotLight
	lightingShader.setUniVec3("spotLight.position", myCamera.Position);
	lightingShader.setUniVec3("spotLight.direction", myCamera.Front);
	lightingShader.setUniVec3("spotLight.ambient", spotLight.getAmbient());
	lightingShader.setUniVec3("spotLight.diffuse", spotLight.getDiffuse());
	lightingShader.setUniVec3("spotLight.specular", spotLight.getSpecular());
	lightingShader.setUniFloat("spotLight.constant", spotLight.getConstant());
	lightingShader.setUniFloat("spotLight.linear", spotLight.getLinear());
	lightingShader.setUniFloat("spotLight.quadratic", spotLight.getQuadratic());
	lightingShader.setUniFloat("spotLight.cutOff", spotLight.getCutOff());
	lightingShader.setUniFloat("spotLight.outerCutOff", spotLight.getOuterCutOff());

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(myCamera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = myCamera.GetViewMatrix();
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

	glBindVertexArray(objectVAO);

	for (unsigned int i = 0; i < 10; i++)
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		lightingShader.setUniMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// also draw the lamp object
	lampShader.use();
	lampShader.setUniMat4("projection", projection);
	lampShader.setUniMat4("view", view);
	glBindVertexArray(lightVAO);
	for (unsigned int i = 0; i < 4; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pointLightPositions[i]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		lampShader.setUniMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	//检查并调用事件，交换缓冲
	glfwPollEvents();
	glfwSwapBuffers(window);
}

//de-allocate all resources once they've outlived their purpose:
glDeleteVertexArrays(1, &objectVAO);
glDeleteVertexArrays(1, &lightVAO);
glDeleteBuffers(1, &VBO);
glDeleteTextures(1, &diffuseMap);
glDeleteTextures(1, &specularMap);