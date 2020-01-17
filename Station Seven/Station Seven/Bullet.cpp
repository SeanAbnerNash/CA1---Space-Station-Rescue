#include "Bullet.h"

/// <summary>
/// bullet constructor
/// </summary>
/// <param name="t_position"></param>
/// <param name="t_rotation"></param>
/// <param name="t_resources"></param>
Bullet::Bullet(sf::Vector2f t_position, float t_rotation, ResourceManager& t_resources):
	m_position(t_position),
	m_rotation(t_rotation),
	m_resourceMng(t_resources)
{
	m_speed = 15;
	m_bulletSprite.setTexture(m_resourceMng.getTexture(TextureID::BULLET));
	m_bulletSprite.setOrigin(m_bulletSprite.getLocalBounds().width / 2 -45, m_bulletSprite.getLocalBounds().height / 2);
	m_lifeTime = 0;

	m_bulletSprite.setPosition(m_position);
	m_bulletSprite.setRotation(m_rotation);
}
/// <summary>
/// function to update the bullet
/// </summary>
void Bullet::update() {
	m_acceleration = sf::Vector2f(std::cos(DEG_TO_RAD * (m_rotation)) * m_speed,
		std::sin(DEG_TO_RAD * (m_rotation)) * m_speed);
	m_position += m_acceleration;

	m_lifeTime++;
	m_bulletSprite.setPosition(m_position);
}
/// <summary>
/// function to render the bullet sprite
/// </summary>
/// <param name="window"></param>
void Bullet::render(sf::RenderWindow& window)
{
	window.draw(m_bulletSprite);
}
/// <summary>
/// function to get the lifetime of bullet
/// </summary>
/// <returns></returns>
int Bullet::getLifetime()
{
	return m_lifeTime;
}
/// <summary>
/// return position of bullet
/// </summary>
/// <returns></returns>
sf::Vector2f Bullet::getPosition()
{
	return m_position;
}
