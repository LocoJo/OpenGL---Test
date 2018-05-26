#include "PhysicalShapeNode.h"

//CONSTRUCTORS

PhysicalShapeNode::PhysicalShapeNode() {
	position, velocity, acceleration = PhysicalVector();
	mass = 0.0;
}

PhysicalShapeNode::PhysicalShapeNode(PhysicalVector inPosition, float inMass) {
	position = inPosition;
	mass = inMass;
}

PhysicalShapeNode::PhysicalShapeNode(PhysicalVector inPosition, PhysicalVector inVelcoity) {
	position = inPosition;
	velocity = inVelcoity;
	mass = 0.0;
}

PhysicalShapeNode::PhysicalShapeNode(PhysicalVector inPosition, PhysicalVector inVelcoity, float inMass) {
	position = inPosition;
	velocity = inVelcoity;
	mass = inMass;
}

PhysicalShapeNode::PhysicalShapeNode(PhysicalVector inPosition, PhysicalVector inVelcoity, PhysicalVector inAcceleration, float inMass) {
	position = inPosition;
	velocity = inVelcoity;
	acceleration = inAcceleration;
	mass = inMass;
}

//UPDATE ORDINATES

void PhysicalShapeNode::updatePosition() { // r = r + vt + 1/2at^2
	this->setPosition((this->getPosition().getX() + this->getVelocity().getX() + (this->getAcceleration().getX() / 2.0)),
		(this->getPosition().getY() + this->getVelocity().getY() + (this->getAcceleration().getY() / 2.0))); 
}

void PhysicalShapeNode::updateVelocity() { // v = v + at
	this->setVelocity((this->getVelocity().getX() + this->getAcceleration().getX()),
		(this->getVelocity().getY() + this->getAcceleration().getY()));
}

void PhysicalShapeNode::updateAcceleration(PhysicalField inPhysicalField) {
	this->setAcceleration(inPhysicalField.getFieldAcceleration().getX(), inPhysicalField.getFieldAcceleration().getY());
}

void PhysicalShapeNode::updateAcceleration(PhysicalField inPhysicalField, float inDragFactor) {
	this->setAcceleration((inPhysicalField.getFieldAcceleration().getX()
		- (getDragAccelerationMagnitude(inDragFactor)*(this->getVelocity().getX()/this->getVelocity().getMagnitude()))),

		(inPhysicalField.getFieldAcceleration().getY()
		- (getDragAccelerationMagnitude(inDragFactor)*(this->getVelocity().getY() / this->getVelocity().getMagnitude()))));
}


//UPDATE ALL ORDINATES

void PhysicalShapeNode::updateState(PhysicalField inPhysicalField) {
	this->updateAcceleration(inPhysicalField);
	this->updatePosition();
	this->updateVelocity();
}

void PhysicalShapeNode::updateState(PhysicalField inPhysicalField, float inDragFactor) {
	this->updateAcceleration(inPhysicalField, inDragFactor);
	this->updatePosition();
	this->updateVelocity();
}

void PhysicalShapeNode::updateStateWASDToAcceleration(int WASDdirection, float accellerationFactor) {
	this->incrementAcceleration(WASDdirection, accellerationFactor);
	this->updatePosition();
	this->updateVelocity();
}

void PhysicalShapeNode::updateStateWASDToVelocity(int WASDdirection, float velocityFactor) {
	this->incrementVelocity(WASDdirection, velocityFactor);
	this->updatePosition();
}

void PhysicalShapeNode::updateState() {
	this->updatePosition();
	this->updateVelocity();
}

bool PhysicalShapeNode::isMovingRight() {
	if (this->velocity.getX() > 0.0) return true;
	else return false;
}

bool PhysicalShapeNode::isMovingUp() {
	if (this->velocity.getY() > 0.0) return true;
	else return false;
}

void PhysicalShapeNode::flipVelocityX() {
	this->velocity.flipX();
}

void PhysicalShapeNode::flipVelocityY() {
	this->velocity.flipY();
}

float PhysicalShapeNode::getMass() {
	return this->mass;
}


//GET FUNCTIONS

PhysicalVector PhysicalShapeNode::getPosition() {
	return this->position;
}

PhysicalVector PhysicalShapeNode::getVelocity() {
	return this->velocity;
}

PhysicalVector PhysicalShapeNode::getAcceleration() {
	return this->acceleration;
}

//SET FUNCTIONS

void PhysicalShapeNode::setPosition(float inX, float inY) {
	this->position.setVector(inX, inY);
}

void PhysicalShapeNode::setPosition(PhysicalVector physicalVector) {
	this->position.setVector(physicalVector);
}

void PhysicalShapeNode::setVelocity(float inX, float inY) {
	this->velocity.setVector(inX, inY);
}

void PhysicalShapeNode::setVelocity(PhysicalVector physicalVector) {
	this->velocity.setVector(physicalVector);
}

void PhysicalShapeNode::setAcceleration(float inX, float inY) {
	this->acceleration.setVector(inX, inY);
}

void PhysicalShapeNode::setAcceleration(PhysicalVector physicalVector) {
	this->acceleration.setVector(physicalVector);
}

float PhysicalShapeNode::getDragAccelerationMagnitude(float inDragFactor) { // RETURNS a*|v|^2 / m
	float dragAcceleration;
	dragAcceleration = this->velocity.getMagnitude();
	dragAcceleration *= dragAcceleration;
	dragAcceleration *= inDragFactor;
	return (dragAcceleration / this->mass);
}

void PhysicalShapeNode::incrementAcceleration(int WASDdirection, float accellerationFactor) {
	switch (WASDdirection) {
		case (int)'w' : this->acceleration.incrementVector(0.0, accellerationFactor);
			break;
		case (int)'a' : this->acceleration.incrementVector(((-1)*accellerationFactor), 0.0);
			break;
		case (int)'s' : this->acceleration.incrementVector(0.0, ((-1)*accellerationFactor));
			break;
		case (int)'d' : this->acceleration.incrementVector(accellerationFactor, 0.0);
			break;
		default : ;
	}
	//if (WASDdirection == (int)'w') this->acceleration.incrementVector(0.0, accellerationFactor);
	//else if (WASDdirection == (int)'s') this->acceleration.incrementVector(0.0, ((-1)*accellerationFactor));
	//else if (WASDdirection == (int)'a') this->acceleration.incrementVector(((-1)*accellerationFactor), 0.0);
	//else if (WASDdirection == (int)'d') this->acceleration.incrementVector(accellerationFactor, 0.0);
}

void PhysicalShapeNode::incrementVelocity(int WASDdirection, float accellerationFactor) {
	switch (WASDdirection) {
	case (int)'w': this->velocity.incrementVector(0.0, accellerationFactor);
		break;
	case (int)'a': this->velocity.incrementVector(((-1)*accellerationFactor), 0.0);
		break;
	case (int)'s': this->velocity.incrementVector(0.0, ((-1)*accellerationFactor));
		break;
	case (int)'d': this->velocity.incrementVector(accellerationFactor, 0.0);
		break;
	}
}