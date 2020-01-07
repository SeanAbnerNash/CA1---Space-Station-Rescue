#include "Player.h"

Player::Player(ResourceManager& t_resources) :
	m_resourceMng(t_resources),
	m_velocity(0, 0),
	m_position(300, 300),
	m_speed(0),
	m_maxSpeed(750),
	m_rotation(90),
	m_heading(0, 0)
{
	m_playerHitbox.setRadius(m_hitboxRadius);
	m_playerHitbox.setOrigin(m_hitboxRadius, m_hitboxRadius);	

	m_playerSprite.setTexture(m_resourceMng.getTexture(TextureID::PLAYERSPRITE));
	m_playerSprite.setOrigin(m_playerSprite.getLocalBounds().width / 2.0f, m_playerSprite.getLocalBounds().height / 2.0f);
	m_playerSprite.setScale(m_spriteDimensions.x /m_playerSprite.getGlobalBounds().width, m_spriteDimensions.y / m_playerSprite.getGlobalBounds().height);
	m_playerSprite.setPosition(m_position);
	m_playerHitbox.setFillColor(sf::Color::Black);
	m_playerHitbox.setPosition(m_position);

	m_view.setSize(1200, 800);
}

void Player::update(sf::Time t_deltaTime)
{
	handleInput();
	borderCheck();
	m_heading.x = cos(m_rotation * (DEG_TO_RAD));
	m_heading.y = sin(m_rotation * (DEG_TO_RAD));
	m_playerSprite.setPosition((m_playerSprite.getPosition().x + m_heading.x * m_speed * t_deltaTime.asMilliseconds() / 1000),
		(m_playerSprite.getPosition().y + m_heading.y * m_speed * t_deltaTime.asMilliseconds() / 1000));
	m_playerHitbox.setPosition((m_playerSprite.getPosition().x + m_heading.x * m_speed * t_deltaTime.asMilliseconds() / 1000),
		(m_playerSprite.getPosition().y + m_heading.y * m_speed * t_deltaTime.asMilliseconds() / 1000));
	m_playerSprite.setRotation(m_rotation - 90);

	for (Bullet* bullet : m_bullets) {
		bullet->update();
		if (bullet->getLifetime() > bullet->BULLET_MAX_LIFE) 
		{
			m_bullets.erase(m_bullets.begin());
		}
	}
	//std::cout << "x" << m_playerSprite.getPosition().x << " " << "y" << m_playerSprite.getPosition().y << std::endl;
}


void Player::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) == true)
	{
		increaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) == true)
	{
		decreaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) == true)
	{
		increaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) == true)
	{
		decreaseRotation();

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) == true)
	{
		m_bullets.push_back(new Bullet(m_playerSprite.getPosition(), m_playerSprite.getRotation() + 90, m_resourceMng));
	}
}

void Player::borderCheck()
{
	////Window checking
	//if (m_playerSprite.getPosition().x > 1200)
	//{
	//	m_playerSprite.setPosition(-200, m_playerSprite.getPosition().y);
	//}
	//if (m_playerSprite.getPosition().y > 800)
	//{
	//	m_playerSprite.setPosition(m_playerSprite.getPosition().x, -200);
	//}
	//if (m_playerSprite.getPosition().x < -200)
	//{
	//	m_playerSprite.setPosition(1200, m_playerSprite.getPosition().y);
	//}
	//if (m_playerSprite.getPosition().y < -200)
	//{
	//	m_playerSprite.setPosition(m_playerSprite.getPosition().x, 800);
	//}
}


void Player::render(sf::RenderWindow& window)
{
	m_view.setCenter(m_playerSprite.getPosition());
	window.setView(m_view);
	window.draw(m_playerHitbox);
	window.draw(m_playerSprite);
	for (Bullet* bullet : m_bullets) {
		if (bullet) 
		{
			bullet->render(window);
		}

	}
}

float Player::getPositionX()
{
	return m_position.x;
}

float Player::getPositionY()
{
	return m_position.y;
}

void Player::increaseRotation()
{
	m_rotation += 3.0f;
}

void Player::increaseSpeed()
{
	if (m_speed < m_maxSpeed)
	{
		m_speed += 10.0f;
	}
}

void Player::decreaseSpeed()
{
	if (m_speed > 0.0f)
	{
		m_speed -= 10.0f;
	}
}

void Player::decreaseRotation()
{
	if (m_rotation != 0.0f)
	{
		m_rotation -= 3.0f;
	}
	else
	{
		m_rotation = 359.0f;
	}

}

sf::Vector2f Player::getPos()
{
	return m_playerSprite.getPosition();
}

sf::Vector2f Player::getVel()
{
	return sf::Vector2f(m_velocity.x, m_velocity.y);
}

sf::View Player::getView()
{
	return m_view;
}

sf::Sprite Player::getSprite()
{
	return m_playerSprite;
}
