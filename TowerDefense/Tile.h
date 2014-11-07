#pragma once
#include <SFML\Graphics.hpp>
#include <memory>
#include <Vector>
#include "Tower.h"
#include "BuildMenu.h"
#include "TowerMenu.h"

class Tile
{
private:
	sf::Vector2i positionPixel;//���Ͻǵ��λ��
	sf::Vector2i position;
	int width;
	int height;
	int cooldown;//ʣ�����ȴʱ�䣬Ĭ��Ϊ����״̬��ֵΪ0.������Ⱦ������ʱTILE_COOLDOWN_TIME��ָ�
	shared_ptr<Tower> tower;
public:
	//Constructors and destroyers
	Tile();
	Tile(int, int);//x,y position,��x�У���y�У���0��ʼ����
	~Tile();

	//Getters
	sf::Vector2i getPosition();
	sf::Vector2i getPositionPixel();
	shared_ptr<Tower>  getTower();
	int getCooldowm();
	vector<Tile*> getNeighbor(int);
	Tile* getStartTile();
	Tile* getEndTile();

	//Setters
	void setPosition(sf::Vector2i);
	void setTower(shared_ptr<Tower>);
	void setCooldown(int);

	//Functions	
	bool isPolluted();
	bool hasTower();
	shared_ptr<BuildMenu> openBuildMenu();
	shared_ptr<TowerMenu> openTowerMenu();

};