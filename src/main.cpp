#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Gizmos.h"
#define GLM_SWIZZLE

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
int main()
{
	if (glfwInit() == false)
	{
		return -1;
	}

	GLFWwindow * window = glfwCreateWindow(300, 300, "window", nullptr, nullptr);

	if (window == nullptr)
	{
		return -2;
	}


	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}
	int major_version = ogl_GetMajorVersion();
	int minor_version = ogl_GetMinorVersion();
	printf("success %d.%d\n", major_version, minor_version);

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	Gizmos::create();
	mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0, 0, 0), vec3(0, 1, 0));

	mat4 projection = glm::perspective(glm::radians(60.0f), 300.0f/300.0f, 0.1f, 1000.0f);
	
	float camera_x = -10.0f;
	float camera_z = -10.0f;
	float timer = 0.0f;

	while (glfwWindowShouldClose(window) == false)
	{
		float dt = (float)glfwGetTime();
		glfwSetTime(0.0);
		timer += dt;
		camera_x = sinf(timer) * 10;
		camera_z = cosf(timer) * 10;
		mat4 view = glm::lookAt(vec3(camera_x, 10, camera_z), vec3(0, 0, 0), vec3(0, 1, 0));

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Gizmos::clear();
		Gizmos::addTransform(mat4(1));
		vec4 white(1);
		vec4 black(0, 0, 0, 1);
		for (int i = 0; i <= 20; i++)
		{
			Gizmos::addLine(vec3(-10 + i, 0, -10), vec3(-10 + i, 0, 10), i == 10 ? white : black);
			Gizmos::addLine(vec3(-10, 0, -10 + i), vec3(10 + i, 0, -10 + i), i == 10 ? white : black);
		}

		Gizmos::addSphere(vec3(0, 0, 0), 1.0f, 20.0f, 20.0f, white);

		Gizmos::draw(projection, view);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
};