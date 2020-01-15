#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "Maths.h"
#define M_PI           3.14159265358979323846  /* pi */
#include <Thor/Vectors.hpp>

class World
{
public:
	World(ResourceManager& t_resources);
	~World();

	void update(sf::Vector2f t_playerPos, sf::Vector2f t_playerVel);
	void render(sf::RenderWindow& t_window);

	//calculations

	sf::Vector2f getPosition();
	sf::Sprite getSprite();
private:
	std::vector<sf::Sprite> m_map;
	ResourceManager& m_resourceMng;
};

