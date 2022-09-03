#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void FrameBufferSizeCallback1(GLFWwindow* givenWindow, int givenWidth, int givenHeight)
{
	glViewport(0, 0, givenWidth, givenHeight);
}

void ProcessInput1(GLFWwindow* givenWindow)
{
	if (glfwGetKey(givenWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(givenWindow, true);
}


int main()
{
	// Initialization

	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw!" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Excersise_2", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to initialize the window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Set the callback function
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback1);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize glew!" << std::endl;
		glfwTerminate();
		return -1;
	}

	GLfloat vertices[]
	{
		//Position			//Colour
		0.2f, 0.6f, 0.0f, 0.95f, 0.95f, 0.0f,
		0.5f, 0.9f, 0.0f, 0.95f, 0.95f, 0.0f,
		0.8f, 0.8f, 0.0f, 0.95f, 0.95f, 0.0f,
		0.9f, 0.6f, 0.0f, 0.95f, 0.95f, 0.0f,
		0.6f, 0.4f, 0.0f, 0.95f, 0.95f, 0.0f,
		0.8f, 0.3f, 0.0f, 0.95f, 0.95f, 0.0f,
		0.7f, -0.1f, 0.0f, 0.95f, 0.95f, 0.0f,
		0.3f, -0.2f, 0.0f, 0.95f, 0.95f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.95f, 0.95f, 0.0f
	};

	// first buffer (vbo)
	unsigned int vertexBufferId1;
	glGenBuffers(1, &vertexBufferId1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	Shader shaderProgram("res/Shaders_{58054}/E1_A2_VertexShader.txt", "res/Shaders_{58054}/E1_A2_FragmentShader.txt");

	// Initializing only once.
	glm::mat4 model = glm::mat4(1.0f);;
	bool last_state_UP = 0;
	bool last_state_DOWN = 0;
	bool last_state_RIGHT = 0;
	bool last_state_LEFT = 0;
	float position_x = 0.0f;
	float position_y = 0.0f;

	//float red=0.95;
	//float green=0.95;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput1(window);
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();

		// Render Using the shader program
		//glUseProgram(shaderProgramId);

		// Bind the first buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
		glEnableVertexAttribArray(0);
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));
		//glEnableVertexAttribArray(1);


		//Transformations

		//UP-DOWN-Right-Left
		bool state_UP = glfwGetKey(window, GLFW_KEY_W);
		bool state_DOWN = glfwGetKey(window, GLFW_KEY_S);
		bool state_RIGHT = glfwGetKey(window, GLFW_KEY_D);
		bool state_LEFT = glfwGetKey(window, GLFW_KEY_A);

		if (state_UP == GLFW_PRESS && last_state_UP != GLFW_PRESS)
		{
			if (position_y <= 0.0f)
			{
				position_y = position_y + 0.1f;
				model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
				//green = green + 0.05f;
			}
		}
		if (state_DOWN == GLFW_PRESS && last_state_DOWN != GLFW_PRESS)
		{
			if (position_y > -0.8f)
			{
				position_y = position_y - 0.1f;
				model = glm::translate(model, glm::vec3(0.0f, -0.1f, 0.0f));
				//green = green - 0.05f;
			}
		}
		if (state_RIGHT == GLFW_PRESS && last_state_RIGHT != GLFW_PRESS)
		{
			if (position_x <= 0.0f)
			{
				position_x = position_x + 0.1f;
				model = glm::translate(model, glm::vec3(0.1f, 0.0f, 0.0f));
				//red = red + 0.05f;
			}
		}
		if (state_LEFT == GLFW_PRESS && last_state_LEFT != GLFW_PRESS)
		{
			if (position_x > -1.0f)
			{
				position_x = position_x - 0.1f;
				model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 0.0f));
				//red = red - 0.05f;
			}
		}
		last_state_UP = state_UP;
		last_state_DOWN = state_DOWN;
		last_state_RIGHT = state_RIGHT;
		last_state_LEFT = state_LEFT;

		//We print the value.
		//std::cout << red << std::endl<< std::endl;
		//std::cout << green << std::endl << std::endl;

		int modelLocation = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);

		//Colour
		//int uniformLocation1 = glGetUniformLocation(shaderProgram.ID, "red");
		//glUniform1f(uniformLocation1, red);
		//int uniformLocation2 = glGetUniformLocation(shaderProgram.ID, "green");
		//glUniform1f(uniformLocation2, green);

		//Draw polygon
		glDrawArrays(GL_POLYGON, 0, 9);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
