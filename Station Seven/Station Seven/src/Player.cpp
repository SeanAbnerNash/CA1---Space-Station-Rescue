#include "Player.h"

/// <summary>
/// Player Contructor
/// setting up physical attributes of player object
/// </summary>
/// <param name="t_resources"></param>
Player::Player(ResourceManager& t_resources) :
	m_resourceMng(t_resources),
	m_velocity(0, 0),
	m_position(1000, 500),
	m_speed(0),
	m_maxSpeed(750),
	m_rotation(90),
	m_heading(0, 0),
	m_workerCollected(0),
	m_health(100)
{
	initPlayer();


	//setting size of main view
	m_view.setSize(1500, 1000);
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
	////circle for player hitbox
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

	m_shieldShape.setRadius(m_playerHitbox.getRadius());
	m_shieldShape.setFillColor(sf::Color(0, 0, 255, 125));
	m_shieldShape.setOutlineThickness(2);
	m_shieldShape.setOutlineColor(sf::Color(255, 0, 255, 125));
	m_shieldShape.setOrigin(m_playerHitbox.getOrigin());
	m_shieldShape.setPosition(m_playerSprite.getPosition());

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
	if (m_shieldActive)
	{
		m_shieldTime = m_shieldClock.getElapsedTime();

		if (m_shieldTime.asSeconds() > 10)
		{
			m_shieldClock.restart();
			m_shieldActive = false;
		}
	}
	m_shieldShape.setPosition(m_playerSprite.getPosition());
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B) == true && m_bombCollected)
	{
		for (int i = 0; i < 360; i += 15) {
			// Spawn ring of bullets around player
			m_bullets.push_back(new Bullet(m_playerSprite.getPosition(), i, m_resourceMng));
			m_bombCollected = false;	// Player has used up his ability
		}

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
	//window.draw(m_playerHitbox);
	window.draw(m_playerSprite);
	for (Bullet* bullet : m_bullets) 
	{
		if (bullet) 
		{
			bullet->render(window);
		}

	}
	if (m_shieldActive)
	{
		window.draw(m_shieldShape);
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
void Player::playerWorkerCollision(std::vector<Worker*> *t_worker)
{
	for(int i=0;i<t_worker->size();++i)
	{
		if (Maths::dist(m_playerSprite.getPosition(), t_worker->at(i)->getPosition()) < 45)
		{
			
			t_worker->at(i)->m_isCollected = true;
			m_workerCollected++;
			std::cout << "player has workers " << m_workerCollected << std::endl;
		}
		//if (m_playerSprite.getGlobalBounds().intersects(t_worker->at(i)->getSprite().getGlobalBounds()))
		//{

		//	//std::cout << "collected" << std::endl;
		//}
	}

}
/// <summary>
/// activate shield arounmd dplayer
/// </summary>
/// <returns></returns>
void Player::activateShield()
{
	if (!m_shieldActive)
	{
		m_shieldClock.restart();
		m_shieldActive = true;
	}
	else
	{
		m_shieldClock.restart();
	}
}

/// <summary>
/// activate 360 shot radius shot around player
/// </summary>
/// <returns></returns>
void Player::activate360Shot()
{
	m_bombCollected = true;
}

/// <summary>
/// collision detection check between player and nests
/// </summary>
/// <param name="nest"></param>
void Player::checkNest(Nest& nest) 
{
	
	if (Maths::dist(m_playerSprite.getPosition(), nest.m_position) < 500)
	{
		// Checks if player is close to the nest
		nest.createMissile();	// Nest fires bullet at player
	}
	for (int i = 0; i < m_bullets.size(); i++) {
		// Loops through all of the player bullets
		if (Maths::dist(m_bullets.at(i)->getPosition(), nest.getPosition()) < 50) {
			// Checks to see if a bullet has hit the nest
			nest.takeDamage();	// Nest loses health
			m_bullets.erase(m_bullets.begin() + i);	// Delete bullet
		}

	}
}
/// <summary>
/// collision detection check between player and sweepers
/// </summary>
/// </summary>
/// <param name="t_sweepers"></param>
void Player::checkSweepers(std::vector<Sweeper*>& t_sweepers)
{
	for (int i = 0; i < m_bullets.size(); ++i) {
		for (int j = 0; j < t_sweepers.size(); ++j) {
			// Loops through all the sweeper bots
			if (m_bullets.size() > i && Maths::dist(m_bullets.at(i)->getPosition(), t_sweepers.at(j)->getPosition()) < 75) {
				// Checks if bullet has hit enemy
				m_workerCollected += t_sweepers.at(j)->m_collected;	// Player gets any worker that sweeper has collected
				t_sweepers.erase(t_sweepers.begin() + j);	// Delete sweeper
				m_bullets.erase(m_bullets.begin() + i);	// Delete bullet
			}
		}
	}
}
