#include "SunTower.h"


SunTower::SunTower(shared_ptr<Tile> mTile)
	:Tower(mTile)
{
	damage[level - 1] = SUN_TOWER_DAMAGE[level - 1];
	price = SUN_TOWER_PRICE;
	income[level - 1] = SUN_TOWER_INCOME[level - 1];
	range[level - 1] = SUN_TOWER_RANGE[level - 1];

	attack.setDamage(damage[level - 1]);
	attack.setRange(range[level - 1]);
	attack.setSpeed(speed);

	timer = speed;

	if (!texture.loadFromFile(NORMAL_TOWER_SPRITE_ADD))
	{
		// TODO erreur...
	}

	sprite.setTexture(texture);
	sf::Vector2i spriteInit(0, currentSprite * size.y);
	sprite.setTextureRect(sf::IntRect(spriteInit, size));
	sprite.setPosition(sf::Vector2f(tile->getPositionPixel().x, tile->getPositionPixel().y));

	rangeCircle.setPosition(sf::Vector2f(this->getPosition()));
	rangeCircle.setRadius(range[level - 1]);
	rangeCircle.setOutlineThickness(2);
	rangeCircle.setFillColor(sf::Color(0, 0, 255, 100));
}

/*
Activate attck
*/

void SunTower::doAttack()
{
	attack.resolve();
}
