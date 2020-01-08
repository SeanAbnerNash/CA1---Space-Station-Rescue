#include "Player.h"

/// <summary>
/// Player Contructor
/// setting up physical attributes of player object
/// </summary>
/// <param name="t_resources"></param>
Player::Player(ResourceManager& t_resources) :
	m_resourceMng(t_resources),
	m_velocity(0, 0),
	m_position(0, 0),
	m_speed(0),
	m_maxSpeed(750),
	m_rotation(90),
	m_heading(0, 0)
{
	initPlayer();
	//setting size of main view
	m_view.setSize(1200, 800);
}
/// <summary>
/// Player destructor
/// </summary>
Player::~Player()
{
}

/// <summary>
/// initialising the player
/// </summary>
void Player::initPlayer()
{
	//circle for player hitbox
	m_playerHitbox.setRadius(m_hitboxRadius);
	m_playerHitbox.setOrigin(m_hitboxRadius, m_hitboxRadius);

	//setting all textures,origins,scale for player object
	m_playerSprite.setTexture(m_resourceMng.getTexture(TextureID::PLAYERSPRITE));
	m_playerSprite.setOrigin(m_playerSprite.getLocalBounds().width / 2.0f, m_playerSprite.getLocalBounds().height / 2.0f);
	m_playerSprite.setScale(m_spriteDimensions.x / m_playerSprite.getGlobalBounds().width, m_spriteDimensions.y / m_playerSprite.getGlobalBounds().height);
	//
	m_playerSprite.setPosition(m_position);
	m_playerHitbox.setFillColor(sf::Color::Black);
	m_playerHitbox.setPosition(m_position);

}
/// <summary>
/// updating the physics of player,
/// handling input,
/// </summary>
/// <param name="t_deltaTime"></param>
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

	for (Bullet* bullet : m_bullets) 
	{
		bullet->update();
		if (bullet->getLifetime() > bullet->BULLET_MAX_LIFE) 
		{
			m_bullets.erase(m_bullets.begin());
		}
	}
	//std::cout << "x" << m_playerSprite.getPosition().x << " " << "y" << m_playerSprite.getPosition().y << std::endl;
}

/// <summary>
/// checking for keyboard input for movement and shooting bullets and handling it
/// </summary>
void Player::handleInput()
{
	m_bulletCounter++;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) == true && m_bulletCounter > m_bulletTime)
	{
		m_bulletCounter = 0;
		m_bullets.push_back(new Bullet(m_playerSprite.getPosition(), m_playerSprite.getRotation() + 90, m_resourceMng));
	}
}
/// <summary>
/// border checking and loop the player object
/// </summary>
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

/// <summary>
/// renders everything
/// </summary>
/// <param name="window"></param>
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
/// <summary>
/// get Xposition of player
/// </summary>
/// <returns></returns>
float Player::getPositionX()
{
	return m_position.x;
}
/// <summary>
/// get Yposition of player
/// </summary>
/// <returns></returns>
float Player::getPositionY()
{
	return m_position.y;
}
/// <summary>
/// increase rotation of player ship
/// </summary>
void Player::increaseRotation()
{
	m_rotation += 3.0f;
}
/// <summary>
/// increase speed of player ship
/// </summary>
void Player::increaseSpeed()
{
	if (m_speed < m_maxSpeed)
	{
		m_speed += 10.0f;
	}
}
/// <summary>
/// decrease speed of player ship
/// </summary>
void Player::decreaseSpeed()
{
	if (m_speed > 0.0f)
	{
		m_speed -= 10.0f;
	}
}
/// <summary>
/// decrease rotation of player ship
/// </summary>
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
/// <summary>
/// get Position of player sprite
/// </summary>
/// <returns></returns>
sf::Vector2f Player::getPos()
{
	return m_playerSprite.getPosition();
}
/// <summary>
/// get velocity of player sprite
/// </summary>
/// <returns></returns>
sf::Vector2f Player::getVel()
{
	return sf::Vector2f(m_velocity.x, m_velocity.y);
}
/// <summary>
/// get the main view of player sprite
/// </summary>
/// <returns></returns>
sf::View Player::getView()
{
	return m_view;
}
/// <summary>
/// get the player sprite
/// </summary>
/// <returns></returns>
sf::Sprite Player::getSprite()
{
	return m_playerSprite;
}
/// <summary>
/// collision detection check between player and workers
/// </summary>
/// <param name="t_workers"></param>
void Player::playerWorkerCollision(std::vector<Worker*> *t_workers)
{
	//TODO: doesnt really work need to work on it
	for (int i = 0; i< t_workers->size(); ++i)
	{
		if (Maths::dist(m_position, t_workers->at(i)->getPosition()) < 100)
		{
			std::cout << "worker collected" << std::endl;
			t_workers->erase(t_workers->begin() + i);
			//++m_workerCollected;
		}
	}
}
