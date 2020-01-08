#include "Worker.h"

/// <summary>
/// Constructor for workers
/// </summary>
/// <param name="t_state"></param>
/// <param name="t_initialPos"></param>
/// <param name="t_resources"></param>
Worker::Worker(WORKERSTATE t_state, sf::Vector2f t_initialPos, ResourceManager& t_resources):
	m_state(t_state),
	m_position(t_initialPos),
	m_resourceMng(t_resources),
	m_velocity(sf::Vector2f(0, 0)),
	m_rotation(0)
{
	srand(time(0));
	m_workerSprite.setTexture(m_resourceMng.getTexture(TextureID::WORKER));
	m_workerSprite.setOrigin(m_workerSprite.getLocalBounds().width / 2, m_workerSprite.getLocalBounds().height / 2);
	m_workerSprite.setScale(m_spriteDimensions.x / m_workerSprite.getGlobalBounds().width, m_spriteDimensions.y / m_workerSprite.getGlobalBounds().height);
	m_workerSprite.setPosition(m_position);
}
/// <summary>
/// destructor for workers
/// </summary>
Worker::~Worker()
{
}
/// <summary>
/// update for the workers
/// </summary>
/// <param name="t_playerPos"></param>
/// <param name="t_playerVel"></param>
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
	default:
		break;
	}
	m_position += m_velocity;
	m_workerSprite.setPosition(m_position);
	m_workerSprite.setRotation(m_rotation);
}
/// <summary>
/// handle rendering of workers sprite
/// </summary>
/// <param name="t_window"></param>
void Worker::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_workerSprite);
}
/// <summary>
/// wander function of the workers
/// </summary>
/// <param name="t_playerPos"></param>
void Worker::wander(sf::Vector2f t_playerPos)
{
	int m_randomDirection = (rand() % 3) - 1;

	m_rotation += (MAX_ROTATION * m_randomDirection);

	float magnitude = Maths::getLength(m_velocity);
	sf::Vector2f direction = sf::Vector2f(std::cos(m_rotation * (PI / 180)), std::sin(m_rotation) * (PI / 180));
	m_velocity = magnitude * (sf::Vector2f(std::cos(m_rotation * (PI / 180)), std::sin(m_rotation * (PI / 180))));
	m_velocity += direction;

	if (MAX_SPEED < magnitude)
	{
		m_velocity = direction * MAX_SPEED;

	}
	m_workerSprite.setRotation(m_rotation);
	std::cout << m_position.x << m_position.y << std::endl;
}
/// <summary>
/// fleeing function of the workers
/// </summary>
/// <param name="t_playerPos"></param>
void Worker::flee(sf::Vector2f t_playerPos)
{
	m_velocity = m_position - t_playerPos;
	m_velocity = Maths::normalize(m_velocity);
	m_velocity *= MAX_SPEED;
	m_rotation = Maths::getNewOrientation(m_rotation, m_velocity);
	m_workerSprite.setRotation(m_rotation);
}
/// <summary>
/// get position function of the workers object
/// </summary>
/// <returns></returns>
sf::Vector2f Worker::getPosition()
{
	return m_position;
}
/// <summary>
/// get sprite of the workers object
/// </summary>
/// <returns></returns>
sf::Sprite Worker::getSprite()
{
	return m_workerSprite;
}
