#include "World.h"

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

	m_nests.push_back(new Nest(sf::Vector2f(1000, 1000), m_resourceMng));
	m_nests.push_back(new Nest(sf::Vector2f(2000, 2000), m_resourceMng));
}

World::~World()
{
}

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
		m_nests.at(i)->update(t_deltaTime, m_player.getPos());
		m_player.checkNest(*m_nests.at(i));
		if (m_nests.at(i)->getDead())
		{
			m_nests.erase(m_nests.begin() + i);
		}
	}

}

void World::render(sf::RenderWindow& t_window)
{
	for (auto i : m_map)
	{
		t_window.draw(i);
	}
	m_grids[m_playerGridLocation]->display(t_window);
	m_player.render(t_window);

	for (Nest* nest : m_nests) {
		nest->render(m_window);	// Draw nest
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

void World::playerTrackingPathfinding()
{
	sf::Vector2i temp;
	temp.x = m_window.mapPixelToCoords(m_click).x;
	temp.y = m_window.mapPixelToCoords(m_click).y;
	m_grids[m_playerGridLocation]->setGoal(temp);
}
