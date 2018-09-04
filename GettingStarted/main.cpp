#define STB_IMAGE_IMPLEMENTATION

#include<iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

#include "game.h"
#include "camera.h"
#include "shader.h"
#include "texture.h"
#include "mouse_inputs.h"
#include "resource_manager.h"

Game breakout(800, 600);

/****************************\
	Function declarations
\****************************/

/**
Configures scene and initializes window */
GLFWwindow * initialize_window();

/**
Callback resizes viewport based on new window size */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/**
*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

/******************************\
	Function Definitions
\******************************/

int main()
{
	GLFWwindow * window = initialize_window();
	if (!window)
	{
		return -1;
	}

	//Projection Matrix: ViewSpace -> DeviceCoords
	//glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
		
	//Time between current frame and last frame
	float deltaTime = 0.0f;	
	//Time of last frame
	float lastFrame = 0.0f; 
	
	breakout.Init();
	breakout.State = GAME_ACTIVE;

	//Rendering loop
	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		// Manage user input
		breakout.ProcessInput(deltaTime);

		// Update Game state
		breakout.Update(deltaTime);

		//Clearing screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);			
		breakout.Render();

		glfwSwapBuffers(window);
	}

	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	glfwTerminate();
	return 0;
}

GLFWwindow * initialize_window()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Establishing a window and setting current context
	GLFWwindow * window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);

	//Initializign GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}

	//Default size of rendering window
	glViewport(0, 0, 800, 600);

	//Registering callback functions
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	
	return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			breakout.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			breakout.Keys[key] = GL_FALSE;
	}
}