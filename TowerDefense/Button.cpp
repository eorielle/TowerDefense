#include "Button.h"

Button::Button()
{
	size = sf::Vector2f(0, 0);
	boundingBox = sprite.getGlobalBounds();
	position = sf::Vector2i(0, 0);
}

Button::Button(std::string textureAddress)
{
	size = sf::Vector2f(0, 0);
	position = sf::Vector2i(0, 0);

	sf::Texture texture;
	if (!texture.loadFromFile(textureAddress))
	{
		// TODO erreur...
	}

	sprite.setTexture(texture);
	boundingBox = sprite.getGlobalBounds();
}

Button::Button(sf::Vector2f mySize, std::string textureAddress, sf::Vector2i myPosition)
{
	sf::Texture texture;
	if (!texture.loadFromFile(textureAddress))
	{
		// TODO erreur...
	}

	sprite.setTexture(texture);
	boundingBox = sprite.getGlobalBounds();

	position = myPosition;
	size = mySize;
}


Button::~Button(){};

sf::Vector2i Button::getPosition()
{
	return position;
}

sf::Vector2f Button::getSize()
{
	return size;
}

sf::Sprite Button::getSprite()
{
	return sprite;
}

void Button::setPosition(sf::Vector2i mPosition)
{
	position = mPosition;
}

void Button::setSize(sf::Vector2f mSize)
{
	size = mSize;
}

void Button::setSprite(sf::Sprite mSprite)
{
	sprite = mSprite;
}

void Button::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
}

bool Button::mouseHover()
{
	bool isHovering = false;
	sf::Vector2f mousePosition((float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y);

	if (boundingBox.contains(mousePosition))
	{
		isHovering = true;
		//updatesprite
	}
	else
	{
		isHovering = false;
		//updatesprite
	}

	return isHovering;
}

bool Button::mouseClicking(sf::Event event)
{
	if (mouseHover())
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			return true;
			//updatesprite
		}
	}
	return false;
}

bool Button::mouseClick(sf::Event event)
{
	if (mouseClicking(event))
	{
		if (event.type == sf::Event::MouseButtonReleased)
		{
			return true;
			//updatesprite
		}
	}
	return false;
}
