#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Tile;

class Grid
{
public:
	Grid();
	~Grid();
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	std::vector<Tile*> m_tiles;
	void setCost();
	void setVector();
	void setDistance();

private:

	sf::Texture m_groundTexture;
	sf::Texture m_obstacleTexture;

	int m_randomSize;
	int m_rectSize;
	int m_gridSize;
	int goalNode;

	void createGrid(int random);
	void clearAll();


	bool m_up = true;
	bool m_down = true;
	bool m_left = true;
	bool m_right = true;
	Tile* m_tile;
};
