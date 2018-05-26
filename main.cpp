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
#include "PhysicalShapeNode.h"
#include "Shape.h"

using namespace std;

void setLastFrameParameters(float argx, float argy);
bool objectIsGoingUp(float thisY, float oldY);
bool objectIsGoingRight(float thisY, float oldY);
void applyBoundaries(PhysicalShapeNode inBall, float inCellRadius, float inRadius);
void introScreen(GLFWwindow* window);
void triangleDraw(float* verticies, float* colour);

const float gravityStrength = -0.01;
const float DEG2RAD = 3.14159 / 180;
const int windowWidth = 800;
const int windowHeight = 450;
const int cellRadius = 1;

float mass = 1.0;
float radius = 0.1;
float speed = 0.001;
float dragFactor = 0.3;
float accelerationFactor = 0.0008;

bool inIntroSequence = true;

float x = -(cellRadius - radius) + 0.1;
float y = (cellRadius - radius) / 2.0;
float lastFrameX = x;
float lastFrameY = y;

PhysicalShapeNode ball = PhysicalShapeNode(PhysicalVector(x, y), PhysicalVector(speed, 0.0), mass);
PhysicalField gravity = PhysicalField(0.0, gravityStrength, 'G');

int main(int argc, char **argv) {

	glutInit(&argc, argv);

	cout << "Main Function Started." << endl;

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowWidth, "OpenGL Shape Game", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	bool ballLeft = true;
	bool ballDown = true;

	//DEFINE DYNAMIC TRIANGLE
	float movingTriangleVerticies[6];

	movingTriangleVerticies[0] = - 0.1;
	movingTriangleVerticies[1] = + 0.1;
	movingTriangleVerticies[2] = + 0.2;
	movingTriangleVerticies[3] = + 0.1;
	movingTriangleVerticies[4] = - 0.1;
	movingTriangleVerticies[5] = - 0.2;

	Shape movingTriangle = Shape(ball.getPosition().getVector(), movingTriangleVerticies);

	//DEFINE STATIC TRIANGLE

	float triangleVerticies[6];
	triangleVerticies[0] = - 0.45;
	triangleVerticies[1] = + 0.05;
	triangleVerticies[2] = + 0.15;
	triangleVerticies[3] = + 0.05;
	triangleVerticies[4] = + 0.15;
	triangleVerticies[5] = - 0.95;

	Shape triangle = Shape(0.55, 0.45, triangleVerticies);

	char keyInput = 'z';

	while (!glfwWindowShouldClose(window)) {
		//Setup View
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		//Intro Screen
		if (inIntroSequence) introScreen(window);

		//Movement Loop
		if (!inIntroSequence) {
			applyBoundaries(ball, cellRadius, radius);

			//Update function based on keyboard input
			if (_kbhit()) {
				keyInput = _getch();
				int a;
			}
			if (keyInput == 'w' || keyInput == 'a' || keyInput == 's' || keyInput == 'd') {
				movingTriangle.updateStateWASDToVelocity(keyInput, accelerationFactor);
			}
			else if (keyInput == 'q') {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
			else movingTriangle.updateState();

			triangle.Shape::testBoundaries(movingTriangle.Shape::getPosition().getX(), movingTriangle.Shape::getPosition().getX());

			//Draw triangles
			triangleDraw(movingTriangle.Shape::getVerticies(), movingTriangle.Shape::getColour());
			triangleDraw(triangle.Shape::getVerticies(), triangle.Shape::getColour());

		}

		setLastFrameParameters(ball.getPosition().getX(), ball.getPosition().getY());

		//Swap buffer and check for events
		keyInput = 'z';
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate;
	exit(EXIT_SUCCESS);
}

void setLastFrameParameters(float argx, float argy) {
	lastFrameX = argx;
	lastFrameX = argy;
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

void applyBoundaries(PhysicalShapeNode inBall, float inCellRadius, float inRadius) {
	if (ball.getPosition().getX() < -(cellRadius - radius) && !ball.isMovingRight()) {
		//flipColours();
		ball.flipVelocityX();
	}

	if (ball.getPosition().getX() > (cellRadius - radius) && ball.isMovingRight()) {
		//flipColours();
		ball.flipVelocityX();
	}

	if (ball.getPosition().getY() < -(cellRadius - radius) && !ball.isMovingUp()) {
		//flipColours();
		ball.flipVelocityY();
	}

	if (ball.getPosition().getY() > (cellRadius - radius) && ball.isMovingUp()) {
		//flipColours();
		ball.flipVelocityY();
	}
}

void introScreen(GLFWwindow* window) {

	char keyInput;
	int l, i;

	char textToScreen[] = "Welcome, please press space to start or q to exit";

	char* st = textToScreen;

	l = strlen(st); // see how many characters are in text string.
	glRasterPos2f(-0.7, 0.6); // location to start printing text
	for (i = 0; i < l; i++) // loop until i is greater then l
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)st[i]); // Print a character on the screen
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