#pragma once

#include "PhysicalShapeNode.h"

class Shape : public PhysicalShapeNode
{
protected:
	int numberOfVerticies;
	float colour[3];
	char boundarySign[3];
	float verticies[6];
	float gradient[3];
	bool oldInsideBoundary[3];
	void boundaryDefinitions();
	void geoCentreInitialization(float* inVerticies);

public:
	Shape();

	Shape(float* inVerticies);

	Shape(float* inVerticies, float* inColour);

	void testBoundaries(float x, float y);

	void testBounceBoundaries(float x, float y, Shape* inShape);

	//UPDATES
	void updateStateWASDToAcceleration(int WASDdirection, float accellerationFactor);

	void updateStateWASDToVelocity(int WASDdirection, float accellerationFactor);

	void updateState();

	void updateVerticies(float* inPositiondiff);

	//GETS
	float* getColour();

	float* getVerticies();

	//OPERATORS
	void bounceOperator(double inGradient);

	//DESTRUCTOR
	~Shape();
};