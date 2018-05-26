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
	void boundaryDefinitions();
	PhysicalShapeNode geoCentreNode;

public:
	Shape();

	Shape(float* inNodeCentre, float* inVerticies);

	Shape(float inNodeCentreX, float inNodeCentreY, float* inVerticies);

	Shape(float* inNodeCentre, float* inVerticies, float* inColour);

	void testBoundaries(float x, float y);

	//UPDATES
	void updateStateWASDToAcceleration(int WASDdirection, float accellerationFactor);

	void updateState();

	void updateVerticies(float* inPositiondiff);

	//GETS
	float* getColour();

	float* getVerticies();

	~Shape();
};