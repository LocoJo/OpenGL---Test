#include "Shape.h"

Shape::Shape()
{
	boundaryDefinitions();
	numberOfVerticies = 3;
	verticies[6] = {0};
	char boundarySign[2] = { '>', '>' };
	geoCentreNode = PhysicalShapeNode();
}

Shape::Shape(float* inNodeCentre, float* inVerticies) {
	numberOfVerticies = 3;
	colour[0] = 0.9;
	colour[1] = 0.1;
	colour[2] = 0.2;
	position.setVector(inNodeCentre);
	for (char element : boundarySign) {
		element = '>';
	}
	int i = 0;
	int j = 0;
	while ((i + j) < 6) {
		while (j < 2) {
			verticies[i + j] = *(inVerticies + (i + j)) + *(inNodeCentre + j);
			j++;
		}
		i += 2;
		j = 0;
	}
	boundaryDefinitions();
}

Shape::Shape(float inNodeCentreX, float inNodeCentreY, float* inVerticies) {
	numberOfVerticies = 3;
	colour[0] = 0.9;
	colour[1] = 0.1;
	colour[2] = 0.2;
	position.setVector(inNodeCentreX, inNodeCentreY);
	for (char element : boundarySign) {
		element = '>';
	}
	int i = 0;
	int j = 0;
	while ((i + j) < 6) {
		while (j < 2) {
			verticies[i + j] = *(inVerticies + (i + j)) + *(position.getVector() + j);
			j++;
		}
		i += 2;
		j = 0;
	}
	boundaryDefinitions();
}

Shape::Shape(float* inNodeCentre, float* inVerticies, float* inColour) {
	numberOfVerticies = 3;
	for (int i = 0; i < 3; i++) {
		colour[i] = *(inColour + i);
	}
	position.setVector(inNodeCentre);
	for (char element : boundarySign) {
		element = '>';
	}
	int i = 0;
	int j = 0;
	while ((i + j) < 6) {
		while (j < 2) {
			verticies[i + j] = *(inVerticies + (i + j)) + *(inNodeCentre + j);
			j++;
		}
		i += 2;
		j = 0;
	}
	boundaryDefinitions();
}

void Shape::boundaryDefinitions() {
	for (int i = 0; i < numberOfVerticies * 2; i += 2) {
		if (i >= 4) {
			gradient[(i/2)] = ((verticies[i + 1] - verticies[1]) / (verticies[i] - verticies[0]));
			if ((position.getY() - verticies[i + 1]) < (gradient[(i/2)] * (position.getY() - verticies[i]))) boundarySign[i] = '<';
		}
		else {
			gradient[(i/2)] = ((verticies[i + 1] - verticies[i + 3]) / (verticies[i] - verticies[i + 2]));
			if ((position.getY() - verticies[i + 1]) < (gradient[(i/2)] * (position.getY() - verticies[i]))) boundarySign[i] = '<';
		}
	}
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
		colour[0] = 0.9;
		colour[1] = 0.1;
		colour[2] = 0.2;
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

Shape::~Shape()
{
}