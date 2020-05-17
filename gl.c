#define GLFW_INCLUDE_ES2
#include <GLFW/glfw3.h>


int
main (int argc,
      char **argv)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;


	window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);

	if (!window) {
		glfwTerminate();

		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}


	glfwTerminate();

	return 0;
}
