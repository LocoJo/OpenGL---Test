#pragma once

#include "PhysicalField.h"

class PhysicalShapeNode : public PhysicalVector{
protected:

	float mass;

	PhysicalVector position;
	PhysicalVector velocity;
	PhysicalVector acceleration;

public:

	//CONSTRUCTORS

	PhysicalShapeNode();

	PhysicalShapeNode(PhysicalVector inPosition, float inMass);

	PhysicalShapeNode(PhysicalVector inPosition, PhysicalVector inVelcoity);

	PhysicalShapeNode(PhysicalVector inPosition, PhysicalVector inVelcoity, float inMass);

	PhysicalShapeNode(PhysicalVector inPosition, PhysicalVector inVelcoity, PhysicalVector inAcceleration, float inMass);

	//ORDINATE MODIFIERS

	void updatePosition();

	void updateVelocity();

	void updateAcceleration(PhysicalField inPhysicalField);

	void updateAcceleration(PhysicalField inPhysicalField, float inDragFactor);

	void incrementAcceleration(int WASDdirection, float accellerationFactor);

	void incrementVelocity(int WASDdirection, float accellerationFactor);

	//UPDATE STATES

	void updateState(PhysicalField inPhysicalField);

	void updateState(PhysicalField inPhysicalField, float inDragFactor);

	void updateStateWASDToAcceleration(int WASDdirection, float accellerationFactor);

	void updateStateWASDToVelocity(int WASDdirection, float velocityFactor);

	void updateState();

	//DIRECTIONS

	bool isMovingRight();

	bool isMovingUp();

	//DIRECTION MODIFIERS

	void flipVelocityX();

	void flipVelocityY();

	//GET FUNCTIONS

	float getMass();

	PhysicalVector getPosition();

	PhysicalVector getVelocity();

	PhysicalVector getAcceleration();

	float getDragAccelerationMagnitude(float inDragFactor);

	//SET FUNCTIONS

	void setPosition(float inX, float inY);

	void setPosition(PhysicalVector physicalVector);

	void setVelocity(float inX, float inY);

	void setVelocity(PhysicalVector physicalVector);

	void setAcceleration(float inX, float inY);

	void setAcceleration(PhysicalVector physicalVector);
};