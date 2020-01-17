#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "Missile.h"

class Wall
{
public:
	Wall(sf::Vector2f t_pos, ResourceManager& t_resources, sf::Vector2f t_size);
	~Wall();
	bool collisionWithSphere(sf::Vector2f t_pos, float t_radius);
	void render(sf::RenderWindow& t_window);
private:
	sf::RectangleShape m_shape;
	sf::Vector2f m_size;
	sf::Color m_colour{ 0,0,0 };
	sf::Vector2f m_position{ 0,0 };
	int m_gridLocation{ 0 };
	sf::Vector2f m_centre;
};

