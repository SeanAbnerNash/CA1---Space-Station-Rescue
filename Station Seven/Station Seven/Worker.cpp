#include "Worker.h"

Worker::Worker(WORKERSTATE t_state, sf::Vector2f t_initialPos, ResourceManager& t_resources):
	m_state(t_state),
	m_position(t_initialPos),
	m_resourceMng(t_resources),
	m_velocity(sf::Vector2f(0, 0)),
	m_rotation(0)
{
	srand(time(0));
	m_workerSprite.setTexture(m_resourceMng.getTexture(TextureID::PLAYERSPRITE));
	m_workerSprite.setOrigin(m_workerSprite.getLocalBounds().width / 2, m_workerSprite.getLocalBounds().height / 2);
	m_workerSprite.setScale(m_spriteDimensions.x / m_workerSprite.getGlobalBounds().width, m_spriteDimensions.y / m_workerSprite.getGlobalBounds().height);
	m_workerSprite.setPosition(m_position);
}

Worker::~Worker()
{
}

void Worker::update(sf::Vector2f t_playerPos, sf::Vector2f t_playerVel)
{
	switch (m_state)
	{
	case FLEE:
		flee(t_playerPos);
		break;
	case WANDER:
		wander(t_playerPos);
		break;
		break;
	}
	m_position += m_velocity;
	m_workerSprite.setPosition(m_position);
	m_workerSprite.setRotation(m_rotation);
}

void Worker::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_workerSprite);
}

float Worker::getNewOrientation(float t_rot, sf::Vector2f t_vel)
{
	if (getLength(t_vel) > 0)
	{
		return (atan2(t_vel.y, t_vel.x)) * (180 / PI);
	}
	else
	{
		return t_rot;
	}
}

float Worker::getLength(sf::Vector2f t_v)
{
	return sqrt((t_v.x * t_v.x) + (t_v.y * t_v.y));
}

sf::Vector2f Worker::normalize(sf::Vector2f t_v)
{
	float length = getLength(t_v);

	if (length != 0)
	{
		t_v.x = t_v.x / length;
		t_v.y = t_v.y / length;
	}
	return t_v;
}

float Worker::dist(sf::Vector2f t_v1, sf::Vector2f t_v2)
{
	float distance = std::sqrt(((t_v1.x - t_v2.x) * (t_v1.x - t_v2.x)) + ((t_v1.y - t_v2.y) * (t_v1.y - t_v2.y)));
	return distance;
}

void Worker::wander(sf::Vector2f t_playerPos)
{
	int m_randomDirection = (rand() % 3) - 1;

	m_rotation += (MAX_ROTATION * m_randomDirection);

	float magnitude = getLength(m_velocity);
	sf::Vector2f direction = sf::Vector2f(std::cos(m_rotation * (PI / 180)), std::sin(m_rotation) * (PI / 180));
	m_velocity = magnitude * (sf::Vector2f(std::cos(m_rotation * (PI / 180)), std::sin(m_rotation * (PI / 180))));
	m_velocity += direction;

	if (MAX_SPEED < magnitude)
	{
		m_velocity = direction * MAX_SPEED;

	}
	m_workerSprite.setRotation(m_rotation);
}

void Worker::flee(sf::Vector2f t_playerPos)
{
	m_velocity = m_position - t_playerPos;
	m_velocity = normalize(m_velocity);
	m_velocity *= MAX_SPEED;
	m_rotation = getNewOrientation(m_rotation, m_velocity);
	m_workerSprite.setRotation(m_rotation);
}
