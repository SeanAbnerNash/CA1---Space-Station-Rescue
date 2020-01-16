// Sean Nash & Patryk Wysocki
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"


#include "Powerup.h"
#include "World.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	
	ResourceManager m_resourceMng;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	sf::View m_miniMap;
	sf::RectangleShape m_mapBorder;
	std::vector<Powerup*>m_powerups;
	World m_world;

};

#endif // !GAME

