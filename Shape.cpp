#pragma once

#include "Shape.h"
#include <stdio.h>
#include <iostream>
#include <math.h>

Shape::Shape()
{
	boundaryDefinitions();
	numberOfVerticies = 3;
	verticies[6] = {0};
	char boundarySign[3] = {'>', '>', '>'};
	position.setVector(0.0, 0.0);
	for (bool element : oldInsideBoundary) {
		element = false;
	}
}

Shape::Shape(float* inVerticies) {
	numberOfVerticies = 3;
	colour[0] = 0.9;
	colour[1] = 0.1;
	colour[2] = 0.2;
	char boundarySign[3] = { '>', '>', '>' };
	int i = 0;
	int j = 0;
	geoCentreInitialization(inVerticies);
	while ((i + j) < 6) {
		while (j < 2) {
			verticies[i + j] = *(inVerticies + (i + j));
			j++;
		}
		i += 2;
		j = 0;
	}
	boundaryDefinitions();
	for (bool element : oldInsideBoundary) {
		element = false;
	}
}

Shape::Shape(float* inVerticies, float* inColour) {
	numberOfVerticies = 3;
	for (int i = 0; i < 3; i++) {
		colour[i] = *(inColour + i);
	}
	char boundarySign[3] = { '>', '>', '>' };
	int i = 0;
	int j = 0;
	geoCentreInitialization(inVerticies);
	while ((i + j) < 6) {
		while (j < 2) {
			verticies[i + j] = *(inVerticies + (i + j));
			j++;
		}
		i += 2;
		j = 0;
	}
	boundaryDefinitions();
	for (bool element : oldInsideBoundary) {
		element = false;
	}
}

void Shape::boundaryDefinitions() {
	for (int i = 0; i < numberOfVerticies * 2; i += 2) {
		if (i >= 4) {
			gradient[(i/2)] = ((verticies[i + 1] - verticies[1]) / (verticies[i] - verticies[0]));
			if ((position.getY() - verticies[i + 1]) < (gradient[(i/2)] * (position.getY() - verticies[i]))) boundarySign[(i/2)] = '<';
		}
		else {
			gradient[(i/2)] = ((verticies[i + 1] - verticies[i + 3]) / (verticies[i] - verticies[i + 2]));
			if ((position.getY() - verticies[i + 1]) < (gradient[(i/2)] * (position.getY() - verticies[i]))) boundarySign[(i/2)] = '<';
		}
	}
}

void Shape::geoCentreInitialization(float* inVerticies) {
	float geoCentre[2] = {0.0, 0.0};
	for (int i = 0; i < 6; i +=2) {
		for (int j = 0; j < 2; j++) {
			geoCentre[j] += *(inVerticies + i + j);
		}
	}
	geoCentre[0] /= ((float)numberOfVerticies);
	geoCentre[1] /= ((float)numberOfVerticies);
	position.setVector(geoCentre[0], geoCentre[1]);
}

void Shape::testBoundaries(float x, float y) {
	bool insideBoundary[3] = { false, false, false };
	for (int i = 0; i < numberOfVerticies * 2; i += 2) {
		if (boundarySign[i] == '<') {
			if ((y - verticies[i + 1]) < (gradient[(i/2)] * (x - verticies[i]))) insideBoundary[i / 2] = true;
		}
		else {
			if ((y - verticies[i + 1]) > (gradient[(i/2)] * (x - verticies[i]))) insideBoundary[i / 2] = true;
		}
	}
	if (insideBoundary[0] == true && insideBoundary[1] == true && insideBoundary[2] == true) {
		colour[0] = 0.5;
		colour[1] = 0.5;
		colour[2] = 0.5;
	}
	else {
		colour[0] = 0.6;
		colour[1] = 0.6;
		colour[2] = 0.6;
	}
	for (int i = 0; i < 3; i++) {
		oldInsideBoundary[i] = insideBoundary[i];
	}
}

void Shape::testBounceBoundaries(float x, float y, Shape* inShape) {
	bool insideBoundary[3] = { false, false, false };
	for (int i = 0; i < numberOfVerticies * 2; i += 2) {
		if (boundarySign[i] == '<') {
			if ((y - verticies[i + 1]) < (gradient[(i / 2)] * (x - verticies[i]))) insideBoundary[i / 2] = true;
		}
		else {
			if ((y - verticies[i + 1]) > (gradient[(i / 2)] * (x - verticies[i]))) insideBoundary[i / 2] = true;
		}
	}
	if (insideBoundary[0] && insideBoundary[1] && insideBoundary[2]) {
		if (oldInsideBoundary[0] && oldInsideBoundary[1] && !oldInsideBoundary[2]) {
			inShape->bounceOperator(gradient[2]);
		}
		else if (oldInsideBoundary[0] && !oldInsideBoundary[1] && oldInsideBoundary[2]) {
			inShape->bounceOperator(gradient[1]);
		}
		else if (!oldInsideBoundary[0] && oldInsideBoundary[1] && oldInsideBoundary[2]){
			inShape->bounceOperator(gradient[0]);
		}
	}
	for (int i = 0; i < 3; i++) {
		oldInsideBoundary[i] = insideBoundary[i];
	}
}

void Shape::updateStateWASDToAcceleration(int WASDdirection, float accellerationFactor) {
	float positionDiff[] = { position.getX(), position.getY() };
	PhysicalShapeNode::updateStateWASDToAcceleration(WASDdirection, accellerationFactor);
	positionDiff[0] = position.getX() - positionDiff[0];
	positionDiff[1] = position.getY() - positionDiff[1];
	this->updateVerticies(positionDiff);
}

void Shape::updateStateWASDToVelocity(int WASDdirection, float accellerationFactor) {
	float positionDiff[] = { position.getX(), position.getY() };
	PhysicalShapeNode::updateStateWASDToVelocity(WASDdirection, accellerationFactor);
	positionDiff[0] = position.getX() - positionDiff[0];
	positionDiff[1] = position.getY() - positionDiff[1];
	this->updateVerticies(positionDiff);
}

void Shape::updateState() {
	float positionDiff[] = {position.getX(), position.getY()};
	PhysicalShapeNode::updateState();
	positionDiff[0] = position.getX() - positionDiff[0];
	positionDiff[1] = position.getY() - positionDiff[1];
	this->updateVerticies(positionDiff);
}

void Shape::updateVerticies(float* inPositiondiff) {
	int i = 0;
	int j = 0;
	while ((i + j) < 6) {
		while (j < 2) {
			verticies[i + j] = verticies[i + j] + *(inPositiondiff + j);
			j++;
		}
		i += 2;
		j = 0;
	}
}

float* Shape::getColour() {
	return colour;
}

float* Shape::getVerticies() {
	return verticies;
}

void Shape::bounceOperator(double inGradient) {
	if (inGradient < 0.0) inGradient *= -1;
	float twoTheta = 2 * (atan((-1 * inGradient)));
	setVelocity((((cos(twoTheta)) * velocity.getX()) + ((sin(twoTheta)) * velocity.getY())),
			    (((sin(twoTheta)) * velocity.getX()) - ((cos(twoTheta)) * velocity.getY())));
}

Shape::~Shape()
{
}