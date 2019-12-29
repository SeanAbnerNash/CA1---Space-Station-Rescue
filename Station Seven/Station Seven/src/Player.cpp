#include "Player.h"

Player::Player(ResourceManager& t_resources) :
	m_resourceMng(t_resources)
{
	m_playerHitbox.setRadius(m_hitboxRadius);
	m_playerHitbox.setOrigin(m_hitboxRadius, m_hitboxRadius);	

	m_playerSprite.setTexture(m_resourceMng.getTexture(TextureID::PLAYERSPRITE));
	m_playerSprite.setOrigin(m_playerSprite.getLocalBounds().width / 2.0f, m_playerSprite.getLocalBounds().height / 2.0f);
	m_position = sf::Vector2f(300, 300);
	m_playerSprite.setScale(m_spriteDimensions.x /m_playerSprite.getGlobalBounds().width, m_spriteDimensions.y / m_playerSprite.getGlobalBounds().height);
	m_playerSprite.setPosition(m_position);
	m_playerHitbox.setFillColor(sf::Color::Black);
	m_playerHitbox.setPosition(m_position);
}

void Player::update(sf::Time t_deltaTime)
{
	//m_angle = 90;
	//m_playerSprite.setRotation(m_angle);
}

void Player::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_playerHitbox);
	t_window.draw(m_playerSprite);

}
