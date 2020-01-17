#include "Missile.h"

Missile::Missile(sf::Vector2f t_pos, ResourceManager& t_resources):
	m_position(t_pos),
	m_resourceMng(t_resources),
	m_speed(1.5),
	m_maxSpeed(750),
	m_rotation(0),
	m_dead(false)
{

	m_missileSprite.setTexture(m_resourceMng.getTexture(TextureID::MISSILE));
	m_missileSprite.setOrigin(m_missileSprite.getGlobalBounds().width / 2, m_missileSprite.getGlobalBounds().height / 2);
	m_missileSprite.setScale(100.0f / m_missileSprite.getGlobalBounds().width, 100.0f / m_missileSprite.getGlobalBounds().height);
	//m_missileSprite.setPosition(m_position);
}

Missile::~Missile()
{
}

void Missile::update(sf::Time t_deltaTime,sf::Vector2f t_playerPos)
{
	steer = seek(t_playerPos);

	// Assigns this steer to the missile
	m_position += steer.linear;
	m_missileSprite.setPosition(m_position);

	// Update position based on velocity
	m_position = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD * (m_rotation)) * m_speed,
		m_position.y + std::sin(DEG_TO_RAD * (m_rotation)) * m_speed);

	if (Maths::dist(t_playerPos, m_position) < 45) {
		// If missile has hit player
		//t_health = t_health - 15;	// Hurt the player
		std::cout << "missile hit player" << std::endl;
		m_dead = true;	// Missile is dead
	}
	// Update time
	m_time += m_clock.restart();
	if (m_time.asSeconds() > 5) {
		// If 5 seconds have passed since missile was spawned
		m_dead = true;	// Destroy missile
	}
}

void Missile::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_missileSprite);	// Draw the missile
}

pathing Missile::seek(sf::Vector2f t_playerPos)
{
	m_velocity = t_playerPos - m_position;
	startCalc();
	m_missileSprite.setRotation(m_rotation);

	pathing seekSteering;
	seekSteering.linear = m_velocity;
	seekSteering.angular = 0.0;
	return seekSteering;
}

bool Missile::isDead()
{
	return m_dead;
}
/// <summary>
/// Function for updating all movement attributes of the missile
/// </summary>
void Missile::startCalc() 
{
	if (m_velocity.x != 0 || m_velocity.y != 0)
	{
		float magnitude = Maths::getLength(m_velocity);
		m_velocity = sf::Vector2f(m_velocity.x / magnitude, m_velocity.y / magnitude);
		m_velocity = m_velocity * m_speed;
		m_rotation = Maths::getNewOrientation(m_rotation, m_velocity);
	}

}