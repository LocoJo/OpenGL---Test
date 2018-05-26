#pragma once
#include <math.h>

class PhysicalVector {
protected:

	int dimension;
	float vector[2];

public:

	PhysicalVector();

	PhysicalVector(float inX, float inY);

	PhysicalVector(float inArray[]);

	PhysicalVector addVector(PhysicalVector physicalVector);

	void setVector(PhysicalVector physicalVector);

	void setVector(float inX, float inY);

	void incrementVector(float inX, float inY);

	float getMagnitude(PhysicalVector physicalVector);

	float getMagnitude();


	//GET FUNCTIONS

	float getX();

	float getY();

	float* getVector();

	//SET FUNCTIONS

	void setX(float inX);

	void setY(float inY);

	void setVector(float* inVectorPointer);

	void flipVector();

	void flipX();

	void flipY();

	float getElement(int dim);

	float getElement(PhysicalVector* physicalVector, int dim);
};