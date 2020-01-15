#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
///@Author Sean Abner Nash
///@Login C00217019
///Flow Field Pathfinding AI
///Time Taken 16 Hours

class Tile
{
public:
	Tile(int* t_highest);
	Tile(sf::Font& t_font, int* t_highest);
	~Tile();
	void setUpText();
	void setSize(sf::Vector2f t_size);
	void setColour(sf::Color t_colour);
	void setPos(sf::Vector2f t_pos);
	void setID(sf::Vector2f t_id);
	void setSteps(int t_steps);
	void reset();//Called by the Tile Manager to reset the Grid to the blank state
	int getSteps();
	int getMode();
	void setMode(int t_mode);
	void update();
	sf::Vector2f getPos();
	sf::Vector2f getID();
	sf::Vector2f getSize();
	void display(sf::RenderWindow& m_renderer, bool t_drawCost, bool t_drawVector, bool t_drawHeatMap);//The bools track which options are drawn
	std::vector<Tile*> getNeighbours();//Returns the Vector of Neighbours the Tile has.
	void setNeighbours(Tile* t_neighbour);//Sets the passed Reference as a part of the Neigbour Vector.
	void listNeighbours(); //Outputs the Neighbours to the console.
	void clearNeighbours();//Empties Neigbour Vector
	float getValue(); //Returns the Value of the Number of Steps to the goal and the terrain Modifiers.
	void findLowestNeighbour();//Sets the lowest Neigbour as such.
	void setLowestNeighbour(int t_low); //Sets the lowest neigbour
	Tile* getLowestNeighbour();//Returns a reference to the lowest neibour 
	void resetSteps();
	void setUpLine();
	void updateLine();
	void updateHeatMap(bool t_heatMap);
	void clearPath();//Clears the drawn path from the grid.
	sf::Vector2f getVectorSpeed();
	void setHeuristic(float t_heuristic);
	float getHeuristic();
	float totalValue();//The Heuristic + Total Steps scaled up.



private:
	std::vector<Tile*> m_neighbours;
	sf::Color m_colour{ 0,255,0, 125 };
	sf::RectangleShape m_shape;
	sf::Vector2f m_size{ 10,10 };
	sf::Vector2f m_pos{ 50,50 };
	sf::Vector2f m_id{ 0,0 };
	sf::Vector2f m_directionVector{ 0,0 };//The Vector of the Tile. Points towards the lowest Neigbour. Used by particles to move.
	sf::Vertex m_line[2];
	float m_heuristicCost{ 0 };
	int m_lowestNeighbour{ 0 }; //The direction to the lowest. Neighbour. With 0 Being no where. 1 Being 12 oclock and going clockwise to 8.
	Tile* m_lowNeighbour{ nullptr };//A reference to the lowest neigbour. Used to show the path to the goal.
	float m_terrain{ 0.0 };//Cost to get to the goal.
	int m_stepsToGoal{ -1 };//-1 is the unvisited 
	int m_value{ 0 }; //The Cost+ the number of steps to the goal.
	int m_mode{ 0 }; // 0 Is base. 1 Is Start, 2 is Endgoal, 3 is obstacle.
	sf::Text m_cost; // text used for message on screen
	int* m_highestCost;//A pointer to the highest cost tile value. Used to scale the heatmap colours.
};

