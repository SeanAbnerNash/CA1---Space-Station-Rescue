#include "Sweeper.h"
/// <summary>
/// Sweeper Contructor
/// setting up physical attributes of sweeper object
/// </summary>
/// <param name="t_pos"></param>
/// <param name="t_resources"></param>
Sweeper::Sweeper(sf::Vector2f t_pos, State t_state,ResourceManager& t_resources):
	m_position(t_pos),
	m_state(t_state),
	m_resourceMng(t_resources),
	m_rotation(0),
	m_speed(2.5f),
	m_velocity(0, 0)
{
	
	m_sweeperSprite.setTexture(m_resourceMng.getTexture(TextureID::SWEEPER));
	m_sweeperSprite.setOrigin(m_sweeperSprite.getLocalBounds().width / 2, m_sweeperSprite.getLocalBounds().height / 2);
	m_sweeperSprite.setScale(m_spriteDimensions.x / m_sweeperSprite.getGlobalBounds().width, m_spriteDimensions.y / m_sweeperSprite.getGlobalBounds().height);
}
/// <summary>
/// destructor for Sweepers
/// </summary>
Sweeper::~Sweeper()
{
}
/// <summary>
/// update for the sweepers
/// </summary>
/// <param name="t_playerPos"></param>
void Sweeper::update(sf::Time t_deltaTime, sf::Vector2f t_playerPos)
{
	behaviourChange(t_playerPos);
	switch (m_state)
	{
	case SEEK:
		seek(t_playerPos);	// Seeks the target position
		break;
	case EVADE:
		flee(t_playerPos);	// Flees from the player
		break;
	case PATROL:
		wander(t_playerPos);	// Wanders around
		break;
	default:
		break;
	}
	m_position += m_velocity;
	m_sweeperSprite.setPosition(m_position);
	m_sweeperSprite.setRotation(m_rotation);

}
/// <summary>
/// handle rendering of sweepers sprite
/// </summary>
/// <param name="t_window"></param>
void Sweeper::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_sweeperSprite);
}

bool Sweeper::inLineofSight(std::vector<Worker*> t_workers)
{
	for (Worker* w : t_workers) {
		// Loops through workers
		if (Maths::getLength(m_position - w->getPosition()) < 300 && w->getPosition() != m_position) 
		{
			// Cheks if worker is close enough
			sf::Vector2f realVelPos = m_velocity + m_position;

			double Dir_C_to_A = atan2(realVelPos.y - m_position.y, realVelPos.x - m_position.x);
			double Dir_C_to_B = atan2(w->getPosition().y - m_position.y, w->getPosition().x - m_position.x);
			double Angle_ACB = Dir_C_to_A - Dir_C_to_B;
			const double Pi = acos(-1);
			if (Angle_ACB > Pi) Angle_ACB -= 2 * Pi;
			else if (Angle_ACB < -Pi) Angle_ACB += 2 * Pi;

			float angle = Angle_ACB;
			angle = angle * RAD_TO_DEG;

			if (Maths::dist(w->getPosition(), m_position) < 50) {
				// If sweeper has caught worker
				m_state = State::PATROL;	// Worker goes back to patrolling
				m_collected++;	// Increment amount sweeper has caught
				w->m_isCollected = true;	// Set worker to have been collected
				angle = 180;
			}

			if (angle < 45 && angle > -45) {
				// Worker is in line of sight of sweeper
				m_position = w->getPosition();	// Sets target position to workers position
				m_state = State::SEEK;	// Sweeper will now seek worker
				return true;
			}
			else
				return false;
		}
	}
	return false;
}

/// <summary>
/// Function for sweeper wandering
/// </summary>
/// <returns></returns>
void Sweeper::wander(sf::Vector2f t_playerPos)
{
	float tempAdjuster = (((rand() % 20 + 1)));//Gives a number between 1 and 20
	tempAdjuster -= 10; //-10 to give a range of -9 and 10,
	tempAdjuster /= 10;  //divide by 10 to give a range of -0.9 and 1

	m_rotation = m_rotation + (MAX_ROTATION * tempAdjuster); //Randomly changes current angle by the max which is scaled by the random scalar
	m_velocity = sf::Vector2f(cos(m_rotation * M_PI / 180), sin(m_rotation * M_PI / 180));//Generates a unit vector in the given angle.
	m_velocity *= MAX_SPEED;//Scales it by the length of the max speed.
	m_sweeperSprite.setRotation(m_rotation);//Updates Sprite
}
/// <summary>
/// Function handle the sweeper chasing a position
/// </summary>
/// <param name="playerPos"></param>
/// <returns></returns>
void Sweeper::seek(sf::Vector2f t_playerPos)
{
	m_velocity = t_playerPos - m_position;
	m_velocity = Maths::normalize(m_velocity);
	m_velocity *= MAX_SPEED;
	m_rotation = Maths::getNewOrientation(m_rotation, m_velocity);
	m_sweeperSprite.setRotation(m_rotation);
}
/// <summary>
/// Function to handle fleeing from the player
/// </summary>
/// <param name="playerPos"></param>
/// <returns></returns>
void Sweeper::flee(sf::Vector2f t_playerPos)
{
	m_velocity = m_position - t_playerPos;
	m_velocity = Maths::normalize(m_velocity);
	m_velocity *= MAX_SPEED;
	m_rotation = Maths::getNewOrientation(m_rotation, m_velocity);
	m_sweeperSprite.setRotation(m_rotation);
}

/// <summary>
/// Function for updating all movement attributes of the missile
/// </summary>
void Sweeper::startCalc()
{
	if (m_velocity.x != 0 || m_velocity.y != 0)
	{
		float magnitude = Maths::getLength(m_velocity);
		m_velocity = sf::Vector2f(m_velocity.x / magnitude, m_velocity.y / magnitude);
		m_velocity = m_velocity * m_speed;
		m_rotation = Maths::getNewOrientation(m_rotation, m_velocity);
	}

}
/// <summary>
/// Function for checking how close the player is
/// and change behaviour
/// </summary>
/// <param name="playerPos"></param>
void Sweeper::behaviourChange(sf::Vector2f t_playerPos)
{
	if (Maths::dist(t_playerPos, m_position) < 300) 
	{
		// Change position sweeper is moving towards
		float tempAdjuster = (((rand() % 20 + 1)));//Gives a number between 1 and 20
		tempAdjuster -= 10; //-10 to give a range of -9 and 10,
		tempAdjuster /= 10;  //divide by 10 to give a range of -0.9 and 1
		if (m_state == State::PATROL) 
		{
			m_state = State::EVADE;	// Evade the player
		}
	}
	else if (m_state == State::EVADE) {
		// If player is further away 
		m_state = State::PATROL;	// Go back to patrolling
	}
}
/// <summary>
/// return position of sweeper
/// </summary>
/// <returns></returns>
sf::Vector2f Sweeper::getPosition()
{
	return m_position;
}