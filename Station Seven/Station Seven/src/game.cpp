#include "game.h"
#include <iostream>

static sf::Int32 MS_PER_UPDATE = 10.0;
/// <summary>
/// game contruction that initialises 
/// the window 
/// the player 
/// the minimap
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1200, 800, 32 }, "SFML Game" },
	m_player(m_resourceMng),
	m_exitGame{ false }, //when true game will exit
	m_world(m_resourceMng),
	m_grid()
{
	m_window.setFramerateLimit(60);

	//TODO: THIS IS where we load the map texture that matches our map in grid.cpp
	//m_worldSprite.setTexture(m_resourceMng.getTexture(TextureID::WORLDMAP));
	//m_worldSprite.setScale(1, 1);
	//m_worldSprite.setOrigin(m_worldSprite.getLocalBounds().width / 2, m_worldSprite.getLocalBounds().height / 2);
	m_mapBorder.setOutlineThickness(10.0f);
	m_mapBorder.setOutlineColor(sf::Color::Black);
	m_mapBorder.setSize(sf::Vector2f(300, 200));

	m_workers.push_back(new Worker(WORKERSTATE::WANDER, sf::Vector2f(900, 500), m_resourceMng));
	m_powerups.push_back(new Powerup(sf::Vector2f(100, 200), POWERUPTYPE::SHIELD, m_resourceMng));
	m_powerups.push_back(new Powerup(sf::Vector2f(0, 100), POWERUPTYPE::SHIELD, m_resourceMng));
	m_powerups.push_back(new Powerup(sf::Vector2f(0, 200), POWERUPTYPE::SHOT360, m_resourceMng));
	m_powerups.push_back(new Powerup(sf::Vector2f(0, 300), POWERUPTYPE::SHOT360, m_resourceMng));
	m_miniMap.zoom(2);
}

/// <summary>
/// destructor of game object
/// </summary>
Game::~Game()
{
}

/// <summary>
/// run fucntion handles the updating of the game
/// this is the game loop.
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if ( sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_grid.mouseClick(sf::Mouse::getPosition(m_window), 1);
			}
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				m_grid.mouseClick(sf::Mouse::getPosition(m_window), 2);
			}
			if (event.mouseButton.button == sf::Mouse::Middle)
			{
				m_grid.mouseClick(sf::Mouse::getPosition(m_window), 3);
			}
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	m_grid.update();
	if (m_exitGame)
	{
		m_window.close();
	}
	m_player.update(t_deltaTime);
	for (Worker* workers : m_workers)
	{
		workers->update(m_player.getPos(),m_player.getVel());
		if (m_player.playerWorkerCollision(workers->getPosition()))
		{
			std::cout << "worker collected" << std::endl;
		}
	}
	for (Powerup* powerup : m_powerups)
	{
		powerup->update();
		if (powerup->collisionDetection(m_player.getPos()))
		{
			powerup->setAlive(false);
			if (powerup->getPowerupType() ==POWERUPTYPE::SHIELD)
			{
				m_player.activateShield();
			}
			else
			{
				m_player.activate360Shot();
			}

		}
	}
	
	
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Cyan);

	//m_window.setView(m_player.getView());
	m_world.render(m_window);
	m_grid.display(m_window);
	m_player.render(m_window);
	m_mapBorder.setPosition(m_player.getPos().x + 300, m_player.getPos().y + 200);
	for (Worker* workers : m_workers)
	{
		workers->render(m_window);
	}
	for (Powerup* powerup : m_powerups)
	{
		powerup->render(m_window);
	}
	
	//m_window.draw(m_mapBorder);

	//m_window.setView(m_miniMap);


	//m_miniMap.setCenter(m_player.getPos());
	m_window.draw(m_player.getSprite());
	for (Worker* workers : m_workers)
	{
		m_window.draw(workers->getSprite());
	}
	//m_miniMap.setViewport(sf::FloatRect(0.75, 0.75, 0.25, 0.25));

	m_window.display();
}