#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "Maths.h"

struct pathing 
{
	sf::Vector2f linear;
	float angular;
};

class Missile
{
public:
	Missile(sf::Vector2f t_pos, ResourceManager& t_resources);
	~Missile();
	void update(sf::Time t_deltaTime,sf::Vector2f t_playerPos);
	void render(sf::RenderWindow& t_window);
	pathing seek(sf::Vector2f t_playerPos);
	bool isDead();
private:
	// Time and clock for checking how long missile has been alive
	sf::Time m_time;
	sf::Clock m_clock;
	ResourceManager& m_resourceMng;
	// Physical attributes
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_rotation;
	bool m_dead;
	float m_speed;
	float m_maxSpeed;
	const float  DEG_TO_RAD = 3.14f / 180.0f;
	sf::Sprite m_missileSprite;
	pathing steer;
	void startCalc();
};