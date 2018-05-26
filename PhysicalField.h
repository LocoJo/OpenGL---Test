#pragma once

#include "PhysicalVector.h"

class PhysicalField : public PhysicalVector {
protected:

	char chargeType;
	PhysicalVector fieldVector;

public:


	//CONSTRUCTORS

	PhysicalField();

	PhysicalField(float inX, float inY, char inChar);

	PhysicalField(float inArray[], char inChar);

	PhysicalField(PhysicalVector inPhysicalVector);

	PhysicalField(PhysicalVector inPhysicalVector, char inChar);

	char getChargeType();

	PhysicalVector getFieldVector();

	void setChargeType(char inChargeType);

	void setFieldVector(PhysicalVector inFieldVector);

	PhysicalVector getFieldAcceleration();
};