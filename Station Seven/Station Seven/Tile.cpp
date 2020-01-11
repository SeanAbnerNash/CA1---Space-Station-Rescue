#include "Tile.h"
#include <iostream>
#include <math.h>

/// <summary>
/// Creates a Tile and assignes the cost if it is an obstacle.
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="size"></param>
/// <param name="obstacle"></param>
Tile::Tile(int t_x, int t_y, int t_size, int t_obstacle):
	m_rectSize(t_size),
	m_setCost(false)
{

	m_rect.setSize(sf::Vector2f(t_size, t_size));
	m_rect.setPosition(t_x, t_y);
	if (t_obstacle == 1)
	{
		setCost(999999);
	}
}

/// <summary>
/// Deconstructor for Tile.
/// </summary>
Tile::~Tile()
{
}

/// <summary>
/// Set the cost of a Tile for flow field pathfinding.
/// Set the costSet so it is not used again.
/// </summary>
/// <param name="x"></param>
void Tile::setCost(double t_cost)
{
	m_cost = t_cost;
	m_setCost = true;
}

/// <summary>
/// Return the cost of the Tile
/// </summary>
/// <returns></returns>
double Tile::getCost()
{
	return m_cost;
}

/// <summary>
/// Check if the Tile has already been used
/// </summary>
/// <returns></returns>
bool Tile::isCostSet()
{
	return m_setCost;
}

int Tile::getRectSize()
{
	return m_rectSize;
}

/// <summary>
/// Set the Tile has been used or not used.
/// Is used for reseting Tiles.
/// </summary>
/// <param name="num"></param>
void Tile::costSet(int num)
{
	if (num == 0)
	{
		m_setCost = false;
	}
	if (num == 1)
	{
		m_setCost = true;
	}
}

/// <summary>
/// Distance no longer used for efficiency
/// </summary>
/// <param name="goalX"></param>
/// <param name="goalY"></param>
void Tile::setDistance(int goalX, int goalY)
{
	m_integrationField = m_cost;
}

/// <summary>
/// Get the integration field of a Tile.
/// </summary>
/// <returns></returns>
double Tile::getIntegrationField()
{
	return m_integrationField;
}

/// <summary>
/// Set the integration field of a Tile.
/// </summary>
/// <param name="field"></param>
void Tile::setIntegrationField(double field)
{
	m_integrationField = field;
}

/// <summary>
/// Set the vector used by ais for pathfinding.
/// </summary>
/// <param name="vectorX"></param>
/// <param name="vectorY"></param>
void Tile::setVector(double vectorX, double vectorY)
{
	m_vectX = vectorX;
	m_vectY = vectorY;
}

/// <summary>
/// Get the X vector used for pathfinding.
/// </summary>
/// <returns></returns>
double Tile::getVectX()
{
	return m_vectX;
}

/// <summary>
/// Get the Y vector used for pathfinding.
/// </summary>
/// <returns></returns>
double Tile::getVectY()
{
	return m_vectY;
}


/// <summary>
/// Gets the position of Tile used for vector calculation
/// </summary>
/// <returns></returns>
int Tile::getPositionX()
{
	return m_rect.getPosition().x;
}

/// <summary>
/// Gets the position of Tile used for vector calculation
/// </summary>
/// <returns></returns>
int Tile::getPositionY()
{
	return m_rect.getPosition().y;
}
void Tile::draw(sf::RenderWindow& window)
{
}