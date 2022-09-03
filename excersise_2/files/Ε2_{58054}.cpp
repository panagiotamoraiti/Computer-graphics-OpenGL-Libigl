#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <E2_Camera_{58054}.h>

Camera myCamera(glm::vec3(0.0f, 0.0f, 3.0f));

float deltaTime = 0.0f;
float currentFrameTime = 0.0f;
float previousFrameTime = 0.0f;

bool last_state_1 = false;
bool last_state_2 = false;
bool mode1 = false;
bool mode2 = false;

float previousMousePositonX = 400.0f;
float previousMousePositonY = 300.0f;

bool firstMouse = true;

void FrameBufferSizeCallback(GLFWwindow* givenWindow, int givenWidth, int givenHeight)
{
	glViewport(0, 0, givenWidth, givenHeight);
}

void ProcessInput(GLFWwindow* givenWindow)
{
	//Left Shift    
	if (glfwGetKey(givenWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		if (glfwGetKey(givenWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(givenWindow, true);

		if (glfwGetKey(givenWindow, GLFW_KEY_W) == GLFW_PRESS)
			myCamera.ProcessKeyboard(FORWARD, deltaTime * 4);

		if (glfwGetKey(givenWindow, GLFW_KEY_S) == GLFW_PRESS)
			myCamera.ProcessKeyboard(BACKWARD, deltaTime * 4);

		if (glfwGetKey(givenWindow, GLFW_KEY_A) == GLFW_PRESS)
			myCamera.ProcessKeyboard(LEFT, deltaTime * 4);

		if (glfwGetKey(givenWindow, GLFW_KEY_D) == GLFW_PRESS)
			myCamera.ProcessKeyboard(RIGHT, deltaTime * 4);

		if (glfwGetKey(givenWindow, GLFW_KEY_E) == GLFW_PRESS)
			myCamera.ProcessKeyboard(UP, deltaTime * 4);

		if (glfwGetKey(givenWindow, GLFW_KEY_Q) == GLFW_PRESS)
			myCamera.ProcessKeyboard(DOWN, deltaTime * 4);
	}
	else
	{
		if (glfwGetKey(givenWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(givenWindow, true);

		if (glfwGetKey(givenWindow, GLFW_KEY_W) == GLFW_PRESS)
			myCamera.ProcessKeyboard(FORWARD, deltaTime);

		if (glfwGetKey(givenWindow, GLFW_KEY_S) == GLFW_PRESS)
			myCamera.ProcessKeyboard(BACKWARD, deltaTime);

		if (glfwGetKey(givenWindow, GLFW_KEY_A) == GLFW_PRESS)
			myCamera.ProcessKeyboard(LEFT, deltaTime);

		if (glfwGetKey(givenWindow, GLFW_KEY_D) == GLFW_PRESS)
			myCamera.ProcessKeyboard(RIGHT, deltaTime);

		if (glfwGetKey(givenWindow, GLFW_KEY_E) == GLFW_PRESS)
			myCamera.ProcessKeyboard(UP, deltaTime);

		if (glfwGetKey(givenWindow, GLFW_KEY_Q) == GLFW_PRESS)
			myCamera.ProcessKeyboard(DOWN, deltaTime);
	}

	//1. //2.
	bool state_1 = glfwGetKey(givenWindow, GLFW_KEY_1);
	bool state_2 = glfwGetKey(givenWindow, GLFW_KEY_2);

	if (last_state_1 != GLFW_PRESS && state_1 == GLFW_PRESS)//1 pressed.
	{
		if (mode1 == false)
		{
			//Activate light sources.
			mode1 = true;
		}
		else if (mode1 == true)
		{
			//Deactivate light sources.
			mode1 = false;
		}
	}
	last_state_1 = state_1;

	if (last_state_2 != GLFW_PRESS && state_2 == GLFW_PRESS)//2 pressed.
	{
		if (mode2 == false)
		{
			//Activate light sources.
			mode2 = true;
		}
		else if (mode2 == true)
		{
			//Deactivate light sources.
			mode2 = false;
		}
	}
	last_state_2 = state_2;
}

void MousPositionCallback(GLFWwindow* givenWindow, double givenMousePositionX, double givenMousePositionY)
{
	//std::cout << givenMousePositionX << std::endl;
	//std::cout << givenMousePositionY << std::endl;

	if (firstMouse)
	{
		previousMousePositonX = givenMousePositionX;
		previousMousePositonY = givenMousePositionY;

		firstMouse = false;
	}

	float offsetX = givenMousePositionX - previousMousePositonX;
	float offsetY = previousMousePositonY - givenMousePositionY;
	previousMousePositonX = givenMousePositionX;
	previousMousePositonY = givenMousePositionY;

	////Left Shift    
	//if (glfwGetKey(givenWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	//{
	//	myCamera.ProcessMouseMovement(offsetX*4, offsetY*4);
	//}
	//else
	//{
	myCamera.ProcessMouseMovement(offsetX, offsetY);
	//}
	
}

void ScrollCallback(GLFWwindow* givenWindow, double givenScrollOffsetX, double givenScrollOffsetY)
{
	////Left Shift    
	//if (glfwGetKey(givenWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	//{
	//	myCamera.ProcessMouseScroll(givenScrollOffsetY*4);
	//}
	//else
	//{
	myCamera.ProcessMouseScroll(givenScrollOffsetY);
	//}
}

int main()
{
	//U = 58054 mod 5 = 4.
	// Initialization

	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw!" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Excersise 2", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to initialize the window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Set the callback function
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

	glfwSetCursorPosCallback(window, MousPositionCallback);

	glfwSetScrollCallback(window, ScrollCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize glew!" << std::endl;
		glfwTerminate();
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	//Data


	//--Vertex Data
	float vertices[] =
	{
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,


		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f

	};

	glm::vec3 cubePositions[] =
	{
	  glm::vec3(0.0f,  0.0f,  0.0f),
	  glm::vec3(2.0f,  5.0f, -15.0f),
	  glm::vec3(-1.5f, -2.2f, -2.5f),
	  glm::vec3(-3.8f, -2.0f, -12.3f),
	  glm::vec3(2.4f, -0.4f, -3.5f),
	  glm::vec3(-1.7f,  3.0f, -7.5f),
	  glm::vec3(1.3f, -2.0f, -2.5f),
	  glm::vec3(1.5f,  2.0f, -2.5f),
	  glm::vec3(1.5f,  0.2f, -1.5f),
	  glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::vec3 pointLightPositions[] = 
	{
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(0.0f, 0.0f, -3.0f)
	};

	glm::vec3 dirLightPositions[] =
	{
	glm::vec3(0.0f, 10.0f, -10.0f),
	glm::vec3(0.0f, -10.0f, -10.0f),
	glm::vec3(-10.0f, 10.0f, -10.0f)
	};

	//Materials
		//gold			
		//turquoise				
		//cyan plastic		
		//brass	
		//yellow rubber			
		//bronze			
		//ruby			
		//copper						
		//obsidian		
		//emerald			
	glm::vec3 ambient[10] =
	{
		glm::vec3(0.24725,0.1995,0.0745),
		glm::vec3(0.1,0.18725,0.1745),
		glm::vec3(0.0,0.1,0.06),
		glm::vec3(0.329412,0.223529,0.027451),
		glm::vec3(0.05,0.05,0.0),
		glm::vec3(0.2125,0.1275,0.054),
		glm::vec3(0.1745,0.01175,0.01175),
		glm::vec3(0.19125,0.0735,0.0225),
		glm::vec3(0.05375,0.05,0.06625),
		glm::vec3(0.0215,0.1745,0.0215)
	};
	glm::vec3 diffuse[10] =
	{
		glm::vec3(0.75164,0.60648,0.22648),
		glm::vec3(0.396,0.74151,0.69102),
		glm::vec3(0.0,0.50980392,0.50980392),
		glm::vec3(0.780392,0.568627,0.113725),
		glm::vec3(0.5,0.5,0.4),
		glm::vec3(0.714,0.4284,0.18144),
		glm::vec3(0.61424,0.04136,0.04136),
		glm::vec3(0.7038,0.27048,0.0828),
		glm::vec3(0.18275,0.17,0.22525),
		glm::vec3(0.07568,0.61424,0.07568)
	};
	glm::vec3 specular[10] =
	{
		glm::vec3(0.628281,0.555802,0.366065),
		glm::vec3(0.297254,0.30829,0.306678),
		glm::vec3(0.50196078,0.50196078,0.50196078),
		glm::vec3(0.992157,0.941176,0.807843),
		glm::vec3(0.7,0.7,0.04),
		glm::vec3(0.393548,0.271906,0.166721),
		glm::vec3(0.727811,0.626959,0.626959),
		glm::vec3(0.256777,0.137622,0.086014),
		glm::vec3(0.332741,0.328634,0.346435),
		glm::vec3(0.633,0.727811,0.633)
	};
	float shininess[10] = {0.4,0.1,0.25,0.21794872,0.078125,0.2,0.6,0.1,0.3,0.6};


	// first buffer (vbo)
	unsigned int vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	Shader shaderProgram("res/Shaders_{58054}/Å2_VertexShader.txt", "res/Shaders_{58054}/Å2_FragmentShader.txt");
	Shader lightSourceShaderProgram("res/Shaders_{58054}/E2_vertex_light.txt", "res/Shaders_{58054}/E2_fragment_light.txt");

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//glm::vec4 point = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	//glm::mat4 transform = glm::mat4(1.0f);
	//transform = glm::translate(transform, glm::vec3(2.0f, 1.0f, 0.0f));
	//point = transform * point;

	//std::cout << point.x << point.y << point.z << std::endl;

	glm::mat4 identity = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);

	// Game loop

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		float time = glfwGetTime();

		currentFrameTime = time;
		deltaTime = currentFrameTime - previousFrameTime;
		previousFrameTime = currentFrameTime;

		glm::vec3 new_light_source_position(5.0f * cos(time), 5.0f * sin(time), 0.0);

		//std::cout << deltaTime << std::endl;

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::vec3 lightSourceColor(1.0f, 1.0f, 1.0f);

		//Direction of the light sources.
		glm::vec3 lightSourceDirection3(0.0f, -1.0f, 0.0f); // only for directional light
		glm::vec3 lightSourceDirection4(0.0f, 1.0f, 0.0f); // only for directional light
		glm::vec3 lightSourceDirection5(1.0f, -1.0f, 0.0f); // only for directional light

		// Render Using the shader program
		shaderProgram.use();

		shaderProgram.setVec3("cameraPosition", myCamera.Position);

		//shaderProgram.setVec3("material.ambientColor", glm::vec3(0.0f, 0.1f, 0.06f));
		//shaderProgram.setVec3("material.diffuseColor", glm::vec3(0.0f, 0.51f, 0.51f));
		//shaderProgram.setVec3("material.specularColor", glm::vec3(0.51f, 0.51f, 0.51f));
		//shaderProgram.setFloat("material.shininess", 128.0f * 0.25f);

		// Light Sources
		if (mode1 == false)
		{	//Activate light sources.
			shaderProgram.setVec3("pointLights[0].position", pointLightPositions[0]);
			shaderProgram.setVec3("pointLights[0].ambientColor", glm::vec3(1.0f, 1.0f, 1.0f));
			shaderProgram.setVec3("pointLights[0].diffuseColor", glm::vec3(1.0f, 1.0f, 1.0f));
			shaderProgram.setVec3("pointLights[0].specularColor", glm::vec3(1.0f, 1.0f, 1.0f));
			shaderProgram.setFloat("pointLights[0].constant", 1.0f);
			shaderProgram.setFloat("pointLights[0].linear", 0.14f);
			shaderProgram.setFloat("pointLights[0].quadratic", 0.07f);

			shaderProgram.setVec3("pointLights[1].position", pointLightPositions[1]);
			shaderProgram.setVec3("pointLights[1].ambientColor", glm::vec3(1.0f, 1.0f, 1.0f));
			shaderProgram.setVec3("pointLights[1].diffuseColor", glm::vec3(1.0f, 1.0f, 1.0f));
			shaderProgram.setVec3("pointLights[1].specularColor", glm::vec3(1.0f, 1.0f, 1.0f));
			shaderProgram.setFloat("pointLights[1].constant", 1.0f);
			shaderProgram.setFloat("pointLights[1].linear", 0.14f);
			shaderProgram.setFloat("pointLights[1].quadratic", 0.07f);

			shaderProgram.setVec3("pointLights[2].position", new_light_source_position);
			shaderProgram.setVec3("pointLights[2].ambientColor", glm::vec3(1.0f, 1.0f, 1.0f));
			shaderProgram.setVec3("pointLights[2].diffuseColor", glm::vec3(1.0f, 1.0f, 1.0f));
			shaderProgram.setVec3("pointLights[2].specularColor", glm::vec3(1.0f, 1.0f, 1.0f));
			shaderProgram.setFloat("pointLights[2].constant", 1.0f);
			shaderProgram.setFloat("pointLights[2].linear", 0.14f);
			shaderProgram.setFloat("pointLights[2].quadratic", 0.07f);
		}
		else
		{	//Deactivate light sources.
			shaderProgram.setVec3("pointLights[0].position", pointLightPositions[0]);
			shaderProgram.setVec3("pointLights[0].ambientColor", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderProgram.setVec3("pointLights[0].diffuseColor", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderProgram.setVec3("pointLights[0].specularColor", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderProgram.setFloat("pointLights[0].constant", 1.0f);
			shaderProgram.setFloat("pointLights[0].linear", 0.14f);
			shaderProgram.setFloat("pointLights[0].quadratic", 0.07f);

			shaderProgram.setVec3("pointLights[1].position", pointLightPositions[1]);
			shaderProgram.setVec3("pointLights[1].ambientColor", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderProgram.setVec3("pointLights[1].diffuseColor", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderProgram.setVec3("pointLights[1].specularColor", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderProgram.setFloat("pointLights[1].constant", 1.0f);
			shaderProgram.setFloat("pointLights[1].linear", 0.14f);
			shaderProgram.setFloat("pointLights[1].quadratic", 0.07f);

			shaderProgram.setVec3("pointLights[2].position", new_light_source_position);
			shaderProgram.setVec3("pointLights[2].ambientColor", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderProgram.setVec3("pointLights[2].diffuseColor", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderProgram.setVec3("pointLights[2].specularColor", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderProgram.setFloat("pointLights[2].constant", 1.0f);
			shaderProgram.setFloat("pointLights[2].linear", 0.14f);
			shaderProgram.setFloat("pointLights[2].quadratic", 0.07f);
		}
		
		if (mode2 == false)
		{	//Activate light sources.
			shaderProgram.setVec3("dirLights[0].direction", lightSourceDirection3); // only for directional light
			shaderProgram.setVec3("dirLights[0].ambientColor", glm::vec3(1.0f, 1.0f, 1.0f));
			shaderProgram.setVec3("dirLights[0].diffuseColor", glm::vec3(1.0f, 1.0f, 1.0f));
			shaderProgram.setVec3("dirLights[0].specularColor", glm::vec3(1.0f, 1.0f, 1.0f));

			shaderProgram.setVec3("dirLights[1].direction", lightSourceDirection4); // only for directional light
			shaderProgram.setVec3("dirLights[1].ambientColor", glm::vec3(1.0f, 1.0f, 1.0f));
			shaderProgram.setVec3("dirLights[1].diffuseColor", glm::vec3(1.0f, 1.0f, 1.0f));
			shaderProgram.setVec3("dirLights[1].specularColor", glm::vec3(1.0f, 1.0f, 1.0f));

			shaderProgram.setVec3("dirLights[2].direction", lightSourceDirection5); // only for directional light
			shaderProgram.setVec3("dirLights[2].ambientColor", glm::vec3(1.0f, 1.0f, 1.0f));
			shaderProgram.setVec3("dirLights[2].diffuseColor", glm::vec3(1.0f, 1.0f, 1.0f));
			shaderProgram.setVec3("dirLights[2].specularColor", glm::vec3(1.0f, 1.0f, 1.0f));
		}
		else
		{	//Deactivate light sources.
			shaderProgram.setVec3("dirLights[0].direction", glm::vec3(1.0f, 1.0f, 1.0f)); // only for directional light
			shaderProgram.setVec3("dirLights[0].ambientColor", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderProgram.setVec3("dirLights[0].diffuseColor", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderProgram.setVec3("dirLights[0].specularColor", glm::vec3(0.0f, 0.0f, 0.0f));

			shaderProgram.setVec3("dirLights[1].direction", glm::vec3(1.0f, 1.0f, 1.0f)); // only for directional light
			shaderProgram.setVec3("dirLights[1].ambientColor", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderProgram.setVec3("dirLights[1].diffuseColor", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderProgram.setVec3("dirLights[1].specularColor", glm::vec3(0.0f, 0.0f, 0.0f));

			shaderProgram.setVec3("dirLights[2].direction", glm::vec3(1.0f, 1.0f, 1.0f)); // only for directional light
			shaderProgram.setVec3("dirLights[2].ambientColor", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderProgram.setVec3("dirLights[2].diffuseColor", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderProgram.setVec3("dirLights[2].specularColor", glm::vec3(0.0f, 0.0f, 0.0f));

		}
		
		glm::mat4 view;
		view = myCamera.GetViewMatrix(); // now we get the view matrix form the camrera class -------------
		shaderProgram.setMat4("view", view);
		glm::mat4 projection;

		// 3D
		projection = glm::perspective(glm::radians(myCamera.Zoom), 800.0f / 600.0f, 0.3f, 100.0f); // now we get the zoom form the camera class ---------------------

		shaderProgram.setMat4("projection", projection);

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model;

			model = glm::translate(identity, cubePositions[i]);
			model = glm::rotate(model, glm::radians(20.0f) * i, glm::vec3(1.0f, 0.3f, 0.5f));

			shaderProgram.setVec3("material.ambientColor", ambient[i]);
			shaderProgram.setVec3("material.diffuseColor", diffuse[i]);
			shaderProgram.setVec3("material.specularColor", specular[i]);
			shaderProgram.setFloat("material.shininess", shininess[i]*128.0);
			shaderProgram.setMat4("model", model);

			glm::mat3 normalTransformation = glm::transpose(glm::inverse(glm::mat3(model)));
			shaderProgram.setMat3("normalTransformation", normalTransformation);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// Render Using the light source shader program
		lightSourceShaderProgram.use();

		lightSourceShaderProgram.setVec3("lightSourceColor", lightSourceColor);
		lightSourceShaderProgram.setMat4("view", view);
		lightSourceShaderProgram.setMat4("projection", projection);

		glm::mat4 model = glm::translate(identity, pointLightPositions[0]);
		lightSourceShaderProgram.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::translate(identity, pointLightPositions[1]);
		lightSourceShaderProgram.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Lightsourse that rotates.
		model = glm::translate(identity, new_light_source_position);
		lightSourceShaderProgram.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(identity, dirLightPositions[0]);
		lightSourceShaderProgram.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::translate(identity, dirLightPositions[1]);
		lightSourceShaderProgram.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::translate(identity, dirLightPositions[2]);
		lightSourceShaderProgram.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}