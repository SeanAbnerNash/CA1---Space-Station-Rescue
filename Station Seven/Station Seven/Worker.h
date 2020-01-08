#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
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
	float getNewOrientation(float t_rot, sf::Vector2f t_vel);
	float getLength(sf::Vector2f t_v);
	sf::Vector2f normalize(sf::Vector2f t_v);
	float dist(sf::Vector2f t_v1, sf::Vector2f t_v2);

	void wander(sf::Vector2f t_playerPos);
	void flee(sf::Vector2f t_playerPos);

private:
	ResourceManager& m_resourceMng;
	WORKERSTATE m_state;
	sf::Sprite m_workerSprite;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_spriteDimensions{ 100,100 };
	float m_rotation;
	const float PI = 3.14159265358979323846;
	const float MAX_SPEED = 1.5f;
	const float MAX_ROTATION = 4;
};