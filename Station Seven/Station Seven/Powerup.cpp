#include "Powerup.h"

Powerup::Powerup(sf::Vector2f t_pos, POWERUPTYPE t_type, ResourceManager& t_resources):
	m_position(t_pos),
	m_powerUpType(t_type),
	m_resourceMng(t_resources),
	m_isAlive(true)
{
	m_powerupSprite.setPosition(m_position);
	
	if (m_powerUpType == POWERUPTYPE::SHIELD)
	{
		m_powerupSprite.setTexture(m_resourceMng.getTexture(TextureID::SHIELD));
		m_powerupSprite.setOrigin(m_powerupSprite.getLocalBounds().width / 2.0f, m_powerupSprite.getLocalBounds().height / 2.0f);
		m_powerupSprite.setScale(m_spriteDimensions.x / m_powerupSprite.getGlobalBounds().width, m_spriteDimensions.y / m_powerupSprite.getGlobalBounds().height);
	}
	else
	{
		m_powerupSprite.setTexture(m_resourceMng.getTexture(TextureID::BOMB));
		m_powerupSprite.setOrigin(m_powerupSprite.getLocalBounds().width / 2.0f, m_powerupSprite.getLocalBounds().height / 2.0f);
		m_powerupSprite.setScale(m_spriteDimensions.x / m_powerupSprite.getGlobalBounds().width, m_spriteDimensions.y / m_powerupSprite.getGlobalBounds().height);
	}
}

Powerup::~Powerup()
{
}

void Powerup::render(sf::RenderWindow& t_window)
{
	if (m_isAlive)
	{
		t_window.draw(m_powerupSprite);
	}
}

void Powerup::update()
{
	m_powerupSprite.setRotation(m_powerupSprite.getRotation() + 1);
}

void Powerup::setAlive(bool t_alive)
{
	m_isAlive = t_alive;
}

bool Powerup::getAlive()
{
	return m_isAlive;
}

POWERUPTYPE Powerup::getPowerupType()
{
	return m_powerUpType;
}

bool Powerup::collisionDetection(sf::Sprite t_player)
{
	if (m_isAlive)
	{
		return t_player.getGlobalBounds().intersects(m_powerupSprite.getGlobalBounds());
	}
	else
	{
		return false;
	}
	
}
