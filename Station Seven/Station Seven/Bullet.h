#pragma once
#include <SFML\Graphics.hpp>
#include "ResourceManager.h"

class Bullet
{
public:

	Bullet(sf::Vector2f t_position, float t_rototation, ResourceManager& t_resources);

	~Bullet() { delete this; }

	void update();
	void render(sf::RenderWindow& window);
	int getLifetime();
	const int BULLET_MAX_LIFE = 100;
private:

	sf::Vector2f m_position;
	float m_rotation;

	sf::Vector2f m_acceleration;
	int m_lifeTime;
	int m_speed;
	sf::Sprite m_bulletSprite;
	const double DEG_TO_RAD = 3.14159 / 180.0f;

	ResourceManager& m_resourceMng;
};