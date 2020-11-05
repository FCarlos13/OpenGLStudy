//#include"helloModels.h"


//void renderLoop()
//{
//	while (!glfwWindowShouldClose(window))
//	{
//		// per-frame time logic
//		// --------------------
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		// input
//		// -----
//		processInput(window);
//
//		// render
//		// ------
//		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		// don't forget to enable shader before setting uniforms
//		ourShader.use();
//
//		// view/projection transformations
//		glm::mat4 projection = glm::perspective(glm::radians(ourCamera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
//		glm::mat4 view = ourCamera.GetViewMatrix();
//		ourShader.setUniMat4("projection", projection);
//		ourShader.setUniMat4("view", view);
//
//		// render the loaded model
//		glm::mat4 model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(0.0f, -10.0f, -10.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
//		ourShader.setUniMat4("model", model);
//		ourModel.Draw(ourShader);
//
//
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		// -------------------------------------------------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//}

const int WIDTH = 800, HEIGHT = 600;

HelloMyModel::HelloModel::HelloModel(const char *path) :myModel(path) 
{

}

void HelloMyModel::HelloModel::displayModels(Shader shader, Camera camera)
{
	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	shader.setUniMat4("projection", projection);
	shader.setUniMat4("view", view);

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -10.0f, -10.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
	shader.setUniMat4("model", model);
	myModel.Draw(shader);
}