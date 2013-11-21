#include <string>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <glload/gl_3_3.h>
#include <GLFW/glfw3.h>
#include "../framework/framework.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

GLuint theProgram;

GLuint modelToCameraMatrixUnif;
GLuint cameraToClipMatrixUnif;

glm::mat4 cameraToClipMatrix(0.0f);

float CalcFrustumScale(float fFovDeg) {
	const float degToRad = 3.14159f * 2.0f / 360.0f;
	float fFovRad = fFovDeg * degToRad;
	return 1.0f / tan(fFovRad / 2.0f);
}

const float fFrustumScale = CalcFrustumScale(45.0f);

void InitializeProgram() {
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "PosColorLocalTransform.vert"));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "ColorPassthrough.frag"));

	theProgram = Framework::CreateProgram(shaderList);

	modelToCameraMatrixUnif = glGetUniformLocation(theProgram, "modelToCameraMatrix");
	cameraToClipMatrixUnif = glGetUniformLocation(theProgram, "cameraToClipMatrix");

	float fzNear = 1.0f; float fzFar = 61.0f;

	cameraToClipMatrix[0].x = fFrustumScale;
	cameraToClipMatrix[1].y = fFrustumScale;
	cameraToClipMatrix[2].z = (fzFar + fzNear) / (fzNear - fzFar);
	cameraToClipMatrix[2].w = -1.0f;
	cameraToClipMatrix[3].z = (2 * fzFar * fzNear) / (fzNear - fzFar);

	glUseProgram(theProgram);
	glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(cameraToClipMatrix));
	glUseProgram(0);
}

const int numberOfVertices = 8;

#define GREEN_COLOR 0.0f, 1.0f, 0.0f, 1.0f
#define BLUE_COLOR 	0.0f, 0.0f, 1.0f, 1.0f
#define RED_COLOR 1.0f, 0.0f, 0.0f, 1.0f
#define GREY_COLOR 0.8f, 0.8f, 0.8f, 1.0f
#define BROWN_COLOR 0.5f, 0.5f, 0.0f, 1.0f

const float vertexData[] = {
	+1.0f, +1.0f, +1.0f,
	-1.0f, -1.0f, +1.0f,
	-1.0f, +1.0f, -1.0f,
	+1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	+1.0f, +1.0f, -1.0f,
	+1.0f, -1.0f, +1.0f,
	-1.0f, +1.0f, +1.0f,

	GREEN_COLOR,
	BLUE_COLOR,
	RED_COLOR,
	BROWN_COLOR,

	GREEN_COLOR,
	BLUE_COLOR,
	RED_COLOR,
	BROWN_COLOR,
};

const GLshort indexData[] = {
	0, 1, 2,
	1, 0, 3,
	2, 3, 0,
	3, 2, 1,

	5, 4, 6,
	4, 5, 7,
	7, 6, 4,
	6, 7, 5,
};

GLuint vertexBufferObject;
GLuint indexBufferObject;
GLuint vao;


void InitializeVertexBuffer() {
	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBufferObject);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

float CalcLerpFactor(float fElapsedTime, float fLoopDuration) {
	float fValue = fmodf(fElapsedTime, fLoopDuration) / fLoopDuration;
	if(fValue > 0.5f)
		fValue = 1.0f - fValue;

	return fValue * 2.0f;
}

glm::vec3 NullScale(float fElapsedTime) {
	return glm::vec3(1.0f, 1.0f, 1.0f);
}

glm::vec3 StaticUniformScale(float fElapsedTime) {
	return glm::vec3(4.0f, 4.0f, 4.0f);
}

glm::vec3 StaticNonUniformScale(float fElapsedTime) {
	return glm::vec3(0.5f, 1.0f, 10.0f);
}

glm::vec3 DynamicUniformScale(float fElapsedTime) {
	const float fLoopDuration = 3.0f;

	return glm::vec3(glm::mix(1.0f, 4.0f, CalcLerpFactor(fElapsedTime, fLoopDuration)));
}

glm::vec3 DynamicNonUniformScale(float fElapsedTime) {
	const float fXLoopDuration = 3.0f;
	const float fZLoopDuration = 5.0f;

	return glm::vec3(glm::mix(1.0f, 0.5f, CalcLerpFactor(fElapsedTime, fXLoopDuration)),
		1.0f,
		glm::mix(1.0f, 10.0f, CalcLerpFactor(fElapsedTime, fZLoopDuration)));
}

struct Instance {
	typedef glm::vec3(*ScaleFunc)(float);

	ScaleFunc CalcScale;
	glm::vec3 offset;

	glm::mat4 ConstructMatrix(float fElapsedTime) {
		glm::vec3 theScale = CalcScale(fElapsedTime);
		glm::mat4 theMat(1.0f);
		theMat[0].x = theScale.x;
		theMat[1].y = theScale.y;
		theMat[2].z = theScale.z;
		theMat[3] = glm::vec4(offset, 1.0f);

		return theMat;
	}
};

Instance g_instanceList[] = {
	{NullScale,					glm::vec3(0.0f, 0.0f, -45.0f)},
	{StaticUniformScale,		glm::vec3(-10.0f, -10.0f, -45.0f)},
	{StaticNonUniformScale,		glm::vec3(-10.0f, 10.0f, -45.0f)},
	{DynamicUniformScale,		glm::vec3(10.0f, 10.0f, -45.0f)},
	{DynamicNonUniformScale,	glm::vec3(10.0f, -10.0f, -45.0f)},
};

void init() {
	InitializeProgram();
	InitializeVertexBuffer();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	size_t colorDataOffset = sizeof(float) * 3 * numberOfVertices;
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorDataOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);

	glBindVertexArray(0);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
}

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(theProgram);

	glBindVertexArray(vao);

	float fElapsedTime = glfwGetTime();
	for(int iLoop = 0; iLoop < ARRAY_COUNT(g_instanceList); iLoop++) {
		Instance &currInst = g_instanceList[iLoop];
		const glm::mat4 &transformMatrix = currInst.ConstructMatrix(fElapsedTime);

		glUniformMatrix4fv(modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0);
	}

	glBindVertexArray(0);
	glUseProgram(0);
}

void reshape (GLFWwindow* window, int w, int h) {
	cameraToClipMatrix[0].x = fFrustumScale * (h / (float)w);
	cameraToClipMatrix[1].y = fFrustumScale;

	glUseProgram(theProgram);
	glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(cameraToClipMatrix));
	glUseProgram(0);

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
	switch (key) {
	  case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, 1);
		return;
	}
}
