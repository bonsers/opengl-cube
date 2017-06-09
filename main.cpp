#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

std::string VERTEXSOURCE =
"#version 330 core\n"
"layout (location = 0) in vec3 pos;\n"
"layout (location = 1) in vec3 color;\n"
"out vec3 fragmentColor;\n"
"uniform mat4 MODEL;\n"
"uniform mat4 VIEW;\n"
"uniform mat4 PROJECTION;\n"
"void main()\n"
"{\n"
"   gl_Position = PROJECTION * VIEW * MODEL * vec4(pos, 1.0);\n"
"   fragmentColor = color;\n"
"}";

std::string FRAGMENTSOURCE =
"#version 330 core\n"
"in vec3 fragmentColor;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"   color = vec4(fragmentColor, 1.0);\n"
"}";

GLfloat X = 0.0f;
GLfloat Y = 0.0f;
GLfloat Z = 0.0f;

int i = 0;
int j = 0;

bool RIGHT_KEY_FLAG = 0;
bool LEFT_KEY_FLAG = 0;
bool UP_KEY_FLAG = 0;
bool DOWN_KEY_FLAG = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
	const GLuint WIDTH = 800;
	const GLuint HEIGHT = 800;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "opengl-cube", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;
	glewInit();
	glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_DEPTH_TEST);

	Shader shader1(VERTEXSOURCE.c_str(), FRAGMENTSOURCE.c_str());

	// CUBE
	// To do: Introduce indexing so we can get rid of duplicate vertices

	GLfloat VERTICES[] = {
		-0.25f, -0.25f, -0.25f, 0.583f, 0.771f, 0.014f,
		-0.25f, -0.25f, 0.25f, 0.609f, 0.115f, 0.436f,
		-0.25f, 0.25f, 0.25f, 0.327f, 0.483f, 0.844f,
		0.25f, 0.25f, -0.25f, 0.822f, 0.569f, 0.201f,
		-0.25f, -0.25f, -0.25f, 0.435f, 0.602f, 0.223f,
		-0.25f, 0.25f, -0.25f, 0.310f, 0.747f, 0.185f,
		0.25f, -0.25f, 0.25f, 0.597f, 0.770f, 0.761f,
		-0.25f, -0.25f, -0.25f, 0.559f, 0.436f, 0.730f,
		0.25f, -0.25f, -0.25f, 0.359f, 0.583f, 0.152f,
		0.25f, 0.25f, -0.25f, 0.483f, 0.596f, 0.789f,
		0.25f, -0.25f, -0.25f, 0.559f, 0.861f, 0.639f,
		-0.25f, -0.25f, -0.25f, 0.195f, 0.548f, 0.859f,
		-0.25f, -0.25f, -0.25f, 0.014f, 0.184f, 0.576f,
		-0.25f, 0.25f, 0.25f, 0.771f, 0.328f, 0.970f,
		-0.25f, 0.25f, -0.25f, 0.406f, 0.615f, 0.116f,
		0.25f, -0.25f, 0.25f, 0.676f, 0.977f, 0.133f,
		-0.25f, -0.25f, 0.25f, 0.971f, 0.572f, 0.833f,
		-0.25f, -0.25f, -0.25f, 0.140f, 0.616f, 0.489f,
		-0.25f, 0.25f, 0.25f, 0.997f, 0.513f, 0.064f,
		-0.25f, -0.25f, 0.25f, 0.945f, 0.719f, 0.592f,
		0.25f, -0.25f, 0.25f, 0.543f, 0.021f, 0.978f,
		0.25f, 0.25f, 0.25f, 0.279f, 0.317f, 0.505f,
		0.25f, -0.25f, -0.25f, 0.167f, 0.620f, 0.077f,
		0.25f, 0.25f, -0.25f, 0.347f, 0.857f, 0.137f,
		0.25f, -0.25f, -0.25f, 0.055f, 0.953f, 0.042f,
		0.25f, 0.25f, 0.25f, 0.714f, 0.505f, 0.345f,
		0.25f, -0.25f, 0.25f, 0.783f, 0.290f, 0.734f,
		0.25f, 0.25f, 0.25f, 0.722f, 0.645f, 0.174f,
		0.25f, 0.25f, -0.25f, 0.302f, 0.455f, 0.848f,
		-0.25f, 0.25f, -0.25f, 0.225f, 0.587f, 0.040f,
		0.25f, 0.25f, 0.25f, 0.517f, 0.713f, 0.338f,
		-0.25f, 0.25f, -0.25f, 0.053f, 0.959f, 0.120f,
		-0.25f, 0.25f, 0.25f, 0.393f, 0.621f, 0.362f,
		0.25f, 0.25f, 0.25f, 0.673f, 0.211f, 0.457f,
		-0.25f, 0.25f, 0.25f, 0.820f, 0.883f, 0.371f,
		0.25f, -0.25f, 0.25f, 0.982f, 0.099f, 0.879f
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	glm::mat4 PROJECTION;
	PROJECTION = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(shader1.Program, "PROJECTION");




	// GAME LOOP
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader1.Use();

		// Create transformations
		glm::mat4 VIEW;

		VIEW = glm::translate(VIEW, glm::vec3(0.0f, 0.0f, -3.0f));

		// Get their uniform location
		GLint modelLoc = glGetUniformLocation(shader1.Program, "MODEL");
		GLint viewLoc = glGetUniformLocation(shader1.Program, "VIEW");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(VIEW));
		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(PROJECTION));

		glBindVertexArray(VAO);

		// Check arrow keys are down
		if (RIGHT_KEY_FLAG == 1)
		{
			i++;
		}
		if (DOWN_KEY_FLAG == 1)
		{
			j++;
		}
		if (LEFT_KEY_FLAG == 1)
		{
			i--;
		}
		if (UP_KEY_FLAG == 1)
		{
			j--;
		}

		glm::mat4 MODEL;
		GLfloat X_ANGLE = 5.0f * i;
		GLfloat Y_ANGLE = 5.0f * j;
		MODEL = glm::rotate(MODEL, glm::radians(X_ANGLE), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(MODEL, glm::radians(Y_ANGLE), glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(MODEL));

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	// Using boolean flag to create game-like rotation control
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		RIGHT_KEY_FLAG = 1;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
	{
		RIGHT_KEY_FLAG = 0;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		DOWN_KEY_FLAG = 1;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
	{
		DOWN_KEY_FLAG = 0;
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		UP_KEY_FLAG = 1;
	}
	if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
	{
		UP_KEY_FLAG = 0;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		LEFT_KEY_FLAG = 1;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
	{
		LEFT_KEY_FLAG = 0;
	}
}