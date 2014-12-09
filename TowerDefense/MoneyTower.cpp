#include "MoneyTower.h"


MoneyTower::MoneyTower(shared_ptr<Tile> mTile)
	:Tower(mTile)
{
	for (int i = 0; i < 3; i++)
	{
		income[level - 1] = MONEY_TOWER_INCOME[level - 1];
	}
	price = MONEY_TOWER_PRICE;

	if (!texture.loadFromFile(MONEY_TOWER_SPRITE_ADD))
	{
		// TODO erreur...
	}
	setTowerTexture();
}

void MoneyTower::doAttack()
{
	generateMoney();
}

void MoneyTower::showRangeCircle(sf::RenderWindow& w)
{

}

/*
Generate money in a frequency defined by timer
*/

void MoneyTower::generateMoney()
{
	if (timer == 0)
	{
		LevelManager::getLevelManager()->getPlayer()->manageMoney(MONEY_TOWER_GENERATION_UNIT[level - 1]);
		timer = speed;
	}
	else
		timer--;
}
