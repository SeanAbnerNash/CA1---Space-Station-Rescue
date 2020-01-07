#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include <iostream>
#include "Bullet.h"
#include <vector>

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
	sf::View getView();
	sf::Sprite getSprite();
private:
	void handleInput();
	void borderCheck();
	//Angle
	float m_angle;
	float m_maxSpeed;
	float m_rotation;
	float m_speed;
	float m_hitboxRadius{ 50 };

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_heading;
	sf::Vector2f m_spriteDimensions{ 100,100 };

	sf::CircleShape m_playerHitbox;
	sf::Texture m_texture;
	sf::Sprite m_playerSprite;

	ResourceManager& m_resourceMng;

	const float  DEG_TO_RAD = 3.14f / 180.0f;
	std::vector<Bullet*> m_bullets;
	sf::View m_view;
	int m_bulletCounter;
	int m_bulletTime = 15;
	//Position
	//Max Speed
	//Current Speed
	//Accelertion Per Second
	//Acceleration Ramp up
	//Deceleration per second
	//Angle Rotation Per second.


};

