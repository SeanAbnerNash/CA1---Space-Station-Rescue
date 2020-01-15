// author Peter Lowe
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Player.h"
#include "Worker.h"
#include "Grid.h"
#include "Powerup.h"
class Grid;
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
	Player m_player;
	std::vector<Worker*>m_workers;
	sf::View m_miniMap;
	sf::RectangleShape m_mapBorder;
	Grid* grid;
	std::vector<Powerup*>m_powerups;
};

#endif // !GAME

