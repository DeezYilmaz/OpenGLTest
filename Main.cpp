

#include "OpenGL_Libraries/Include/glad/glad.h"
#include "OpenGL_Libraries/Include/glfw3.h"
#include <iostream>
#include "Shader_s.h"

	#include <math.h>
	#include <glm/gtc/matrix_transform.hpp>
	#include <glm/gtc/type_ptr.hpp>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;

double MouseX = 0;
double MouseY = 0;



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

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	};


	//------------GENERATE VAO-----------
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	//------------------------------
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



	//------------LINK SHADER-------------

	Shader ourShader("Vertex.vs", "Fragment.f");


	//---------------CREATE PROGRAM-------------
	ourShader.use();
	//----------VERTEX ATTRIBUTES---------

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//----------------UNIFORMS-------------
	

	int MousePosUni = glGetUniformLocation(ourShader.ID, "MousePos");



	glEnable(GL_DEPTH_TEST);
	//-------------------------------
	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glUniform2f(MousePosUni, MouseX, MouseY);




		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.6f, 0.1f, 0.3f, 1.0f);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{


	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

	MouseX = xpos / WINDOW_WIDTH;
	MouseY = ypos / WINDOW_HEIGHT;
}
