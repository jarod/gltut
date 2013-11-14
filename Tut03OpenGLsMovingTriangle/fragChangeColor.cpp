
#include <string>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <glload/gl_3_3.h>
#include <GLFW/glfw3.h>
#include "../framework/framework.h"

GLuint theProgram;
GLuint elapsedTimeUniform;

void InitializeProgram() {
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "calcOffset.vert"));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "calcColor.frag"));

	theProgram = Framework::CreateProgram(shaderList);

	elapsedTimeUniform = glGetUniformLocation(theProgram, "time");

	GLuint loopDurationUnf = glGetUniformLocation(theProgram, "loopDuration");
	GLuint fragLoopDurUnf = glGetUniformLocation(theProgram, "fragLoopDuration");


	glUseProgram(theProgram);
	glUniform1f(loopDurationUnf, 5.0f);
	glUniform1f(fragLoopDurUnf, 10.0f);
	glUseProgram(0);
}

const float vertexPositions[] = {
	0.25f, 0.25f, 0.0f, 1.0f,
	0.25f, -0.25f, 0.0f, 1.0f,
	-0.25f, -0.25f, 0.0f, 1.0f,
};

GLuint positionBufferObject;
GLuint vao;


void InitializeVertexBuffer() {
	glGenBuffers(1, &positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STREAM_DRAW);
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

	glUniform1f(elapsedTimeUniform, static_cast<float>(glfwGetTime()));

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
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
