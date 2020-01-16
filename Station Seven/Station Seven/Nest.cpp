#include "Nest.h"

Nest::Nest(sf::Vector2f t_pos, ResourceManager& t_resources):
	m_position(t_pos),
	m_resourceMng(t_resources),
	m_dead(false),
	m_health(4)
{
	m_nestSprite.setTexture(m_resourceMng.getTexture(TextureID::NEST));
	m_nestSprite.setOrigin(m_nestSprite.getGlobalBounds().width / 2, m_nestSprite.getGlobalBounds().height / 2);
	m_nestSprite.setScale(100.0f / m_nestSprite.getGlobalBounds().width, 100.0f / m_nestSprite.getGlobalBounds().height);
	m_nestSprite.setPosition(m_position);
}

Nest::~Nest()
{
}

void Nest::update(sf::Time t_deltaTime, sf::Vector2f t_playerPos)
{
	//shoot missile
	for (int i = 0; i < m_missiles.size(); i++) {
		// Loop through missiles
		m_missiles.at(i)->update(t_deltaTime, t_playerPos);	// Update missiles
		if (m_missiles.at(i)->isDead()) 
		{
			// If missile is dead
			m_missiles.erase(m_missiles.begin() + i);	// Delete missile 
		}
	}
	//spawn enemies
}

void Nest::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_nestSprite);

	for (Missile* m : m_missiles) {
		m->render(t_window);	// Draw all the missiles
	}
}

void Nest::takeDamage(/*int& t_playerScore*/)
{
	m_health--;	// Deduct health 
	if (m_health <= 0) {
		// Checks if nest has run out of health
		m_dead = true;	// Set nest to be dead
		//t_playerScore += 20;
	}
}
void Nest::createMissile() 
{
	if (m_missiles.size() < 1) {
		// If missile is currently fired 
		m_missiles.push_back(new Missile(m_position, m_resourceMng));	// Fire missile
	}
}

sf::Vector2f Nest::getPosition()
{
	return m_position;
}

bool Nest::getDead()
{
	return m_dead;
}
