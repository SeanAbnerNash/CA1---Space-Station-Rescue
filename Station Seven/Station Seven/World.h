#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "Maths.h"
#include "Player.h"
#include "Worker.h"
#include "TileManager.h"
#include "Wall.h"
#include <iostream>
#define M_PI           3.14159265358979323846  /* pi */
#include <Thor/Vectors.hpp>
#include "Nest.h"
#include "Powerup.h"
class World
{
public:
	World(ResourceManager& t_resources, sf::RenderWindow& t_window);
	~World();

	void update( sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);

	//calculations
	void mouseClick(sf::Vector2i t_clickPos, int m_mode);
	sf::Vector2i vecFToVecI(sf::Vector2f t_vec);
	void setUpGrid1(int u, int i);
	void setUpGrid2(int u, int i);
	void setUpGrid3(int u, int i);
	void setUpGrid4(int u, int i);
	void setUpGrid5(int u, int i);
	void setUpGrid6(int u, int i);
	void setUpGrid7(int u, int i);
	void setUpGrid8(int u, int i);
	void setUpGrid9(int u, int i);
	void setUpGrids();

	void playerTrackingPathfinding();
private:
	std::vector<sf::Sprite> m_map;
	ResourceManager& m_resourceMng;
	Player m_player;
	std::vector<Worker*>m_workers;
	std::vector<TileManager*> m_grids;
	sf::RenderWindow& m_window;
	int m_playerGridLocation{ 0 };
	sf::Vector2i m_click{ 600,400 };
	std::vector<Nest*> m_nests;
	std::vector<Powerup*>m_powerups;
	std::vector<Wall*>m_walls;
};

