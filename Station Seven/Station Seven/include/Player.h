#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include <iostream>

class Player
{
public:
	Player(ResourceManager& t_resources);
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	float getPositionX();
	float getPositionY();
	void increaseRotation();
	void increaseSpeed();
	void decreaseSpeed();
	void decreaseRotation();
	sf::Vector2f getPos();
	sf::Vector2f getVel();
private:
	//Angle
	float m_angle;
	sf::Vector2f m_position;
	sf::CircleShape m_playerHitbox;
	sf::Texture m_texture;
	sf::Sprite m_playerSprite;
	ResourceManager& m_resourceMng;

	sf::Vector2f m_spriteDimensions{ 100,100 };
	float m_hitboxRadius{ 50 };
	sf::Vector2f m_velocity;
	float m_maxSpeed;
	float m_rotation;
	float m_speed;
	sf::Vector2f m_heading;
	const float  DEG_TO_RAD = 3.14f / 180.0f;
	
	//Position
	//Max Speed
	//Current Speed
	//Accelertion Per Second
	//Acceleration Ramp up
	//Deceleration per second
	//Angle Rotation Per second.


};

