#pragma once
#include "Tower.h"
#include "AreaAttack.h"

class SunTower :
	public Tower
{
public:
	SunTower(shared_ptr<Tile> mTile);
	SunTower(float mDamage, int mPrice, int mLevel, float mRange, float mSpeed, sf::Sprite mSprite);
	virtual ~SunTower(){};

	void doAttack() override;
private:
	AreaAttack attack;
};

