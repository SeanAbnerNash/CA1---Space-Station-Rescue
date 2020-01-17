#pragma once

///@Author Sean Abner Nash
///@Login C00217019
///Flow Field Pathfinding AI
///Time Taken 16 Hours

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"
class TileManager
{
public:
	TileManager();
	~TileManager();
	TileManager(sf::Vector2f t_startPos);
	TileManager(sf::Font& t_ArialBlackfont);
	void display(sf::RenderWindow& m_renderer);
	void mouseClick(sf::Vector2i t_clickPos, int m_mode);//Mouse click handling
	Tile* getTile(sf::Vector2f t_targetID);//Given a tile ID returns a reference to said tile
	Tile* getTileAt(sf::Vector2i t_targetLocation);//Given a position on the screen, Uses getTile() method to find and returna  a reference
	void flipCosts();//Flips the Respective Bool
	void flipVector();//Flips the Respective Bool
	void flipHeatMap();//Flips the Respective Bool
	void resetOldTile(Tile* t_oldTile, int t_newMode);//Takes care of dangling pointers when overwriting specific tiles.
	void reset();//Resets the grid
	void update();
	void showPath();//Draws the path.
	int getHighestCost();
	int getPathCost();
	bool withinBounds(sf::Vector2i t_point);
	void clearPath();//Clears the Path
	float length(sf::Vector2f t_left, sf::Vector2f t_right);
	void setGoal(sf::Vector2i t_goal);
	void setMode(sf::Vector2f t_id, int t_mode);



private:
	std::vector<Tile*> m_grid;
	sf::Vector2i m_gridSize{ 60,60 };
	sf::Vector2f m_tileSize{ 50,50 };
	sf::Vector2f m_tileGap{ 0,0 };
	sf::Vector2f m_startingPos{ 0,0 };
	Tile* m_start = nullptr;
	Tile* m_end = nullptr;
	bool gridChanged{ true };
	int checkCount{ 0 };
	int m_gridNumber{ 1 };//The number of tiles on the grid. Calculated during creation.
	void setUpVectorGrid();//Does the brushfire algorithm
	void setUpVectorField();//sets up the vector flow fields
	void setUpGrid();//Initially sets up the grid.
	int m_highestCost{ 0 };//Highest cost tile on the grid
	int m_pathCost{ 0 };//Cumulative cost of the path
	bool m_drawVector{ false };
	bool m_drawCost{ false };
	bool m_drawHeatMap{ false };

};

