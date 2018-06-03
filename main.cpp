#define NDEBUG

#pragma once

#include <iostream>
#include <GL\freeglut_std.h>
#include <string>
#include <conio.h>
#include <GLFW\glfw3.h>
#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>
#include "PhysicalVector.h"
#include "PhysicalShapeNode.h"
#include "Shape.h"

using namespace std;

void setLastFrameParameters(float* inPosition);
bool objectIsGoingUp(float thisY, float oldY);
bool objectIsGoingRight(float thisY, float oldY);
void applyBoundaries(Shape* inShape, float inCellRadius, float inRadius);
void introScreen(GLFWwindow* window);
void triangleDraw(float* verticies, float* colour);

// Define constant parameters 
const float gravityStrength = -0.01;
const float DEG2RAD = 3.14159 / 180;
const int windowWidth = 800;
const int windowHeight = 450;
const int cellRadius = 1;

// Define physical variables
float mass = 1.0;
float radius = 0.1;
float speed = 0.001;
float dragFactor = 0.3;
float accelerationFactor = 0.0008;
float x = -(cellRadius - radius) + 0.1;
float y = (cellRadius - radius) / 2.0;
float lastFrameX = x;
float lastFrameY = y;

// Define physical objects
PhysicalField gravity = PhysicalField(0.0, gravityStrength, 'G');

// Define game parameters
int frameWidth, frameHeight;
bool inIntroSequence = true;
char keyInput;

int main(int argc, char **argv) {

	cout << "Main Function Started." << endl;

	//GL initialisation
	glutInit(&argc, argv);
	if (!glfwInit()) exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	// Define GLFW window
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowWidth, "OpenGL Shape Game", NULL, NULL);

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	//DEFINE DYNAMIC TRIANGLE
	float movingTriangleVerticies[6];

	movingTriangleVerticies[0] = - 0.1 + x;
	movingTriangleVerticies[1] = + 0.1 + y;
	movingTriangleVerticies[2] = + 0.2 + x;
	movingTriangleVerticies[3] = + 0.1 + y;
	movingTriangleVerticies[4] = - 0.1 + x;
	movingTriangleVerticies[5] = - 0.2 + y;

	Shape movingTriangle = Shape(movingTriangleVerticies);

	//DEFINE STATIC TRIANGLE

	float triangleVerticies[6];
	triangleVerticies[0] = - 0.45 + 0.55;
	triangleVerticies[1] = + 0.25 + 0.45;
	triangleVerticies[2] = + 0.15 + 0.55;
	triangleVerticies[3] = + 0.25 + 0.45;
	triangleVerticies[4] = + 0.15 + 0.55;
	triangleVerticies[5] = - 0.75 + 0.45;

	float triangleColour[3] = {0.6, 0.6, 0.6};

	Shape triangle = Shape(triangleVerticies, triangleColour);

	while (!glfwWindowShouldClose(window)) {
		//Setup View
		glfwGetFramebufferSize(window, &frameWidth, &frameHeight);
		glViewport(0, 0, frameWidth, frameHeight);
		glClear(GL_COLOR_BUFFER_BIT);

		//Intro Screen
		if (inIntroSequence) introScreen(window);

		//Movement Loop
		if (!inIntroSequence) {
			applyBoundaries(&movingTriangle, cellRadius, radius);

			//Update function based on keyboard input
			if (_kbhit()) {
				keyInput = _getch();
			}
			if (keyInput == 'w' || keyInput == 'a' || keyInput == 's' || keyInput == 'd') {
				movingTriangle.updateStateWASDToVelocity(keyInput, accelerationFactor);
			}
			else if (keyInput == 'q') {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
			else movingTriangle.updateState();

			triangle.testBounceBoundaries(movingTriangle.getPosition().getX(), movingTriangle.getPosition().getY(), &movingTriangle);
			
			// Draw functions

			//Draw triangles
			triangleDraw(movingTriangle.getVerticies(), movingTriangle.getColour());
			triangleDraw(triangle.getVerticies(), triangle.getColour());

			glBegin(GL_POLYGON);

			for (int i = 0; i < 360; i++) {
				float degInRad = i * DEG2RAD;
				glColor3f(0.3, 0.3, 0.3);
				glVertex2f((cos(degInRad)*radius) + movingTriangle.getPosition().getX(), (sin(degInRad)*radius) + movingTriangle.getPosition().getY());
			}

			glEnd();

		}

		setLastFrameParameters(movingTriangle.getPosition().getVector());

		//Swap buffer and check for events
		keyInput = NULL;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate;
	exit(EXIT_SUCCESS);
}

void setLastFrameParameters(float* inPosition) {
	lastFrameX = *inPosition;
	lastFrameX = *(inPosition + 1);
}

bool objectIsGoingRight(float thisX, float oldX) {
	if (thisX - oldX > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool objectIsGoingUp(float thisY, float oldY) {
	if (thisY - oldY > 0) {
		return true;
	}
	else {
		return false;
	}
}

void applyBoundaries(Shape* inShape, float inCellRadius, float inRadius) {
	if (inShape->getPosition().getX() < -(inCellRadius - inRadius) && !inShape->isMovingRight()) {
		inShape->flipVelocityX();
	}

	if (inShape->getPosition().getX() > (inCellRadius - inRadius) && inShape->isMovingRight()) {
		inShape->flipVelocityX();
	}

	if (inShape->getPosition().getY() < -(inCellRadius - inRadius) && !inShape->isMovingUp()) {
		inShape->flipVelocityY();
	}

	if (inShape->getPosition().getY() > (inCellRadius - inRadius) && inShape->isMovingUp()) {
		inShape->flipVelocityY();
	}
}

void introScreen(GLFWwindow* window) {

	char keyInput;
	int l, i;

	char textToScreen[] = "Welcome, please press space to start or q to exit";

	char* st = textToScreen;

	l = strlen(st); // see how many characters are in text string.

	int textToScreenLength = 0;

	//float indent = ((-1 * textToScreenLength) / (2 * GLUT_WINDOW_WIDTH));

	glRasterPos2f(-0.7, 0.6); // location to start printing text

	for (i = 0; i < l; i++) // loop until i is greater then l
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)st[i]); // Print a character on the screen
	}

	if (_kbhit()) {
		keyInput = _getch();
		if ((int)keyInput == 32) inIntroSequence = false;
		else if (keyInput == 'q') glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void triangleDraw(float* inVerticies, float* inColour) {

	glColor3f(inColour[0], inColour[1], inColour[2]);

	//glColor3f(0.2, 0.4, 0.5);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, inVerticies);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
	glDisableClientState(GL_VERTEX_ARRAY);
}

/**
Ball Code - START

glBegin(GL_POLYGON);

for (int i = 0; i < 360; i++) {
	float degInRad = i * DEG2RAD;
	glColor3f(colours[0], colours[1], colours[2]);
	glVertex2f((cos(degInRad)*radius) + ball.getPosition().getX(), (sin(degInRad)*radius) + ball.getPosition().getY());
}

glEnd();

Ball Code - END 
**/

/**
void flipColours();
**/

/**
void flipColours() {
for (float& colour : colours)
colour = 1 - colour;
}
**/

/**
cout << "Moving triangle X is: " << (int)(movingTriangle.Shape::getGeoX() * 100) <<
"Moving triagle Y is: " << (int)(movingTriangle.Shape::getGeoY() * 100) << endl;
**/

//ball.updateStateWASDToVelocity(keyInput, accelerationFactor);
//else ball.updateState();
//triangle.Shape::testBoundaries(ball.getPosition().getX(), ball.getPosition().getY());