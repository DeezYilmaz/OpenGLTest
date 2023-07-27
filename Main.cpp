

#include "glad/glad.h"
#include "glfw3.h"
#include <iostream>
#include "Shader_s.h"
#include <stb_image.h>


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "Cube.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;

double MouseX = 0;
double MouseY = 0;

int projectUni;
int transfromUni;
int MousePosUni;
int textureUni;

Camera camera(glm::vec3(0.f,0.f,1.f));

glm::mat4 view;
glm::mat4 projection;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "TestWindow", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);



	//------------LINK SHADER-------------

	Shader ourShader("Vertex.vert", "Fragment.frag");


	//---------------CREATE PROGRAM-------------
	ourShader.use();
	//----------VERTEX ATTRIBUTES---------
	//----------------UNIFORMS-------------
	
	projectUni = glGetUniformLocation(ourShader.ID, "projectAndCamera");
	transfromUni = glGetUniformLocation(ourShader.ID, "model");
	textureUni = glGetUniformLocation(ourShader.ID, "ourTexture");

	//----------------GENERATE TEXTURE---------------
#pragma region texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture



	int width, height, nrChannels;
	unsigned char* data = stbi_load("textures\\emerald.png", &width, &height, &nrChannels, 0);
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
	glUniform1i(textureUni, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

#pragma endregion initialize Texture
	//-------------------------------

	glEnable(GL_DEPTH_TEST);



	std::vector<unique_ptr<Drawable>> cubes;


	for (size_t i = 0; i < 1000; i++)
	{
		Cube cb;
		cb.setUniforms(transfromUni);
		glm::vec3 translation(rand()%500/10.f, rand() %500 / 10.f, rand() % 100 / 10.f);
		cb.moveObject(&translation);
		cubes.push_back(std::make_unique<Cube>(cb));
	}





	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		processInput(window);

		projection = glm::perspective(glm::radians(camera.Zoom), (float)WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
		view = camera.GetViewMatrix();

		glUniformMatrix4fv(projectUni, 1, GL_FALSE, glm::value_ptr(projection* view));

		for (size_t i = 0; i < cubes.size(); i++)
		{
			cubes[i]->draw();
		}




		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	system("pause");
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}



float speed = 0.5f;


float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;
bool mouseActive = false;

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, 0.1);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, 0.1);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, 0.1);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, 0.1);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, .1);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, .1);




	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

		mouseActive = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else {

		mouseActive = false;
		firstMouse = true;
		double xpos = (WINDOW_WIDTH / 2.0);
		double ypos = (WINDOW_HEIGHT / 2.0);
		glfwGetCursorPos(window, &xpos, &ypos);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
	}
}




void cursor_position_callback(GLFWwindow* window, double xposIn, double yposIn)
{

	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

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

	if(mouseActive)
		camera.ProcessMouseMovement(xoffset, yoffset);
		
}