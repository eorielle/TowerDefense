#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Tower.h"
#include "BuildMenu.h"
#include "TowerMenu.h"

class Tile
{
private:
	sf::Vector2f position;
	int width;
	int height;
	int cooldown;//ʣ�����ȴʱ�䣬Ĭ��Ϊ����״̬��ֵΪ0.������Ⱦ������ʱTILE_COOLDOWN_TIME��ָ�
	Tower* tower;
public:
	//Constructors and destroyers
	Tile();
	~Tile();

	//Getters
	sf::Vector2f getPosition();
	Tower* getTower();
	int getCooldowm();

	//Setters
	void setPosition(sf::Vector2f);
	void setTower(Tower*);
	void setCooldown(int);

	//Functions
	bool isPolluted();
	bool hasTower();
	BuildMenu* openBuildMenu();
	TowerMenu* openTowerMenu();

};