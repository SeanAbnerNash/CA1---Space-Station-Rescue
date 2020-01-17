#include "World.h"

/// <summary>
/// World constructor
/// here we set up the map and entities
/// </summary>
/// <param name="t_resources"></param>
/// <param name="t_window"></param>
World::World(ResourceManager& t_resources, sf::RenderWindow& t_window):
	m_resourceMng(t_resources),
	m_player(m_resourceMng),
	m_window{t_window}
{
	//m_workerSprite.setTexture(m_resourceMng.getTexture(TextureID::WORKER));
	m_map.push_back(sf::Sprite(m_resourceMng.getTexture(TextureID::MAPGRID11)));
	m_map.push_back(sf::Sprite(m_resourceMng.getTexture(TextureID::MAPGRID21)));
	m_map.push_back(sf::Sprite(m_resourceMng.getTexture(TextureID::MAPGRID31)));

	m_map.push_back(sf::Sprite(m_resourceMng.getTexture(TextureID::MAPGRID12)));
	m_map.push_back(sf::Sprite(m_resourceMng.getTexture(TextureID::MAPGRID22)));
	m_map.push_back(sf::Sprite(m_resourceMng.getTexture(TextureID::MAPGRID32)));


	m_map.push_back(sf::Sprite(m_resourceMng.getTexture(TextureID::MAPGRID13)));
	m_map.push_back(sf::Sprite(m_resourceMng.getTexture(TextureID::MAPGRID23)));
	m_map.push_back(sf::Sprite(m_resourceMng.getTexture(TextureID::MAPGRID33)));


	//m_map[0].setPosition(sf::Vector2f( 0, m_map[0].getPosition().y)); //The Initial Tile is set to position 0,0
	m_map[1].setPosition(sf::Vector2f(m_map[0].getPosition().x + m_map[0].getGlobalBounds().width, m_map[0].getPosition().y));
	m_map[2].setPosition(sf::Vector2f(m_map[1].getPosition().x + m_map[1].getGlobalBounds().width, m_map[1].getPosition().y)); //Row 1


	m_map[3].setPosition(sf::Vector2f(0, m_map[0].getPosition().y + m_map[0].getGlobalBounds().height));//Row 2
	m_map[4].setPosition(sf::Vector2f(m_map[3].getPosition().x + m_map[3].getGlobalBounds().width, m_map[3].getPosition().y));
	m_map[5].setPosition(sf::Vector2f(m_map[4].getPosition().x + m_map[4].getGlobalBounds().width, m_map[3].getPosition().y));

	m_map[6].setPosition(sf::Vector2f(0, m_map[3].getPosition().y + m_map[3].getGlobalBounds().height));//Row 2
	m_map[7].setPosition(sf::Vector2f(m_map[6].getPosition().x + m_map[6].getGlobalBounds().width, m_map[6].getPosition().y));
	m_map[8].setPosition(sf::Vector2f(m_map[7].getPosition().x + m_map[7].getGlobalBounds().width, m_map[6].getPosition().y));

	m_grids.push_back(new TileManager());
	m_grids.push_back(new TileManager(sf::Vector2f(m_map[1].getPosition().x -12, m_map[1].getPosition().y+1)));
	m_grids.push_back(new TileManager(sf::Vector2f(m_map[2].getPosition().x - 32, m_map[2].getPosition().y + 1)));
	
	m_grids.push_back(new TileManager(sf::Vector2f(m_map[3].getPosition().x, m_map[3].getPosition().y-12)));
	m_grids.push_back(new TileManager(sf::Vector2f(m_map[4].getPosition().x-12, m_map[4].getPosition().y - 12)));
	m_grids.push_back(new TileManager(sf::Vector2f(m_map[5].getPosition().x -32, m_map[5].getPosition().y - 12)));

	m_grids.push_back(new TileManager(sf::Vector2f(m_map[6].getPosition().x, m_map[6].getPosition().y-32)));
	m_grids.push_back(new TileManager(sf::Vector2f(m_map[7].getPosition().x -12, m_map[7].getPosition().y - 32)));
	m_grids.push_back(new TileManager(sf::Vector2f(m_map[8].getPosition().x -32, m_map[8].getPosition().y - 32)));

	m_powerups.push_back(new Powerup(sf::Vector2f(1000, 200), POWERUPTYPE::SHIELD, m_resourceMng));
	m_powerups.push_back(new Powerup(sf::Vector2f(1000, 2000), POWERUPTYPE::SHIELD, m_resourceMng));
	m_powerups.push_back(new Powerup(sf::Vector2f(1000, 2500), POWERUPTYPE::SHOT360, m_resourceMng));
	m_powerups.push_back(new Powerup(sf::Vector2f(1250, 2000), POWERUPTYPE::SHOT360, m_resourceMng));

	for (int i = 0; i < 10; i++)

	{
		m_workers.push_back(new Worker(WORKERSTATE::WANDER, sf::Vector2f(1200, 500), m_resourceMng));
	}


		m_nests.clear();
		m_nests.push_back(new Nest(sf::Vector2f(1000, 1000), m_resourceMng));
		m_nests.push_back(new Nest(sf::Vector2f(1000, 4000), m_resourceMng));
		m_nests.push_back(new Nest(sf::Vector2f(3000, 1000), m_resourceMng));
		m_nests.push_back(new Nest(sf::Vector2f(4000, 2000), m_resourceMng));
	

	if (!m_font.loadFromFile("ASSETS\\FONTS\\arial.ttf"))	// Checks to make sure font is correct
	{
		std::cout << "Problem loading font file!" << std::endl;
	}
	m_healthText.setFont(m_font);
	m_healthText.setFillColor(sf::Color::Black);
	m_healthText.setOrigin(m_healthText.getLocalBounds().width / 2, m_healthText.getLocalBounds().height / 2);

	m_workersText.setFont(m_font);
	m_workersText.setFillColor(sf::Color::Black);
	m_workersText.setOrigin(m_workersText.getLocalBounds().width / 2, m_workersText.getLocalBounds().height / 2);
	updateUI();
}
/// <summary>
/// world destructor
/// </summary>
World::~World()
{
}
/// <summary>
/// here we do updates of player the world
/// pathfinding , powerups
/// collision detection
/// </summary>
/// <param name="t_deltaTime"></param>
void World::update( sf::Time t_deltaTime)
{

	m_player.update(t_deltaTime);

	for (int i = 0; i < 9; i++)
	{
		if (m_grids[i]->withinBounds(vecFToVecI(m_player.getPos())))
		{
			m_playerGridLocation = i;
		}
	}
	m_grids[m_playerGridLocation]->update();
	playerTrackingPathfinding();

	for (int i = 0; i < m_nests.size(); ++i)
	{
		m_nests.at(i)->update(t_deltaTime, m_player.getPos(),m_workers,m_player.m_health, m_particles);
		m_player.checkNest(*m_nests.at(i),m_particles);
		m_player.checkSweepers(m_nests.at(i)->m_sweepers,m_particles);
		if (m_nests.at(i)->getDead())
		{
			for (Sweeper* sweeper : m_nests.at(i)->m_sweepers)
			{
				m_sweepers.push_back(sweeper);
			}
			m_nests.erase(m_nests.begin() + i);
		}
	}
	m_player.checkSweepers(m_sweepers, m_particles);
	for (Sweeper* sweeper : m_sweepers)
	{
		sweeper->update(t_deltaTime, m_player.getPos());
		sweeper->inLineofSight(m_workers);
	}
	for (Powerup* powerup : m_powerups)
	{
		powerup->update();
		if (powerup->collisionDetection(m_player.getPos()))
		{
			powerup->setAlive(false);
			if (powerup->getPowerupType() ==POWERUPTYPE::SHIELD)
			{
				m_player.activateShield();
			}
			else
			{
				m_player.activate360Shot();
			}

		}
	}

	for (int i=0;i<m_workers.size();++i)
	{
		m_workers.at(i)->update(m_player.getPos(),m_player.getVel());
		if (m_workers.at(i)->m_isCollected)
		{
			m_workers.erase(m_workers.begin() + i);
		}
	

	}
	m_player.playerWorkerCollision(&m_workers);

	for (int i = 0; i < m_particles.size(); i++) {
		// Loops through particle systems
		m_particles.at(i)->update();

		//Checks if the particle system is empty
		if (m_particles.at(i)->m_particles.size() <= 0) {
			// Deletes the particle system
			m_particles.erase(m_particles.begin() + i);
		}
	}
}

/// <summary>
/// here we render the world 
/// entities player powerups
/// </summary>
/// <param name="t_window"></param>
void World::render(sf::RenderWindow& t_window)
{
	m_window.setView(m_player.getView());
	for (auto i : m_map)
	{
		t_window.draw(i);
	}
	m_grids[m_playerGridLocation]->display(t_window);
	m_player.render(t_window);
	m_window.draw(m_healthText);
	m_window.draw(m_workersText);
	for (Nest* nest : m_nests) {
		nest->render(m_window);	// Draw nest
	}
	for (Powerup* powerup : m_powerups)
	{
		powerup->render(m_window);
	}
	for (Worker* workers : m_workers)
	{
		workers->render(m_window);
	}
	for (Sweeper* sweeper : m_sweepers) 
	{
		sweeper->render(m_window);	
	}
	for (ParticleSystem* ps : m_particles) {
		ps->draw(m_window); // Draw particle system
	}
}

void World::mouseClick(sf::Vector2i t_clickPos, int m_mode)
{
	sf::Vector2i temp;
	temp.x = m_window.mapPixelToCoords(t_clickPos).x;
	temp.y = m_window.mapPixelToCoords(t_clickPos).y;
	std::cout << t_clickPos.x << "    " << t_clickPos.y << std::endl;
	m_grids[m_playerGridLocation]->mouseClick(temp, m_mode);
	
}

sf::Vector2i World::vecFToVecI(sf::Vector2f t_vec)
{
	return sf::Vector2i(t_vec.x,t_vec.y);
}

/// <summary>
/// track the player pathfinding
/// </summary>
void World::playerTrackingPathfinding()
{
	sf::Vector2i temp;
	temp.x = m_window.mapPixelToCoords(m_click).x;
	temp.y = m_window.mapPixelToCoords(m_click).y;
	m_grids[m_playerGridLocation]->setGoal(temp);
}

void World::updateUI()
{

	m_healthText.setString("Health" + std::to_string(m_player.m_health));
	m_healthText.setPosition(
		m_player.getSprite().getPosition().x - 500,
		m_player.getSprite().getPosition().y - 370
	);
	m_workersText.setString("Workers" +std::to_string(m_player.m_workerCollected));
	m_workersText.setPosition(
		m_player.getSprite().getPosition().x + 500,
		m_player.getSprite().getPosition().y - 370
	);
}
