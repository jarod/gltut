
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <cstring>
#include <glload/gl_3_3.h>
#include <glload/gl_load.hpp>
#include <glutil/Shader.h>
#include <GLFW/glfw3.h>
#include "framework.h"
#include "directories.h"

#ifdef LOAD_X11
#define APIENTRY
#endif

namespace Framework {

	GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename) {
		std::string strFilename = FindFileOrThrow(strShaderFilename);
		std::ifstream shaderFile(strFilename.c_str());
		std::stringstream shaderData;
		shaderData << shaderFile.rdbuf();
		shaderFile.close();

		try {
			return glutil::CompileShader(eShaderType, shaderData.str());
		} catch(std::exception &e) {
			fprintf(stderr, "%s\n", e.what());
			throw;
		}
	}

	GLuint CreateProgram(const std::vector<GLuint> &shaderList) {
		try {
			GLuint prog = glutil::LinkProgram(shaderList);
            std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
			return prog;
		} catch(std::exception &e) {
            std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
			fprintf(stderr, "%s\n", e.what());
			throw;
		}
	}

	float DegToRad(float fAngDeg) {
		const float fDegToRad = 3.14159f * 2.0f / 360.0f;
		return fAngDeg * fDegToRad;
	}

	std::string FindFileOrThrow( const std::string &strBasename ) {
		std::string strFilename = LOCAL_FILE_DIR + strBasename;
		std::ifstream testFile(strFilename.c_str());
		if(testFile.is_open())
			return strFilename;

		
		strFilename = GLOBAL_FILE_DIR + strBasename;
		testFile.open(strFilename.c_str());
		if(testFile.is_open())
			return strFilename;

		throw std::runtime_error("Could not find the file " + strBasename);
	}
}

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init();
//Called to update the display.
void display();
//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape(GLFWwindow *window, int w, int h);
//Called whenever a key on the keyboard was pressed.
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);

void APIENTRY DebugFunc(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
			   const GLchar* message, const GLvoid* userParam) {
	std::string srcName;
	switch(source) {
    case GL_DEBUG_SOURCE_API_ARB: srcName = "API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB: srcName = "Window System"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB: srcName = "Shader Compiler"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY_ARB: srcName = "Third Party"; break;
    case GL_DEBUG_SOURCE_APPLICATION_ARB: srcName = "Application"; break;
    case GL_DEBUG_SOURCE_OTHER_ARB: srcName = "Other"; break;
	}

	std::string errorType;
	switch(type) {
	case GL_DEBUG_TYPE_ERROR_ARB: errorType = "Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB: errorType = "Deprecated Functionality"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB: errorType = "Undefined Behavior"; break;
	case GL_DEBUG_TYPE_PORTABILITY_ARB: errorType = "Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE_ARB: errorType = "Performance"; break;
	case GL_DEBUG_TYPE_OTHER_ARB: errorType = "Other"; break;
	}

	std::string typeSeverity;
	switch(severity) {
	case GL_DEBUG_SEVERITY_HIGH_ARB: typeSeverity = "High"; break;
	case GL_DEBUG_SEVERITY_MEDIUM_ARB: typeSeverity = "Medium"; break;
	case GL_DEBUG_SEVERITY_LOW_ARB: typeSeverity = "Low"; break;
	}

	printf("%s from %s,\t%s priority\nMessage: %s\n",
		errorType.c_str(), srcName.c_str(), typeSeverity.c_str(), message);
}

int main(int argc, char *argv[]) {
	if (!glfwInit()) {
		printf("glfwInit failed!\n");
		return EXIT_FAILURE;
	}

	int width = 500;
	int height = 500;
	GLFWwindow *window;
	window = glfwCreateWindow(width, height, argv[0], nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);

	GLFWframebuffersizefun(reshape);
	glfwSetKeyCallback(window, keyboard);

	glload::LoadFunctions();

	if(!glload::IsVersionGEQ(3, 3)) {
		printf("Your OpenGL version is %i, %i. You must have at least OpenGL 3.3 to run this tutorial.\n",
			glload::GetMajorVersion(), glload::GetMinorVersion());
		glfwDestroyWindow(window);
		return 0;
	}

	if(glext_ARB_debug_output) {
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		glDebugMessageCallbackARB(DebugFunc, (void*)15);
	}

	init();

	while(!glfwWindowShouldClose(window)) {
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return EXIT_SUCCESS;
}
