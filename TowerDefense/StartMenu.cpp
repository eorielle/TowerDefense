#include "StartMenu.h"
#include <string>

StartMenu::StartMenu()
{
}

StartMenu::StartMenu(std::string myTextureAddress, sf::Vector2u mySize, sf::Vector2i myPosition)
{
	Menu(myTextureAddress, mySize, myPosition);
}

//functions

void StartMenu::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
	startGameButton.draw(w);
	openCreditsButton.draw(w);
	muteButton.draw(w);
	exitGameButton.draw(w);
}

void StartMenu::resolveEvent(sf::Event event)
{
	if (startGameButton.mouseClick(event))
	{
		startGame();
	}
	if (openCreditsButton.mouseClick(event))
	{
		openCredits();
	}
	if (muteButton.mouseClick(event))
	{
		AudioManager audio = AudioManager::getAudioManager();
		if (audio.isMute() == false)
		{
			muteGame();
		}
		else
		{
			playMusic();
		}
	}
	if (exitGameButton.mouseClick(event))
	{
		exitGame();
	}
}

void StartMenu::startGame()
{
	GameMenu gameMenu = GameMenu(GAME_MENU_DEFAULT_TEXTURE, sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT), sf::Vector2i(0,0));
	MenuManager* m = MenuManager::getMenuManager();

	m->popMenu();
	m->addMenu(gameMenu);

	this -> ~StartMenu();
}

void StartMenu::openCredits()
{
	CreditsMenu credits = CreditsMenu();
	MenuManager* m = MenuManager::getMenuManager();

	m->addMenu(credits);
}

void StartMenu::muteGame()
{
	AudioManager audio = AudioManager::getAudioManager();
	audio.mute();
}

void StartMenu::playMusic()
{
	AudioManager audio = AudioManager::getAudioManager();
	audio.play();
}

void StartMenu::exitGame()
{
	MenuManager* m = MenuManager::getMenuManager();
	m-> ~MenuManager();
}

