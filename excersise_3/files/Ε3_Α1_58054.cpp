#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

#include "stb_image/stb_image.h"

Camera myCamera(glm::vec3(0.0f, 0.0f, 3.0f));

float deltaTime = 0.0f;
float currentFrameTime = 0.0f;
float previousFrameTime = 0.0f;

float previousMousePositonX = 400.0f;
float previousMousePositonY = 300.0f;

bool firstMouse = true;

bool last_state_1 = 0;
bool mode_1 = false;
bool last_state_2 = 0;
bool mode_2 = false;
bool last_state_3 = 0;
bool mode_3 = false;
bool last_state_4 = 0;
bool mode_4 = false;
bool last_state_5 = 0;
bool mode_5 = false;
int x = 1;

void FrameBufferSizeCallback(GLFWwindow* givenWindow, int givenWidth, int givenHeight)
{
	glViewport(0, 0, givenWidth, givenHeight);
}

void ProcessInput(GLFWwindow* givenWindow)
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

	//if (glfwGetKey(givenWindow, GLFW_KEY_E) == GLFW_PRESS)
	//	myCamera.ProcessKeyboard(UP, deltaTime);

	//if (glfwGetKey(givenWindow, GLFW_KEY_Q) == GLFW_PRESS)
	//	myCamera.ProcessKeyboard(DOWN, deltaTime);

	//1-KEY    
	bool state_1 = glfwGetKey(givenWindow, GLFW_KEY_1);
	if (last_state_1 != GLFW_PRESS && state_1 == GLFW_PRESS)//1 pressed.
	{
		if (mode_1 == false)
		{
			mode_1 = true;//Right.
		}
		else if (mode_1 == true)
		{
			mode_1 = false;//Left.
		}
	}
	last_state_1 = state_1;

	//2-KEY    
	bool state_2 = glfwGetKey(givenWindow, GLFW_KEY_2);
	if (last_state_2 != GLFW_PRESS && state_2 == GLFW_PRESS)//2 pressed.
	{
		if (mode_2 == false)
		{
			x += 1;
			mode_2 = true;
		}
		else if (mode_2 == true)
		{
			x += 1;
			mode_2 = false;
		}
	}
	last_state_2 = state_2;

	//3-KEY    
	bool state_3 = glfwGetKey(givenWindow, GLFW_KEY_3);
	if (last_state_3 != GLFW_PRESS && state_3 == GLFW_PRESS)//3 pressed.
	{
		if (mode_3 == false)
		{
			x -= 1;
			mode_3 = true;
		}
		else if (mode_3 == true)
		{
			x -= 1;
			mode_3 = false;
		}
		if (x<=0)
		{
			x = 1;
		}
	}
	last_state_3 = state_3;

	//4-KEY    
	bool state_4 = glfwGetKey(givenWindow, GLFW_KEY_4);
	if (last_state_4 != GLFW_PRESS && state_4 == GLFW_PRESS)//4 pressed.
	{
		if (mode_4 == false)
		{
			mode_4 = true;
		}
		else if (mode_4 == true)
		{
			mode_4 = false;
		}
	}
	last_state_4 = state_4;

	//5-KEY    
	bool state_5 = glfwGetKey(givenWindow, GLFW_KEY_5);
	if (last_state_5 != GLFW_PRESS && state_5 == GLFW_PRESS)//5 pressed.
	{
		if (mode_5 == false)
		{
			mode_5 = true;
		}
		else if (mode_5 == true)
		{
			mode_5 = false;
		}
	}
	last_state_5 = state_5;
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

	myCamera.ProcessMouseMovement(offsetX, offsetY);
}

void ScrollCallback(GLFWwindow* givenWindow, double givenScrollOffsetX, double givenScrollOffsetY)
{
	myCamera.ProcessMouseScroll(givenScrollOffsetY);
}

unsigned int GenerateTexture(const char* givenTextureFilePath)
{
	unsigned int textureId;
	glGenTextures(1, &textureId);

	int imageWidth, imageHeight, numberOfchannels;
	unsigned char* imageData;

	stbi_set_flip_vertically_on_load(true);
	imageData = stbi_load(givenTextureFilePath, &imageWidth, &imageHeight, &numberOfchannels, 0);

	int imageFormat = 3;

	if (numberOfchannels == 1)
		imageFormat = GL_RED;
	else if (numberOfchannels == 3)
		imageFormat = GL_RGB;
	else if (numberOfchannels == 4)
		imageFormat = GL_RGBA;

	if (imageData)
	{
		glBindTexture(GL_TEXTURE_2D, textureId);
		if (mode_4==true)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, imageWidth, imageHeight, 0, imageFormat, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
		std::cout << "Could not read the image!!!" << std::endl;

	stbi_image_free(imageData);
	return textureId;
}

unsigned int GenerateTexture2(const char* givenTextureFilePath)
{
	unsigned int textureId;
	glGenTextures(1, &textureId);

	int imageWidth, imageHeight, numberOfchannels;
	unsigned char* imageData;

	stbi_set_flip_vertically_on_load(true);
	imageData = stbi_load(givenTextureFilePath, &imageWidth, &imageHeight, &numberOfchannels, 0);

	int imageFormat = 3;

	if (numberOfchannels == 1)
		imageFormat = GL_RED;
	else if (numberOfchannels == 3)
		imageFormat = GL_RGB;
	else if (numberOfchannels == 4)
		imageFormat = GL_RGBA;

	if (imageData)
	{
		glBindTexture(GL_TEXTURE_2D, textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, imageWidth, imageHeight, 0, imageFormat, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
		std::cout << "Could not read the image!!!" << std::endl;

	stbi_image_free(imageData);
	return textureId;
}

int main()
{

	// Initialization

	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw!" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Excerise 3.1", NULL, NULL);

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
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	glm::vec3 cubePositions[] =
	{
	  glm::vec3(-2.0f,  0.0f,  0.0f),
	  glm::vec3(0.0f,  0.0f, 0.0f),
	  glm::vec3(2.0f, 0.0f, 0.0f),
	};

	// first buffer (vbo)
	unsigned int vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	Shader shaderProgram1("res/Shaders_58054/E3_A1_VertexShader1.txt", "res/Shaders_58054/E3_A1_FragmentShader1.txt");
	Shader shaderProgram2("res/Shaders_58054/E3_A1_VertexShader2.txt", "res/Shaders_58054/E3_A1_FragmentShader2.txt");
	Shader shaderProgram3("res/Shaders_58054/E3_A1_VertexShader1.txt", "res/Shaders_58054/E3_A1_FragmentShader3.txt");
	Shader lightSourceShaderProgram("res/Shaders_58054/LightSourceVertexShader.txt", "res/Shaders_58054/LightSourceFragmentShader.txt");

	glm::mat4 identity = glm::mat4(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	bool mode_key_1 = false;
	float dt = 0.0f;;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		unsigned int awesomefaceTextureId = GenerateTexture("res/Images/awesomeface.png");
		unsigned int containerTextureId = GenerateTexture("res/Images/container.jpg");
		unsigned int matrixTextureId = GenerateTexture2("res/Images/matrix.jpg");
		unsigned int container2TextureId = GenerateTexture("res/Images/container2.png");
		unsigned int container2SpecularTextureId = GenerateTexture("res/Images/container2_specular.png");

		float time = glfwGetTime();

		currentFrameTime = time;
		deltaTime = currentFrameTime - previousFrameTime;
		previousFrameTime = currentFrameTime;

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::vec3 lightSourceColor(1.0f, 1.0f, 1.0f);
		glm::vec3 lightSourcePosition(0.0f, 0.0f, 5.0f);
		glm::vec3 lightSourceDirection(0.0f, 0.0f, -1.0f); // only for directional light

		glm::mat4 model;
		glm::mat3 normalTransformation;
		glm::mat4 view;
		view = myCamera.GetViewMatrix(); // now we get the view matrix form the camrera class -------------
		glm::mat4 projection;
		// 3D
		projection = glm::perspective(glm::radians(myCamera.Zoom), 800.0f / 600.0f, 0.3f, 100.0f); // now we get the zoom form the camera class ---------------------

		///////////////////////////////////////////////////////////////////////////////////////////
		//Cube1
		shaderProgram1.use();
		if (mode_1 == true)
		{
			//Flip the face.
			mode_key_1 = true;
		}
		else
		{
			//Dont flip the face.
			mode_key_1 = false;
		}
		shaderProgram1.setBool("mode_key_1", mode_key_1);
		//std::cout << mode_key_1 << std::endl;

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, awesomefaceTextureId);
		shaderProgram1.setInt("material.awesomefaceTexture", 0);
		
		model = glm::translate(identity, cubePositions[0]);
		shaderProgram1.setMat4("model", model);
		normalTransformation = glm::transpose(glm::inverse(glm::mat3(model)));
		shaderProgram1.setMat3("normalTransformation", normalTransformation);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		shaderProgram1.setVec3("cameraPosition", myCamera.Position);
		shaderProgram1.setFloat("material.shininess", 128.0f * 2.0f);
		shaderProgram1.setVec3("lightSource.direction", lightSourceDirection); // only for directional light
		shaderProgram1.setVec3("lightSource.ambientColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shaderProgram1.setVec3("lightSource.diffuseColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shaderProgram1.setVec3("lightSource.specularColor", glm::vec3(1.0f, 1.0f, 1.0f));

		shaderProgram1.setMat4("view", view);
		shaderProgram1.setMat4("projection", projection);

		/////////////////////////////////////////////////////////////////////////////////////////////
		//Cube2
		shaderProgram2.use();
		shaderProgram2.setInt("x", x);
		//std::cout << x << std::endl;

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, containerTextureId);
		shaderProgram2.setInt("containerTexture", 1);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, awesomefaceTextureId);
		shaderProgram2.setInt("material.awesomefaceTexture", 2);
		
		model = identity;
		model = glm::translate(identity, cubePositions[1]);
		shaderProgram2.setMat4("model", model);
		//normalTransformation = identity;
		//glm::transpose(glm::inverse(glm::mat3(model)));
		normalTransformation = glm::transpose(glm::inverse(glm::mat3(model)));
		shaderProgram2.setMat3("normalTransformation", normalTransformation);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		shaderProgram2.setVec3("cameraPosition", myCamera.Position);
		shaderProgram2.setFloat("material.shininess", 128.0f * 2.0f);
		shaderProgram2.setVec3("lightSource.direction", lightSourceDirection); // only for directional light
		shaderProgram2.setVec3("lightSource.ambientColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shaderProgram2.setVec3("lightSource.diffuseColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shaderProgram2.setVec3("lightSource.specularColor", glm::vec3(1.0f, 1.0f, 1.0f));

		shaderProgram2.setMat4("view", view);
		shaderProgram2.setMat4("projection", projection);

		///////////////////////////////////////////////////////////////////////////////////////////////
		//Cube3
		shaderProgram3.use();

		if (mode_5 == true)
		{
			//Moving.
			dt += 0.02f;
		}
		else
		{
			//Not moving.
			dt += 0.0f;
		}
		shaderProgram3.setFloat("dt", dt);
		//std::cout << mode_5 << std::endl;


		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, container2TextureId);
		shaderProgram3.setInt("material.container2Texture", 3);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, container2SpecularTextureId);
		shaderProgram3.setInt("material.container2SpecularTexture", 4);
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, matrixTextureId);
		shaderProgram3.setInt("matrixTexture", 5);
		
		model = identity;
		model = glm::translate(identity, cubePositions[2]);
		shaderProgram3.setMat4("model", model);
		normalTransformation = glm::transpose(glm::inverse(glm::mat3(model)));
		shaderProgram3.setMat3("normalTransformation", normalTransformation);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		shaderProgram3.setVec3("cameraPosition", myCamera.Position);
		shaderProgram3.setFloat("material.shininess", 128.0f * 2.0f);
		shaderProgram3.setVec3("lightSource.direction", lightSourceDirection); // only for directional light
		shaderProgram3.setVec3("lightSource.ambientColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shaderProgram3.setVec3("lightSource.diffuseColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shaderProgram3.setVec3("lightSource.specularColor", glm::vec3(1.0f, 1.0f, 1.0f));

		shaderProgram3.setMat4("view", view);
		shaderProgram3.setMat4("projection", projection);

		////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////

		// Render Using the light source shader program
		lightSourceShaderProgram.use();

		lightSourceShaderProgram.setVec3("lightSourceColor", lightSourceColor);
		lightSourceShaderProgram.setMat4("view", view);
		lightSourceShaderProgram.setMat4("projection", projection);

		model=identity;
		model = glm::translate(identity, lightSourcePosition);
		lightSourceShaderProgram.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
