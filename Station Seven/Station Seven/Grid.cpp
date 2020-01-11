#include "Grid.h"
#include <iostream>
#include <fstream>
#include <math.h>


/// <summary>
/// Grid constructor.
/// Call create.
/// </summary>
Grid::Grid():
	m_randomSize(1),
	m_rectSize(200),
	m_gridSize(50)
{
	createGrid(m_randomSize);
}

/// <summary>
/// Initialises a new grid with hard coded values
/// </summary>
/// <param name="random"></param>
void Grid::createGrid(int random)
{
	srand(time(NULL));

	//TODO:
	//Create a texture that will match this 50 by 50 array for our map
	//this is for our flow field algorithm 
	//do something like 1 = Wall/Obstacle 0 = none so player can fly through W=worker P=predator,N=nest and then some powerups.
	//TODO LIKE VERY SOON.
	// values for grid world. 1 = obstacle
	int map[50][50] =
	{ { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	// For loop to create a nide at each grid spot and pass if it is an obstacle
	for (int x = 1; x <= m_gridSize; x++)
	{
		for (int y = 1; y <= m_gridSize; y++)
		{

			m_tile = new Tile(-5200 + x * (m_rectSize), -5200 + y * (m_rectSize), m_rectSize, map[x - 1][y - 1]);
			m_tiles.push_back(m_tile);
		}
	}
}

/// <summary>
/// deconstructor for grid
/// </summary>
Grid::~Grid()
{
}


/// <summary>
/// Grid Update function
/// </summary>
/// <param name="window"></param>
void Grid::update(sf::RenderWindow& window)
{
}

/// <summary>
/// Resets all paramaters of m_tiles so they can be used for new path
/// </summary>
void Grid::clearAll()
{
	for (int i = 0; i < m_tiles.size(); i++)
	{
		if (m_tiles[i]->getCost() < 999)  // does not reset obstacles
		{
			m_tiles[i]->setCost(0);
			m_tiles[i]->costSet(0);
		}
		m_tiles[i]->setVector(0, 0);
		m_tiles[i]->setIntegrationField(0);
	}
}

/// <summary>
/// Set the cost of each obstacle for the flow field pathfinding
/// </summary>
void Grid::setCost()
{
	std::vector<int> que;  // Que of node index to perform cost calculation on.
	que.push_back(goalNode);  // Start with goal.
	m_tiles[goalNode]->setCost(0);  // Goal cost will always be 0.
	int indexHorizontal = m_gridSize;
	int indexVertical = 1;
	while (que.empty() == false)
	{
		// Calculate what directions are available.
		m_up = true;
		m_down = true;
		m_left = true;
		m_right = true;

		if (que.front() < m_gridSize)  // Furthest left possible.
		{
			m_left = false;
		}
		if (que.front() > ((m_gridSize * m_gridSize) - (m_gridSize + 1))) // Greater than max right value (2249).
		{
			m_right = false;
		}
		if (que.front() % m_gridSize == 0)  // Checks if is on top row of m_tiles.
		{
			m_up = false;
		}
		for (int x = 0; x < m_gridSize; x++)
		{
			if (que.front() == ((m_gridSize - 1) + (m_gridSize * x)))  // Checks if is on bottom row of m_tiles.
			{
				m_down = false;
			}
		}
		if (m_up == true)
		{
			if (m_tiles[que.front() - indexVertical]->isCostSet() == false)
			{
				m_tiles[(que.front() - indexVertical)]->setCost(m_tiles[que.front()]->getCost() + 1);   // Set cost to previous + 1.
				que.push_back(que.front() - indexVertical);  // Push onto que so cost is performed on this node.
			}
		}
		if (m_down == true)
		{
			if (m_tiles[que.front() + indexVertical]->isCostSet() == false)
			{
				m_tiles[(que.front() + indexVertical)]->setCost(m_tiles[que.front()]->getCost() + 1);
				que.push_back(que.front() + indexVertical);
			}
		}
		if (m_left == true)
		{
			if (m_tiles[que.front() - indexHorizontal]->isCostSet() == false)
			{
				m_tiles[(que.front() - indexHorizontal)]->setCost(m_tiles[que.front()]->getCost() + 1);
				que.push_back(que.front() - indexHorizontal);
			}
		}
		if (m_right == true)
		{
			if (m_tiles[que.front() + indexHorizontal]->isCostSet() == false)
			{
				m_tiles[(que.front() + indexHorizontal)]->setCost(m_tiles[que.front()]->getCost() + 1);
				que.push_back(que.front() + indexHorizontal);
			}
		}
		que.erase(que.begin());  // Get rid of node index just used.
	}
}

/// <summary>
/// set the vector of each tile
/// future work for AI Movement
/// </summary>
void Grid::setVector()
{
	for (int i = 0; i < m_tiles.size(); i++)
	{

		m_up = true;
		m_down = true;
		m_left = true;
		m_right = true;
		int indexHorizontal = m_gridSize;
		int indexVertical = 1;
		double leftField = 0;
		double rightField = 0;
		double upField = 0;
		double downField = 0;
		double vectorX = 0;
		double vectorY = 0;
		int offset = 19;  // Offset to force ai away from walls.
		if (m_tiles[i]->getIntegrationField() < 9000)
		{
			// Calculate what directions are available.
			if (i < m_gridSize)
			{
				m_left = false;
			}
			if (i > ((m_gridSize * m_gridSize) - (m_gridSize + 1)))
			{
				m_right = false;
			}
			if (i % m_gridSize == 0)
			{
				m_up = false;
			}
			for (int iter = 0; iter < m_gridSize; iter++)
			{
				if (i == ((m_gridSize - 1) + (m_gridSize * iter)))
				{
					m_down = false;
				}
			}
			// Get the integration field of all available m_tiles and use to calculate vector
			if (m_up == true)
			{
				if (m_tiles[i - indexVertical]->getIntegrationField() < 9000)
				{
					upField = m_tiles[i - indexVertical]->getIntegrationField();
				}
				else
				{
					upField = m_tiles[i]->getIntegrationField() + m_tiles[i]->getIntegrationField() / offset;  // Use own value + offset if node is an obstacle;
				}
			}
			else
			{
				upField = m_tiles[i]->getIntegrationField() + m_tiles[i]->getIntegrationField() / offset;  // Use own value if node is unavailable;
			}
			if (m_down == true)
			{

				if (m_tiles[i + indexVertical]->getIntegrationField() < 9000)
				{
					downField = m_tiles[i + indexVertical]->getIntegrationField();
				}
				else
				{
					downField = m_tiles[i]->getIntegrationField() + m_tiles[i]->getIntegrationField() / offset;
				}
			}
			else
			{
				downField = m_tiles[i]->getIntegrationField() + m_tiles[i]->getIntegrationField() / offset;
			}
			if (m_left == true)
			{
				if (m_tiles[i - indexHorizontal]->getIntegrationField() < 9000)
				{
					leftField = m_tiles[i - indexHorizontal]->getIntegrationField();
				}
				else
				{
					leftField = m_tiles[i]->getIntegrationField() + m_tiles[i]->getIntegrationField() / offset;
				}
			}
			else
			{
				leftField = m_tiles[i]->getIntegrationField() + m_tiles[i]->getIntegrationField() / offset;
			}
			if (m_right == true)
			{
				if (m_tiles[i + indexHorizontal]->getIntegrationField() < 9000)
				{
					rightField = m_tiles[i + indexHorizontal]->getIntegrationField();
				}
				else
				{
					rightField = m_tiles[i]->getIntegrationField() + m_tiles[i]->getIntegrationField() / offset;
				}
			}
			else
			{
				rightField = m_tiles[i]->getIntegrationField() + m_tiles[i]->getIntegrationField() / offset;
			}
			// Combine surrounding cost values to create a vector.
			vectorX = leftField - rightField;
			vectorY = upField - downField;
			// Turn into a unit vector
			double tempX = ((((m_tiles[i]->getPositionX() + (m_rectSize / 2)) + vectorX) - (m_tiles[i]->getPositionX() + (m_rectSize / 2))) * (((m_tiles[i]->getPositionX() + (m_rectSize / 2)) + vectorX) - (m_tiles[i]->getPositionX() + (m_rectSize / 2))));
			double tempY = ((((m_tiles[i]->getPositionY() + (m_rectSize / 2)) + vectorY) - (m_tiles[i]->getPositionY() + (m_rectSize / 2))) * (((m_tiles[i]->getPositionY() + (m_rectSize / 2)) + vectorY) - (m_tiles[i]->getPositionY() + (m_rectSize / 2))));
			double vectMag = sqrt(tempX + tempY);
			vectorX = vectorX / vectMag;
			vectorY = vectorY / vectMag;
			m_tiles[i]->setVector(vectorX, vectorY);  // Assign the unit vector to the node.
		}


	}
}

/// <summary>
/// Calls the set distance of each node for pathfinding.
/// </summary>
void Grid::setDistance()
{
	for (int i = 0; i < m_tiles.size(); i++)
	{
		m_tiles[i]->setDistance((m_tiles[goalNode]->getPositionX() + (m_rectSize / 2)), (m_tiles[goalNode]->getPositionY() + (m_rectSize / 2)));
	}
}
void Grid::draw(sf::RenderWindow& window)
{
	//m_player->draw(m_window);
	for (int i = 0; i < m_tiles.size(); i++)
	{
		m_tiles[i]->draw(window);
	}
}