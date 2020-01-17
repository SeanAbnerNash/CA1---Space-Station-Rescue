#include "Tile.h"

///@Author Sean Abner Nash
///@Login C00217019
///Flow Field Pathfinding AI
///Time Taken 16 Hours


Tile::Tile(int* t_highest)
{
	m_highestCost = t_highest;
	m_shape.setSize(m_size);
	m_shape.setFillColor(m_colour);
	m_shape.setPosition(m_pos);
	setUpLine();
}

Tile::Tile(sf::Font& t_font, int* t_highest)
{
	m_highestCost = t_highest;
	m_shape.setSize(m_size);
	m_shape.setFillColor(m_colour);
	m_shape.setPosition(m_pos);
	m_cost.setFont(t_font);
	setUpText();
	setUpLine();
}

Tile::~Tile()
{
}

void Tile::setUpText()
{

	m_cost.setString(std::to_string(m_value));
	m_cost.setCharacterSize(10);
	m_cost.setFillColor(sf::Color::White);
	m_cost.setOutlineThickness(2.0f);
}

void Tile::setSize(sf::Vector2f t_size)
{
	m_size = t_size;
	m_shape.setSize(m_size);
}

void Tile::setColour(sf::Color t_colour)
{
	m_colour = t_colour;
	m_shape.setFillColor(m_colour);
}

void Tile::setPos(sf::Vector2f t_pos)
{
	m_pos = t_pos;
	m_shape.setPosition(m_pos);
}

void Tile::setID(sf::Vector2f t_id)
{
	m_id = t_id;
}

void Tile::setSteps(int t_steps)
{
	m_stepsToGoal = t_steps;
}

void Tile::reset()
{
	setSteps(-1);
	setLowestNeighbour(0);
	setMode(0);
	m_lowNeighbour = nullptr;
	m_heuristicCost = 0;
}

int Tile::getSteps()
{
	return m_stepsToGoal;
}

int Tile::getMode()
{
	return m_mode;
}

void Tile::setMode(int t_mode)
{
	if (m_mode == t_mode)
	{
		m_mode = 0;
	}
	else {
		m_mode = t_mode;
	}
	switch (m_mode) {//Sets the New colours and cost values
	case 0:
		setColour(sf::Color{ 0,200,0, 125});
		m_terrain = 0;
		break; //optional
	case 1:
		setColour(sf::Color{ 0,0,200 });
		m_terrain = 0;
		break; //optional
	case 2:
		setColour(sf::Color{ 200,0,0 });
		m_terrain = 0;
		break; //optional
	case 3:
		setColour(sf::Color{ 0,0,0 });
		m_terrain = 1000;
		break; //optional
	case 4:
		setColour(sf::Color{ 200,100,0 });
		m_terrain = 0;
		break; //optional
	}

}

void Tile::update()
{

	m_value = m_stepsToGoal + m_terrain;
	//m_cost.setString(std::to_string(m_value));//Updates the Cost String
	//m_cost.setPosition(m_pos.x + m_size.x / 2 - m_cost.getGlobalBounds().width / 2, m_pos.y + m_size.y / 2);

	updateLine();




}

sf::Vector2f Tile::getPos()
{
	return m_pos;
}

sf::Vector2f Tile::getID()
{
	return m_id;
}

sf::Vector2f Tile::getSize()
{
	return m_size;
}

void Tile::display(sf::RenderWindow& m_renderer, bool t_drawCost, bool t_drawVector, bool t_drawHeatMap)
{
	updateHeatMap(t_drawHeatMap);
	m_renderer.draw(m_shape);
	//if (t_drawCost) {
	//	m_renderer.draw(m_cost);
	//}
	if (t_drawVector) {
		m_renderer.draw(m_line, 2, sf::Lines);
	}
}

std::vector<Tile*> Tile::getNeighbours()
{
	return m_neighbours;
}

void Tile::setNeighbours(Tile* t_neighbour)
{
	m_neighbours.push_back(t_neighbour);
}

void Tile::listNeighbours()
{
	for (auto& i : m_neighbours)
	{
		std::cout << "Neighbour X ID : " << i->getID().x << " Neighbour Y ID: " << i->getID().y << std::endl;
	}
}

void Tile::clearNeighbours()
{
	m_neighbours.clear();
	m_lowNeighbour = nullptr;
}

float Tile::getValue()
{
	return m_value;
}

void Tile::findLowestNeighbour()
{

	float tempValue = 100000;
	m_lowestNeighbour = 0;
	for (auto& i : m_neighbours)//Loops through Neigbours.
	{
		sf::Vector2f tempId = i->getID() - m_id;
		if (i->getSteps() != -1 && i->totalValue() < tempValue) {
			tempValue = i->totalValue();
			if (tempId.x == -1)
			{
				if (tempId.y == -1)//-1,-1
				{
					m_lowestNeighbour = 8;
					m_lowNeighbour = i;
				}
				else if (tempId.y == 0)//-1,0
				{
					m_lowestNeighbour = 7;
					m_lowNeighbour = i;
				}
				else if (tempId.y == 1)//-1,1
				{
					m_lowestNeighbour = 6;
					m_lowNeighbour = i;
				}
			}
			else if (tempId.x == 0)
			{
				if (tempId.y == -1)//0,-1
				{
					m_lowestNeighbour = 1;
					m_lowNeighbour = i;
				}
				else if (tempId.y == 0)//0,0
				{
					m_lowestNeighbour = 0;
					m_lowNeighbour = nullptr;
				}
				else if (tempId.y == 1)//0,1
				{
					m_lowestNeighbour = 5;
					m_lowNeighbour = i;
				}
			}
			else if (tempId.x == 1)
			{
				if (tempId.y == -1)//1,-1
				{
					m_lowestNeighbour = 2;
					m_lowNeighbour = i;
				}
				else if (tempId.y == 0)//1,0
				{
					m_lowestNeighbour = 3;
					m_lowNeighbour = i;
				}
				else if (tempId.y == 1)//1,1
				{
					m_lowestNeighbour = 4;
					m_lowNeighbour = i;
				}
			}


		}

	}
	if (m_mode == 3 || m_mode == 1)
	{
		m_lowestNeighbour = 0;
	}
}

void Tile::setLowestNeighbour(int t_low)
{
	m_lowestNeighbour = t_low;
}

Tile* Tile::getLowestNeighbour()
{
	return m_lowNeighbour;
}

void Tile::resetSteps()
{
	m_stepsToGoal = -1;
}

void Tile::setUpLine()
{
	m_line[0].position = sf::Vector2f(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2);
	m_line[0].color = sf::Color::Magenta;
	m_line[1].position = sf::Vector2f(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2 + m_size.y / 8);
	m_line[1].color = sf::Color::White;
}

void Tile::updateLine()
{
	switch (m_lowestNeighbour)
	{
	case 0:

		m_line[0].position = sf::Vector2f(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2);
		m_line[1].position = sf::Vector2f(m_pos.x + m_size.x / 2, m_pos.y + 1 + m_size.y / 2);
		m_directionVector = sf::Vector2f{ 0,0 };
		break;
	case 1:
		m_line[0].position = sf::Vector2f(m_pos.x + m_size.x / 2, (m_pos.y + m_size.y / 2) - m_size.y / 3);
		m_line[1].position = sf::Vector2f(m_pos.x + m_size.x / 2, (m_pos.y + m_size.y / 2) + m_size.y / 3);
		m_directionVector = sf::Vector2f{ 0,-1 };
		break;
	case 2:
		m_line[0].position = sf::Vector2f((m_pos.x + m_size.x / 2) + m_size.x / 3, (m_pos.y + m_size.y / 2) - m_size.y / 3);
		m_line[1].position = sf::Vector2f((m_pos.x + m_size.x / 2) - m_size.x / 3, (m_pos.y + m_size.y / 2) + m_size.y / 3);
		m_directionVector = sf::Vector2f{ 1,-1 };
		break;
	case 3:
		m_line[0].position = sf::Vector2f((m_pos.x + m_size.x / 2) + m_size.x / 3, (m_pos.y + m_size.y / 2));
		m_line[1].position = sf::Vector2f((m_pos.x + m_size.x / 2) - m_size.x / 3, (m_pos.y + m_size.y / 2));
		m_directionVector = sf::Vector2f{ 1,0 };
		break;
	case 4:
		m_line[0].position = sf::Vector2f((m_pos.x + m_size.x / 2) + m_size.x / 3, (m_pos.y + m_size.y / 2) + m_size.y / 3);
		m_line[1].position = sf::Vector2f((m_pos.x + m_size.x / 2) - m_size.x / 3, (m_pos.y + m_size.y / 2) - m_size.y / 3);
		m_directionVector = sf::Vector2f{ 1,1 };
		break;
	case 5:
		m_line[0].position = sf::Vector2f((m_pos.x + m_size.x / 2), (m_pos.y + m_size.y / 2) + m_size.y / 3);
		m_line[1].position = sf::Vector2f((m_pos.x + m_size.x / 2), (m_pos.y + m_size.y / 2) - m_size.y / 3);
		m_directionVector = sf::Vector2f{ 0,1 };
		break;
	case 6:
		m_line[0].position = sf::Vector2f((m_pos.x + m_size.x / 2) - m_size.x / 3, (m_pos.y + m_size.y / 2) + m_size.y / 3);
		m_line[1].position = sf::Vector2f((m_pos.x + m_size.x / 2) + m_size.x / 3, (m_pos.y + m_size.y / 2) - m_size.y / 3);
		m_directionVector = sf::Vector2f{ -1,1 };
		break;
	case 7:
		m_line[0].position = sf::Vector2f((m_pos.x + m_size.x / 2) - m_size.x / 3, (m_pos.y + m_size.y / 2));
		m_line[1].position = sf::Vector2f((m_pos.x + m_size.x / 2) + m_size.x / 3, (m_pos.y + m_size.y / 2));
		m_directionVector = sf::Vector2f{ -1,0 };
		break;
	case 8:
		m_line[0].position = sf::Vector2f((m_pos.x + m_size.x / 2) - m_size.x / 3, (m_pos.y + m_size.y / 2) - m_size.y / 3);
		m_line[1].position = sf::Vector2f((m_pos.x + m_size.x / 2) + m_size.x / 3, (m_pos.y + m_size.y / 2) + m_size.y / 3);
		m_directionVector = sf::Vector2f{ -1,-1 };
		break;

	}
}

void Tile::updateHeatMap(bool t_heatMap)
{
	if (t_heatMap) {
		if (m_mode == 0 && m_stepsToGoal != -1)
		{
			m_colour.g = 255 - (255 * m_value / (*m_highestCost * 1.3f));
			m_shape.setFillColor(m_colour);
		}
		else if (m_mode == 0 && m_stepsToGoal == -1) {
			m_colour.g = 100;
			m_shape.setFillColor(m_colour);
		}
	}
	if (!t_heatMap) {
		if (m_mode == 0)
		{
			m_colour.g = 200;
			m_shape.setFillColor(m_colour);
		}
	}


}

void Tile::clearPath()
{
}

sf::Vector2f Tile::getVectorSpeed()
{
	return m_directionVector;
}

void Tile::setHeuristic(float t_heuristic)
{
	m_heuristicCost = t_heuristic;
}

float Tile::getHeuristic()
{
	return m_heuristicCost;
}

float Tile::totalValue()
{
	return (m_stepsToGoal * 100) + m_heuristicCost;
}
