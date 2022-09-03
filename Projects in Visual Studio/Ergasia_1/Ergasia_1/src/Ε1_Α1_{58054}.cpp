/*#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shader.h>

void FrameBufferSizeCallback(GLFWwindow* givenWindow, int givenWidth, int givenHeight)
{
	glViewport(0, 0, givenWidth, givenHeight);
}

void ProcessInput(GLFWwindow* givenWindow)
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

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Excersise_1", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to initialize the window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Set the callback function
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize glew!" << std::endl;
		glfwTerminate();
		return -1;
	}

	GLfloat vertices1[] =
	{
			//Position		//Colour
		-0.5f, 0.5f, 0.0f, 1.0, 0.0, 0.0,
		-0.3f, 0.3f, 0.0f, 1.0, 0.0, 0.0,
		-0.3f, -0.3f, 0.0f, 1.0, 0.0, 0.0,
		-0.6f, -0.4f, 0.0f, 1.0, 0.0, 0.0,
		-0.65f, 0.3f, 0.0f, 1.0, 0.0, 0.0
	};

	GLfloat vertices2[]
	{
			//Position		//Colour
		0.2f, 0.6f, 0.0f, 1.0, 1.0, 0.0,
		0.5f, 0.9f, 0.0f, 1.0, 1.0, 0.0,
		0.8f, 0.8f, 0.0f, 1.0, 1.0, 0.0,
		0.9f, 0.6f, 0.0f, 1.0, 1.0, 0.0,
		0.6f,  0.4f, 0.0f, 1.0, 1.0, 0.0,
		0.8f,  0.3f, 0.0f, 1.0, 1.0, 0.0,
		0.7f, -0.1f, 0.0f, 1.0, 1.0, 0.0,
		0.3f, -0.2f, 0.0f, 1.0, 1.0, 0.0,
		0.0f, 0.0f, 0.0f, 1.0, 1.0, 0.0
	};

	// first buffer (vbo)
	unsigned int vertexBufferId1;
	glGenBuffers(1, &vertexBufferId1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
	//glEnableVertexAttribArray(0);

	// second buffer (vbo)
	unsigned int vertexBufferId2;
	glGenBuffers(1, &vertexBufferId2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
	//glEnableVertexAttribArray(0);

	Shader shaderProgram("res/Shaders_{58054}/E1_A1_VertexShader.txt", "res/Shaders_{58054}/E1_A1_FragmentShader.txt");

	//Initializing only once.
	float intensity = 0.5f;
	bool last_state_W=0;
	bool mode=false;//Default mode.
	bool last_state_UP = 0;
	bool last_state_DOWN = 0;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();

		// Render Using the shader program
		//glUseProgram(shaderProgramId);

		// Bind the first buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
		glEnableVertexAttribArray(0);
		
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glDrawArrays(GL_POLYGON, 0, 5);

		// Bind the second buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId2);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
		glEnableVertexAttribArray(0);

		//Colour
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glDrawArrays(GL_POLYGON, 0, 9);

		int uniformLocation = glGetUniformLocation(shaderProgram.ID, "intensity");
		glUniform1f(uniformLocation, intensity);
		
		//UP-DOWN
		bool state_UP = glfwGetKey(window, GLFW_KEY_UP);
		bool state_DOWN = glfwGetKey(window, GLFW_KEY_DOWN);
		if (state_UP == GLFW_PRESS && last_state_UP != GLFW_PRESS)
		{
			if (intensity < 1.0f)
			{
				intensity = intensity + 0.1f;
			}
		}
		if (state_DOWN == GLFW_PRESS && last_state_DOWN != GLFW_PRESS)
		{
			if (intensity >= 0.1f)
			{
				intensity = intensity - 0.1f;
			}
		}
		last_state_UP = state_UP;
		last_state_DOWN = state_DOWN;
		//We print the value.
	    //std::cout << intensity << std::endl<< std::endl;

		//W-KEY    
		bool state_W = glfwGetKey(window, GLFW_KEY_W);
		//bool mode;//Default mode->false
	
		if (last_state_W != GLFW_PRESS && state_W == GLFW_PRESS)//W pressed.
		{
			if (mode == false)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//Wireframe mode.
				mode = true;//Wireframe mode.
			}
			else if(mode==true)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//Default mode.
				mode = false;//Default mode.
			}
		}
		last_state_W = state_W;
		//We print the value.
		//std::cout << mode << std::endl;
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}*/