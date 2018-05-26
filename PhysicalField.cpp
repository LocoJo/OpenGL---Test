#include "PhysicalField.h"

	//CONSTRUCTORS

	PhysicalField::PhysicalField() {
		chargeType = '0';
		fieldVector = PhysicalVector();
	}

	PhysicalField::PhysicalField(float inX, float inY, char inChar) {
		fieldVector = PhysicalVector(inX, inY);
		chargeType = inChar;
	}

	PhysicalField::PhysicalField(float inArray[], char inChar) {
		fieldVector = PhysicalVector(inArray);
		chargeType = inChar;
	}

	PhysicalField::PhysicalField(PhysicalVector inPhysicalVector) {
		fieldVector = inPhysicalVector;
		chargeType = '0';
	}

	PhysicalField::PhysicalField(PhysicalVector inPhysicalVector, char inChar) {
		fieldVector = inPhysicalVector;
		chargeType = inChar;
	}

	char PhysicalField::getChargeType() {
		return this->chargeType;
	}

	PhysicalVector PhysicalField::getFieldVector() {
		return this->fieldVector;
	}

	void PhysicalField::setChargeType(char inChargeType) {
		this->chargeType = inChargeType;
	}

	void PhysicalField::setFieldVector(PhysicalVector inFieldVector) {
		this->fieldVector = inFieldVector;
	}

	PhysicalVector PhysicalField::getFieldAcceleration() {
		if (this->getChargeType() == 'G') {
			return this->getFieldVector();
		}
		else {
			return PhysicalVector();
		}
	}