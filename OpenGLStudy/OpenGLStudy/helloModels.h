#include "glheader.h"

#include "Model.h"

namespace HelloMyModel
{
	class HelloModel
	{
	private:
		Model myModel;
		Shader myShader;
		Camera myCamera;
	public:
		HelloModel(const char* path) :
			myModel(path), myShader("Resources\\Shaders\\1.model_loading.vs", "Resources\\Shaders\\1.model_loading.fs"),
			myCamera(glm::vec3(0.0f, 0.0f, 3.0f)){};
		~HelloModel() = default;
		//function
		void displayModels();
	};

	void HelloModel::displayModels()
	{
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(myCamera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = myCamera.GetViewMatrix();
		myShader.setUniMat4("projection", projection);
		myShader.setUniMat4("view", view);

		// render the loaded model
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -10.0f, -10.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
		myShader.setUniMat4("model", model);
		myModel.Draw(myShader);
	}
}