

#include "glad/glad.h"
#include "glfw3.h"
#include <iostream>
#include "Shader_s.h"
#include <stb_image.h>

#include <math.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Cube.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;

double MouseX = 0;
double MouseY = 0;

int transfromUni;
int MousePosUni;
int textureUni;


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
	


	Cube cb;

	//------------LINK SHADER-------------

	Shader ourShader("Vertex.vert", "Fragment.frag");


	//---------------CREATE PROGRAM-------------
	ourShader.use();
	//----------VERTEX ATTRIBUTES---------
	//----------------UNIFORMS-------------
	
	transfromUni = glGetUniformLocation(ourShader.ID, "transform");
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


	glm::mat4 transformMatrix(1.0f);

	
	glm::mat4 viewMatrix(1.0f);
	viewMatrix = glm::lookAt(glm::vec3(1.0f, 1.0f, 5.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 projectionMatrix= glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
	transformMatrix = projectionMatrix * viewMatrix ;


	//projection view model

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		processInput(window);

		glm::vec3 translation(0.0f, 0.02f, 0.0f);
		cb.moveObject(&translation);
		glUniformMatrix4fv(transfromUni, 1, GL_FALSE, glm::value_ptr(transformMatrix * (*cb.modelMatrix)));
		cb.draw();

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



void processInput(GLFWwindow* window)
{
	
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	MouseX = xpos / WINDOW_WIDTH;
	MouseY = ypos / WINDOW_HEIGHT;
}
