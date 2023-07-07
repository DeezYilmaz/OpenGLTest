

#include "OpenGL_Libraries/Include/glad/glad.h"
#include "OpenGL_Libraries/Include/glfw3.h"
#include <iostream>
#include "Shader_s.h"

#include <math.h>

#include <fstream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void updateRotation(float* angle, int rotationMatrixUNi);
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
		-0.25f,-0.25f,0.25f, 1.0f, 0.f, 0.f,
		 0.25f,-0.25f,0.25f, 1.0f, 0.f, 0.f,
		 0.25f, 0.25f,0.25f, 1.0f, 0.f, 0.f,


		-0.25f,-0.25f,0.25f, 1.0f, 0.f, 0.f,
		-0.25f,0.25f,0.25f,  1.0f, 0.f, 0.f,
		 0.25f, 0.25f,0.25f, 1.0f, 0.f, 0.f,

		
		

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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//----------------UNIFORMS-------------
	float angle = 0;

	int MousePosUni = glGetUniformLocation(ourShader.ID, "MousePos");

	
	int rotationMatrixUNi = glGetUniformLocation(ourShader.ID, "rotationMatrix");

	//-------------------------------
	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glUniform2f(MousePosUni, MouseX, MouseY);

		updateRotation(&angle, rotationMatrixUNi);
		

		glClearColor(0.6f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void updateRotation(float* angle, int rotationMatrixUNi) {
	*angle += 0.1f;
	float ZrotationMat[] = { cos(*angle),-sin(*angle),0,
						sin(*angle), cos(*angle),0,
						0,			0,		   1
	};
	float YrotationMat[] = { cos(*angle),0, sin(*angle),
							 0,			 1,     0,					
							 sin(*angle),0, cos(*angle),
	};

	glUniformMatrix3fv(rotationMatrixUNi, 1, true, YrotationMat);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		MouseX = 0.3f;
		MouseY = 0.2f;
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	
		MouseX = xpos / WINDOW_WIDTH;
		MouseY = ypos / WINDOW_HEIGHT;
}
