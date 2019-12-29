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

	
	//Position
	//Max Speed
	//Current Speed
	//Accelertion Per Second
	//Acceleration Ramp up
	//Deceleration per second
	//Angle Rotation Per second.


};

