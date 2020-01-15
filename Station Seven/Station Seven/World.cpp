#include "World.h"

World::World(ResourceManager& t_resources):
	m_resourceMng(t_resources)
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


}

World::~World()
{
}

void World::render(sf::RenderWindow& t_window)
{
	for (auto i : m_map)
	{
		t_window.draw(i);
	}
}
