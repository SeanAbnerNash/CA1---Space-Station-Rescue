#include "Bullet.h"

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

void Bullet::update() {
	m_acceleration = sf::Vector2f(std::cos(DEG_TO_RAD * (m_rotation)) * m_speed,
		std::sin(DEG_TO_RAD * (m_rotation)) * m_speed);
	m_position += m_acceleration;

	m_lifeTime++;
	m_bulletSprite.setPosition(m_position);
}

void Bullet::render(sf::RenderWindow& window)
{
	window.draw(m_bulletSprite);
}

int Bullet::getLifetime()
{
	return m_lifeTime;
}
