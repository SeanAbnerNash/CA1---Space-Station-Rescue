#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "Worker.h"
#include "Maths.h"
// An enum that has all states the enemy can be in
enum State
{
	EVADE,
	PATROL,
	SEEK
};
class Sweeper
{
	public:
		Sweeper(sf::Vector2f t_pos,State t_state,ResourceManager& t_resources);
		~Sweeper();
		void update(sf::Time t_deltaTime, sf::Vector2f t_playerPos);
		void render(sf::RenderWindow& t_window);
		bool inLineofSight(std::vector<Worker*> t_workers);
		void wander(sf::Vector2f t_playerPos);
		void seek(sf::Vector2f t_playerPos);
		void flee(sf::Vector2f t_playerPos);
		void startCalc();
		void behaviourChange(sf::Vector2f t_playerPos);
		int m_collected = 0;
		sf::Vector2f getPosition();
	private:
		sf::Sprite m_sweeperSprite;
		sf::Vector2f m_position;
		sf::Vector2f m_velocity;
		ResourceManager& m_resourceMng;
		float m_rotation;
		sf::Vector2f m_spriteDimensions{ 100,100 };
		bool m_dead = false;	// Whether enemy is dead or not
		const float MAX_SPEED = 1.5f;
		const float MAX_ROTATION = 2;
		const float  DEG_TO_RAD = 3.14f / 180.0f;
		const double RAD_TO_DEG = 180.0f / 3.14159;
		float m_speed;
		State m_state;
		
};