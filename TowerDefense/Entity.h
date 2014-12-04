#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Entity
{
protected:
	sf::Vector2i position;
	sf::Vector2f size;
	float speed;
	sf::Sprite sprite;
	shared_ptr<Tile> tile;
	int timer;//To define Config respectively for Enemy and Tower
	sf::Texture texture;

public:
	//Constructors and destroyers
	Entity();
	~Entity();

	//Getters
	sf::Vector2i getPosition();
	sf::Vector2f getSize();
	float getSpeed();
	sf::Sprite getSprite();
	shared_ptr<Tile> getTile();

	//Setters
	void setPosition(sf::Vector2i mPosition);
	void setSize(sf::Vector2f mSize);
	void setSpeed(float mSpeed);
	void setSprite(sf::Sprite mSprite);

	//Functions
	void draw(sf::RenderWindow&);
};

