#include "Nest.h"

/// <summary>
/// Nest Contructor
/// setting up physical attributes of player object
/// </summary>
/// <param name="t_pos"></param>
/// <param name="t_resources"></param>
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

/// <summary>
/// Nest destructor
/// </summary>
Nest::~Nest()
{
}

/// <summary>
/// updating the nest functionality 
/// missile update
/// </summary>
/// <param name="t_deltaTime"></param>
/// <param name="t_playerPos"></param>
void Nest::update(sf::Time t_deltaTime, sf::Vector2f t_playerPos, std::vector<Worker*> t_workers)
{
	m_sweeperTimer++;
	if (m_sweeperTimer > 100 && m_sweepers.size() < 5)
	{
		createSweeper();	// Spawn sweeper
	}
	for (Sweeper* sweeper : m_sweepers) {
		// Loop through enemies

		sweeper->update(t_deltaTime,t_playerPos);	// Update sweeper
		sweeper->inLineofSight(t_workers);	// Have enemies check if worker is in line of sight
	}
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

/// <summary>
/// drawing of the nest and missiles
/// </summary>
/// <param name="t_window"></param>
void Nest::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_nestSprite);

	for (Missile* missile : m_missiles) {
		missile->render(t_window);	// Draw all the missiles
	}
	for (Sweeper* sweeper : m_sweepers) {
		sweeper->render(t_window);	// Draw all the sweepers
	}
}

/// <summary>
/// function that when hit by player bullet it takes damage
/// </summary>
void Nest::takeDamage(/*int& t_playerScore*/)
{
	m_health--;	// Deduct health 
	if (m_health <= 0) {
		// Checks if nest has run out of health
		m_dead = true;	// Set nest to be dead
		//t_playerScore += 20;
	}
}

/// <summary>
/// create missile that shoots from nests
/// </summary>
void Nest::createMissile() 
{
	if (m_missiles.size() < 1) {
		// If missile is currently fired 
		m_missiles.push_back(new Missile(m_position, m_resourceMng));	// Fire missile
	}
}
// Function for spawning a new sweeper bot
void Nest::createSweeper() {
	m_sweeperTimer = 0;	// Reset the timer

						// Spawn a new sweeper
	m_sweepers.push_back(new Sweeper(m_position, State::PATROL, m_resourceMng));
}
/// <summary>
/// getposition of nest
/// </summary>
/// <returns></returns>
sf::Vector2f Nest::getPosition()
{
	return m_position;
}

/// <summary>
/// check if dead
/// </summary>
/// <returns></returns>
bool Nest::getDead()
{
	return m_dead;
}
