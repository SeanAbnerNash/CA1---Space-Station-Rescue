#include "game.h"
#include <iostream>

static sf::Int32 MS_PER_UPDATE = 10.0;

Game::Game() :
	m_window{ sf::VideoMode{ 1200, 800, 32 }, "SFML Game" },
	m_player(m_resourceMng),
	m_exitGame{false} //when true game will exit
{
	m_window.setFramerateLimit(60);
	m_mapBorder.setOutlineThickness(10.0f);
	m_mapBorder.setOutlineColor(sf::Color::Black);
	m_mapBorder.setSize(sf::Vector2f(300, 200));

	m_workers.push_back(new Worker(WORKERSTATE::WANDER, sf::Vector2f(200, 200), m_resourceMng));
	m_workers.push_back(new Worker(WORKERSTATE::FLEE, sf::Vector2f(300, 200), m_resourceMng));
}


Game::~Game()
{
}


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
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	m_player.update(t_deltaTime);
	for (Worker* workers : m_workers)
	{
		workers->update(m_player.getPos(),m_player.getVel());
	}
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.setView(m_player.getView());
	m_player.render(m_window);
	m_mapBorder.setPosition(m_player.getPos().x + 300, m_player.getPos().y + 200);
	for (Worker* workers : m_workers)
	{
		workers->render(m_window);
	}
	m_window.draw(m_mapBorder);

	m_window.setView(m_miniMap);


	m_miniMap.setCenter(m_player.getPos());
	m_window.draw(m_player.getSprite());
	m_miniMap.setViewport(sf::FloatRect(0.75, 0.75, 0.25, 0.25));
	m_window.display();
}