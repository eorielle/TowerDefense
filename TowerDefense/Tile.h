#pragma once
#include <SFML\Graphics.hpp>
#include <memory>
#include "Tower.h"
#include "BuildMenu.h"
#include "TowerMenu.h"

class Tile
{
private:
	sf::Vector2f position;//���Ͻǵ��λ��
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
	sf::Vector2f getPosition();
	shared_ptr<Tower>  getTower();
	int getCooldowm();

	//Setters
	void setPosition(sf::Vector2f);
	void setTower(shared_ptr<Tower>);
	void setCooldown(int);

	//Functions
	bool isPolluted();
	bool hasTower();
	shared_ptr<BuildMenu> openBuildMenu();
	shared_ptr<TowerMenu> openTowerMenu();

};