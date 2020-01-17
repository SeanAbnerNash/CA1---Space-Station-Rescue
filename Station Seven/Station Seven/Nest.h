#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "Missile.h"
#include "Sweeper.h"
class Nest
{
	public:
		Nest(sf::Vector2f t_pos,ResourceManager& t_resources);
		~Nest();
		void update(sf::Time t_deltaTime, sf::Vector2f t_playerPos,std::vector<Worker*> t_workers, int& t_playerHealth);
		void render(sf::RenderWindow& t_window);
		void takeDamage(/*int& t_playerScore*/);
		void createSweeper();
		void createMissile();
		sf::Vector2f getPosition();
		bool getDead();
		sf::Vector2f m_position;
		std::vector<Missile*> m_missiles;	// The  vector of missiles
		std::vector<Sweeper*> m_sweepers;	// The nests vector of enemies
	private:
		ResourceManager& m_resourceMng;
		int m_sweeperTimer;
		int m_health;
		bool m_dead;
		sf::Sprite m_nestSprite;
		
};