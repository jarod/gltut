
#include <string>
#include <vector>
#include <cmath>
#include <cstdio>
#include <glload/gl_3_3.h>
#include <GLFW/glfw3.h>
#include "../framework/framework.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))


GLuint theProgram;
GLuint elapsedTimeUniform;

void InitializeProgram() {
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "FragPosition.vert"));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "FragPosition.frag"));

	theProgram = Framework::CreateProgram(shaderList);
}

const float vertexData[] = {
	0.75f, 0.75f, 0.0f, 1.0f,
	0.75f, -0.75f, 0.0f, 1.0f,
	-0.75f, -0.75f, 0.0f, 1.0f,
};

GLuint vertexBufferObject;
GLuint vao;


void InitializeVertexBuffer() {
	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void init() {
	InitializeProgram();
	InitializeVertexBuffer();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(theProgram);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glUseProgram(0);
}

void reshape (GLFWwindow* window, int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
	switch (key) {
	  case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, 1);
		return;
	}
}
