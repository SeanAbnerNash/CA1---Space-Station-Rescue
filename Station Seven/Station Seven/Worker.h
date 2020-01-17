#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "Maths.h"
#define M_PI           3.14159265358979323846  /* pi */
#include <Thor/Vectors.hpp>

enum WORKERSTATE
{
	FLEE,
	WANDER,
};
class Worker
{
public:
	Worker(WORKERSTATE t_state, sf::Vector2f t_initialPos, ResourceManager& t_resources);
	~Worker();

	void update(sf::Vector2f t_playerPos, sf::Vector2f t_playerVel);
	void render(sf::RenderWindow& t_window);

	//calculations

	void wander(sf::Vector2f t_playerPos);
	void flee(sf::Vector2f t_playerPos);
	sf::Vector2f getPosition();
	sf::Sprite getSprite();
	sf::Vector2f m_position;
	bool m_isCollected;
private:
	ResourceManager& m_resourceMng;
	WORKERSTATE m_state;
	sf::Sprite m_workerSprite;
	
	sf::Vector2f m_velocity;
	sf::Vector2f m_spriteDimensions{ 100,100 };
	float m_rotation;

	const float MAX_SPEED = 1.5f;
	const float MAX_ROTATION = 2;
};