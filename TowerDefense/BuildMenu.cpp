#include "BuildMenu.h"
#include "Config.h"
#include "LevelManager.h"
#include "NormalTower.h"
#include "MoneyTower.h"
#include "SlowTower.h"
#include "SunTower.h"
#include "Tower.h"

//Constructors, destructors

BuildMenu::BuildMenu(){}

BuildMenu::BuildMenu(shared_ptr<Tile> pTile)
{
	tile = pTile;
	sf::Vector2i tilePositionPixel(tile->getPositionPixel());

	basicTwButton=Button(BASIC_TOWER_BUTTON_TEXTURE, SMALL_BUTTON_SIZE, tilePositionPixel + sf::Vector2i(-BUTTON_WIDTH, -BUTTON_WIDTH), 1);
	moneyTwButton=Button(MONEY_TOWER_BUTTON_TEXTURE, SMALL_BUTTON_SIZE, tilePositionPixel + sf::Vector2i(BUTTON_WIDTH, -BUTTON_HEIGHT), 1);
	slowTwButton=Button(SLOW_TOWER_BUTTON_TEXTURE, SMALL_BUTTON_SIZE, tilePositionPixel + sf::Vector2i(BUTTON_WIDTH, BUTTON_HEIGHT), 1);
	sunTwButton=Button(SUN_TOWER_BUTTON_TEXTURE, SMALL_BUTTON_SIZE, tilePositionPixel + sf::Vector2i(-BUTTON_WIDTH, BUTTON_HEIGHT), 1);

	if (!font.loadFromFile(FONT))
	{
		//error
	}

	basicPrice.setFont(font);
	moneyPrice.setFont(font);
	slowPrice.setFont(font);
	sunPrice.setFont(font);

	basicPrice.setColor(sf::Color::Green);
	moneyPrice.setColor(sf::Color::Green);
	slowPrice.setColor(sf::Color::Green);
	sunPrice.setColor(sf::Color::Green);

	basicPrice.setString("$" + std::to_string(NORMAL_TOWER_PRICE));
	moneyPrice.setString("$" + std::to_string(MONEY_TOWER_PRICE));
	slowPrice.setString("$" + std::to_string(SLOW_TOWER_PRICE));
	sunPrice.setString("$" + std::to_string(SUN_TOWER_PRICE));

	basicPrice.setCharacterSize(14);
	moneyPrice.setCharacterSize(14);
	slowPrice.setCharacterSize(14);
	sunPrice.setCharacterSize(14);

	basicPrice.setPosition(sf::Vector2f(basicTwButton.getPosition()));
	moneyPrice.setPosition(sf::Vector2f(moneyTwButton.getPosition()));
	slowPrice.setPosition(sf::Vector2f(slowTwButton.getPosition()));
	sunPrice.setPosition(sf::Vector2f(sunTwButton.getPosition()));
}

BuildMenu::~BuildMenu(){}

//Getters

shared_ptr<Tile> BuildMenu::getTile()
{
	return tile;
}

//Functions

void BuildMenu::buyBasicTw()
{
	if (!tile->hasEnemy()){
		LevelManager::getLevelManager()->getPlayer()->manageMoney(-NORMAL_TOWER_PRICE);
		auto pNormalTw = make_shared<NormalTower>(tile);
		LevelManager::getLevelManager()->addTower(pNormalTw);
		tile->setTower(pNormalTw);
	}
}

void BuildMenu::buyMoneyTw()
{
	if (!tile->hasEnemy()){
		LevelManager::getLevelManager()->getPlayer()->manageMoney(-MONEY_TOWER_PRICE);
		auto pMoneyTw = make_shared<MoneyTower>(tile);
		LevelManager::getLevelManager()->addTower(pMoneyTw);
		tile->setTower(pMoneyTw);
	}
}

void BuildMenu::buySlowTw()
{
	if (!tile->hasEnemy()){
		LevelManager::getLevelManager()->getPlayer()->manageMoney(-SLOW_TOWER_PRICE);
		auto pSlowTw = make_shared<SlowTower>(tile);
		LevelManager::getLevelManager()->addTower(pSlowTw);
		tile->setTower(pSlowTw);
	}
}

void BuildMenu::buySunTw()
{
	if (!tile->hasEnemy()){
		LevelManager::getLevelManager()->getPlayer()->manageMoney(-SUN_TOWER_PRICE);
		auto pSunTw = make_shared<SunTower>(tile);
		LevelManager::getLevelManager()->addTower(pSunTw);
		tile->setTower(pSunTw);
	}
	
}


void BuildMenu::resolveEvent(sf::Event event)
{
	if (basicTwButton.checkHover())
	{	
		basicTwButton.resolveEvent(event);
		if (basicTwButton.checkClick())
		{
			if (LevelManager::getLevelManager()->getPlayer()->getMoney() >= NORMAL_TOWER_PRICE)
			{
				buyBasicTw();
			}
			close();
		}
	}
	else if (sunTwButton.checkHover())
	{
		sunTwButton.resolveEvent(event);
		if (sunTwButton.checkClick())
		{
			if (LevelManager::getLevelManager()->getPlayer()->getMoney() >= SUN_TOWER_PRICE)
			{
				buySunTw();
			}
			close();
		}
	}
	else if (slowTwButton.checkHover())
	{
		slowTwButton.resolveEvent(event);
		if (slowTwButton.checkClick())
		{
			if (LevelManager::getLevelManager()->getPlayer()->getMoney() >= SLOW_TOWER_PRICE)
			{
				buySlowTw();
			}
			close();
		}
	}
	else if (moneyTwButton.checkHover())
	{
		moneyTwButton.resolveEvent(event);
		if (moneyTwButton.checkClick())
		{
			if (LevelManager::getLevelManager()->getPlayer()->getMoney() >= MONEY_TOWER_PRICE)
			{
				buyMoneyTw();
			}
			close();
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		close();
	}
}

void BuildMenu::draw(sf::RenderWindow& w)
{
	w.draw(sprite);

	if (basicTwButton.mouseHover(w))
	{
		auto tempTower = make_shared<NormalTower>(tile);
		tempTower->draw(w);
		tempTower->showRangeCircle(w);
	}

	if (slowTwButton.mouseHover(w))
	{
		auto tempTower = make_shared<SlowTower>(tile);
		tempTower->draw(w);
		tempTower->showRangeCircle(w);
	}
	if (moneyTwButton.mouseHover(w))
	{
		auto tempTower = make_shared<MoneyTower>(tile);
		tempTower->draw(w);
		tempTower->showRangeCircle(w);
	}
	if (sunTwButton.mouseHover(w))
	{
		auto tempTower = make_shared<SunTower>(tile);
		tempTower->draw(w);
		tempTower->showRangeCircle(w);
	}

	basicTwButton.draw(w);
	slowTwButton.draw(w);
	moneyTwButton.draw(w);
	sunTwButton.draw(w);

	w.draw(basicPrice);
	w.draw(moneyPrice);
	w.draw(slowPrice);
	w.draw(sunPrice);
}

void BuildMenu::close()
{
	LevelManager::getLevelManager()->updatePath();
	MenuManager::getMenuManager()->popMenu();
	MenuManager::getMenuManager()->setExistBTMenu(false);
}