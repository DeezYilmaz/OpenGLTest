

#include "OpenGL_Libraries/Include/glad/glad.h"
#include "OpenGL_Libraries/Include/glfw3.h"
#include <iostream>
#include "Shader_s.h"
#include <stb_image.h>

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

int transfromUni;
int MousePosUni;
int textureUni;

glm::mat4 trans = glm::mat4(1.0f);
glm::mat4 pers;
glm::mat4 rotat;

glm::mat4 result;
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
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	
	//------------GENERATE VAO-----------
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	//------------GENERATE VBO-----------
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	

	////-----------GENERATE EBO------------
	/*unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/


	//------------LINK SHADER-------------

	Shader ourShader("Vertex.vert", "Fragment.frag");


	//---------------CREATE PROGRAM-------------
	ourShader.use();
	//----------VERTEX ATTRIBUTES---------

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//----------------UNIFORMS-------------
	
	transfromUni = glGetUniformLocation(ourShader.ID, "transform");
	MousePosUni = glGetUniformLocation(ourShader.ID, "MousePos");
	textureUni = glGetUniformLocation(ourShader.ID, "ourTexture");

	//----------------GENERATE TEXTURE---------------


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
	//-------------------------------

	glEnable(GL_DEPTH_TEST);



	pers = glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 100.f);
	result = pers;
	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		processInput(window);
		
		

		glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,0);
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


glm::mat4 matPT=pers;

void processInput(GLFWwindow* window)
{
	float speed = 5;
	bool moved = false;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		trans = glm::translate(trans, glm::vec3(0.f, 0.f, -0.1f));
		moved = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		trans = glm::translate(trans, glm::vec3(0.f, 0.f, 0.1f));
		moved = true;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		trans = glm::translate(trans, glm::vec3(-0.1f, 0.f, 0.f));
		moved = true;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		trans = glm::translate(trans, glm::vec3(0.1f, 0.f, 0.f));
		moved = true;
	}
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
	rotat = glm::rotate(trans, glm::radians(-(0.5f - (float)MouseX) * 30), glm::vec3(0.0, 1.0, 0.0));
	rotat = glm::rotate(rotat, glm::radians(-(0.5f - (float)MouseY) * 30), glm::vec3(1.0, 0.0, 0.0));

	if (moved) {
		matPT = pers * trans;
	}
	result = matPT * rotat;


	glUniform2f(MousePosUni, MouseX, MouseY);
	glUniformMatrix4fv(transfromUni, 1, GL_FALSE, glm::value_ptr(result));

}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	MouseX = xpos / WINDOW_WIDTH;
	MouseY = ypos / WINDOW_HEIGHT;
}
