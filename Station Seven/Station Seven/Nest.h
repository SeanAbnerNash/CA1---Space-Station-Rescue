#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "Missile.h"
class Nest
{
	public:
		Nest(sf::Vector2f t_pos,ResourceManager& t_resources);
		~Nest();
		void update(sf::Time t_deltaTime, sf::Vector2f t_playerPos);
		void render(sf::RenderWindow& t_window);
		void takeDamage(/*int& t_playerScore*/);
		void createMissile();
		sf::Vector2f getPosition();
		bool getDead();
	private:
		ResourceManager& m_resourceMng;
		sf::Vector2f m_position;
		int m_health;
		bool m_dead;
		sf::Sprite m_nestSprite;
		std::vector<Missile*> m_missiles;	// The  vector of missiles
};