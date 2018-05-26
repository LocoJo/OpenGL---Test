#include "PhysicalVector.h"

PhysicalVector::PhysicalVector() {
	dimension = 2;
	for (float& element : vector)
		element = 0.0;
}

PhysicalVector::PhysicalVector(float inX, float inY) {
	dimension = 2;
	vector[0] = inX;
	vector[1] = inY;
}

PhysicalVector::PhysicalVector(float inArray[]) {
	dimension = 2;
	for (int i = 0; i < 2; i++) {
		vector[i] = inArray[i];
	}
}

PhysicalVector PhysicalVector::addVector(PhysicalVector physicalVector) {
	float sumVector[2];
	for (int i = 0; i < 2; i++) {
		sumVector[0] = this->getElement(i) + getElement(&physicalVector, i);
	}
	return PhysicalVector(sumVector);
}

void PhysicalVector::setVector(PhysicalVector physicalVector) {
	for (int i = 0; i < 2; i++) {
		this->vector[i] = getElement(&physicalVector, i);
	}
}

void PhysicalVector::setVector(float inX, float inY) {
	vector[0] = inX;
	vector[1] = inY;
}

void PhysicalVector::incrementVector(float inX, float inY) {
	vector[0] += inX;
	vector[1] += inY;
}

float PhysicalVector::getMagnitude(PhysicalVector physicalVector) {
	float Magnitude = 0.0;
	for (float& element : physicalVector.vector) {
		Magnitude += (element*element);
	}
	return sqrt(Magnitude);
}

float PhysicalVector::getMagnitude() {
	float Magnitude = 0.0;
	for (float& element : this->vector) {
		Magnitude += (element*element);
	}
	return sqrt(Magnitude);
}


//GETS FUNCTIONS

float PhysicalVector::getX() {
	return this->vector[0];
}

float PhysicalVector::getY() {
	return this->vector[1];
}

float* PhysicalVector::getVector() {
	return vector;
}


//SET FUNCTIONS

void PhysicalVector::setX(float inX) {
	this->vector[0] = inX;
}

void PhysicalVector::setY(float inY) {
	this->vector[1] = inY;
}

void PhysicalVector::setVector(float* inVectorPointer) {
	for (int i = 0; i < 2; i++) {
		vector[i] = *(inVectorPointer + i);
	}
}

void PhysicalVector::flipVector() {
	for (float element : this->vector) {
		element = -(element);
	}
}

void PhysicalVector::flipX() {
	this->vector[0] = -(this->vector[0]);
}

void PhysicalVector::flipY() {
	this->vector[1] = -(this->vector[1]);
}

float PhysicalVector::getElement(int dim) {
	return this->vector[dim];
}

float PhysicalVector::getElement(PhysicalVector* physicalVector, int dim) {
	return physicalVector->vector[dim];
}





