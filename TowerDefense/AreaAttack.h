#pragma once
#include "Attack.h"

class AreaAttack :
	public Attack
{
private:
	float range;

public:
	AreaAttack();
	~AreaAttack();

	float getRange();

	void setRange();

	sf::Vector2f getTarget();
};

