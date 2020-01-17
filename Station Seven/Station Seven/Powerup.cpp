#include "Powerup.h"

/// <summary>
/// powerup constuctor
/// setting up physical attributes of powerups 
/// </summary>
/// <param name="t_pos"></param>
/// <param name="t_type"></param>
/// <param name="t_resources"></param>
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
/// <summary>
/// powerup destructor
/// </summary>
Powerup::~Powerup()
{
}
/// <summary>
/// if alive draw powerups
/// </summary>
/// <param name="t_window"></param>
void Powerup::render(sf::RenderWindow& t_window)
{
	if (m_isAlive)
	{
		t_window.draw(m_powerupSprite);
	}
}

/// <summary>
/// simple update of powerups
/// </summary>
void Powerup::update()
{
	m_powerupSprite.setRotation(m_powerupSprite.getRotation() + 1);
}
/// <summary>
/// make powerup alive
/// </summary>
/// <param name="t_alive"></param>
void Powerup::setAlive(bool t_alive)
{
	m_isAlive = t_alive;
}
/// <summary>
/// check if alive
/// </summary>
/// <returns></returns>
bool Powerup::getAlive()
{
	return m_isAlive;
}
/// <summary>
/// return the type of powerup
/// </summary>
/// <returns></returns>
POWERUPTYPE Powerup::getPowerupType()
{
	return m_powerUpType;
}

/// <summary>
/// collision detection between player and powerup
/// </summary>
/// <param name="t_playerPos"></param>
/// <returns></returns>
bool Powerup::collisionDetection(sf::Vector2f t_playerPos)
{
	if (Maths::dist(m_position, t_playerPos) < 80 && m_isAlive) 
	{
		// Checks if player hit pick up
		return true;
	}
	else
	{
		return false;
	}
	
}
