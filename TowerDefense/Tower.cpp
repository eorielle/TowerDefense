#include "Tower.h"
#include "Player.h"
#include "LevelManager.h"
#include "NormalAttack.h"

Tower::Tower(shared_ptr<Tile> mTile)
{
	level = 1;
	currentSprite = level - 1;
	tile = mTile;
	size = sf::Vector2i(TILE_WIDTH, TILE_HEIGHT);
	position = sf::Vector2i(tile->getPositionPixel().x + 25, tile->getPositionPixel().y + 25);
	speed = TOWER_SPEED;
	timer = speed;
}


Tower::~Tower()
{
}
/*
Getters and Setters
*/
float Tower::getDamage()
{
	return damage[level - 1];
}

int Tower::getPrice()
{
	return price;
}

int Tower::getLevel()
{
	return level;
}

float Tower::getRange()
{
	return range[level - 1];
}

void Tower::setDamage(float mDamage)
{
	damage[level - 1] = mDamage;
}

void Tower::setPrice(int mPrice)
{
	price = mPrice;
}

void Tower::setLevel(int mLevel)
{
	level = mLevel;
}

void Tower::setRange(float mRange)
{
	range[level - 1] = mRange;
}

void Tower::setAttack()
{
	attack->setCenter(position);
	attack->setDamage(damage[level - 1]);
	attack->setSlowAmount(slowAmount[level - 1]);
	attack->setRange(range[level - 1]);
	attack->setSpeed(speed);
	attack->setTimer(timer);
}

void Tower::setTowerTexture()
{
	sprite.setTexture(texture);
	sf::Vector2i spriteInit(0, currentSprite * size.y);
	sprite.setTextureRect(sf::IntRect(spriteInit, size));
	sprite.setPosition(sf::Vector2f(tile->getPositionPixel().x, tile->getPositionPixel().y));
}

void Tower::setRangeCircle()
{
	rangeCircle.setOrigin(sf::Vector2f(range[level - 1], range[level - 1]));
	rangeCircle.setPosition(sf::Vector2f(position.x, position.y));
	rangeCircle.setRadius(range[level - 1]);
	rangeCircle.setFillColor(RANGE_CIRCLE_FILL_COLOR);
}

void Tower::spriteUpdate(int i)
{
	currentSprite = i;
	setTowerTexture();
}

/*
Upgrade the level of tower and set its new parameters
*/
void Tower::upgradeTw()
{
	if (level < 3)
	{
		level++;
		speed -= 5;
		timer = speed;
		currentSprite = level - 1;
		spriteUpdate(currentSprite);
		setAttack();
		setRangeCircle();
	}
}
/*
Downgrade the level of tower and set its new parameters
*/
void Tower::downgradeTw()
{
	if (level > 0)
	{
		level--;
		
		if (level > 0)
		{
			speed += 5;
			currentSprite = level - 1;
			spriteUpdate(currentSprite);
			timer = speed;

			setAttack();
			setRangeCircle();
		}
	}	
}

/*
Sell this tower
*/
void Tower::sellTw()
{
	LevelManager::getLevelManager()->getPlayer()->manageMoney(income[level - 1]);
	tile->setTower(NULL);
}


