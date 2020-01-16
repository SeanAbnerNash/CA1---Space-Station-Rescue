#include "TileManager.h"
#include <deque>

///@Author Sean Abner Nash
///@Login C00217019
///Flow Field Pathfinding AI
///Time Taken 16 Hours

TileManager::TileManager()
{
	m_gridNumber = (m_gridSize.x + 1) * (m_gridSize.y + 1);
	for (int i = 0; i < m_gridNumber; i++) {
		m_grid.push_back(new Tile(&m_highestCost));
	}
	setUpGrid();
}

TileManager::~TileManager()
{
}

TileManager::TileManager(sf::Vector2f t_startPos) :
	m_startingPos{t_startPos}
{
	m_gridNumber = (m_gridSize.x + 1) * (m_gridSize.y + 1);
	for (int i = 0; i < m_gridNumber; i++) {
		m_grid.push_back(new Tile(&m_highestCost));
	}
	setUpGrid();
}

TileManager::TileManager(sf::Font& t_ArialBlackfont) {
	m_gridNumber = (m_gridSize.x + 1) * (m_gridSize.y + 1);
	for (int i = 0; i < m_gridNumber; i++) {
		m_grid.push_back(new Tile(t_ArialBlackfont, &m_highestCost));
	}
	setUpGrid();
}

void TileManager::display(sf::RenderWindow& m_renderer) {
	for (auto& i : m_grid) {
		i->display(m_renderer, m_drawCost, m_drawVector, m_drawHeatMap);
	}
}

void TileManager::mouseClick(sf::Vector2i t_clickPos, int m_mode) {

	if (withinBounds(t_clickPos))
	{
		sf::Vector2i temp;
		temp.x = t_clickPos.x - m_startingPos.x;
		temp.y = t_clickPos.y - m_startingPos.y;

		Tile* i = getTileAt(temp);
		gridChanged = true;
		switch (m_mode) {
		case 1:
			resetOldTile(i, m_mode);
			if (m_start != nullptr)
			{
				m_start->setMode(m_mode);
			}
			m_start = i;
			setUpVectorGrid();
			i->setMode(m_mode);
			break;
		case 2:
			resetOldTile(i, m_mode);
			if (m_end != nullptr)
			{
				m_end->setMode(m_mode);
			}
			m_end = i;
			i->setMode(m_mode);
			break; //optional
		case 3:
			resetOldTile(i, m_mode);
			i->setMode(m_mode);
			setUpVectorGrid();
			break; //optional
		}

	}


}

Tile* TileManager::getTile(sf::Vector2f t_targetID)
{
	int index = (t_targetID.x) + (t_targetID.y * m_gridSize.y);

	if (t_targetID.y != 0)
	{
		index = index + (1 * t_targetID.y);
	}
	Tile* found = m_grid[index];
	return found;
}

Tile* TileManager::getTileAt(sf::Vector2i t_targetLocation)
{
	int col = t_targetLocation.x / (m_tileSize.x + m_tileGap.x);
	int row = t_targetLocation.y / (m_tileSize.y + m_tileGap.y);
	if (col > m_gridSize.x)
	{
		col = m_gridSize.x;
	}
	if (col < 0)
	{
		col = 0;
	}
	if (row > m_gridSize.y)
	{
		row = m_gridSize.y;
	}
	if (col < 0)
	{
		row = 0;
	}
	return getTile(sf::Vector2f(col, row));
}

void TileManager::flipCosts()
{
	m_drawCost = !m_drawCost;
}

void TileManager::flipVector()
{
	m_drawVector = !m_drawVector;
}

void TileManager::flipHeatMap()
{
	m_drawHeatMap = !m_drawHeatMap;
}

void TileManager::resetOldTile(Tile* t_oldTile, int t_newMode)
{
	if (t_newMode == 1)
	{
		switch (t_oldTile->getMode()) {

		case 2:
			clearPath();
			m_end->setMode(2);
			m_end = nullptr;
			break;

		}
	}
	if (t_newMode == 2)
	{
		switch (t_oldTile->getMode()) {

		case 1:
			clearPath();
			m_start->setMode(1);
			m_start = nullptr;
			break;

		}
	}
	if (t_newMode == 3)
	{
		switch (t_oldTile->getMode()) {

		case 1:
			clearPath();
			m_start->setMode(1);
			m_start = nullptr;
			break;
		case 2:
			clearPath();
			m_end->setMode(2);
			m_end = nullptr;
			break;

		}
	}


}

void TileManager::reset()
{
	for (auto& i : m_grid)
	{
		i->reset();
	}
	m_start = nullptr;
	m_end = nullptr;
	gridChanged = true;
	m_highestCost = 0;
	m_pathCost = 0;
}




void TileManager::update()
{


	if (gridChanged)
	{
		for (auto& i : m_grid)
		{
			i->update();
		}



		checkCount++;
		if (checkCount == 1)
		{
			setUpVectorField();
		}
		if (checkCount == 2)
		{
			checkCount = 0;
			gridChanged = false;
			showPath();
		}

	}

}


void TileManager::showPath()
{

	if (m_end != nullptr && m_start != nullptr)
	{
		if (m_end->getSteps() == -1 || m_start->getSteps() == -1)
		{
			clearPath();
		}
		if (m_end->getSteps() != -1)
		{
			m_pathCost = 0;
			clearPath();
			Tile* m_currentTile = m_end->getLowestNeighbour();
			m_pathCost += m_end->getValue();
			if (m_currentTile != m_start)
			{
				while (m_currentTile != m_start)
				{
					m_pathCost += m_currentTile->getValue();
					m_currentTile->setMode(4);
					m_currentTile = m_currentTile->getLowestNeighbour();
				}
			}
		}
	}

}

int  TileManager::getHighestCost()
{
	return m_highestCost;
}

int TileManager::getPathCost()
{
	return m_pathCost;
}

bool TileManager::withinBounds(sf::Vector2i t_point)
{
	if (t_point.x >= m_startingPos.x && t_point.x <= (m_startingPos.x + (m_gridSize.x * (m_tileSize.x + m_tileGap.x))))
	{
		if (t_point.y >= m_startingPos.y && t_point.y <= (m_startingPos.y + (m_gridSize.y * (m_tileSize.y + m_tileGap.y))))
		{
			return true;
		}
	}
	return false;
}

void TileManager::clearPath()
{
	for (auto& i : m_grid)
	{
		if (i->getMode() == 4)
		{
			i->setMode(4);
		}
	}
}


float TileManager::length(sf::Vector2f t_left, sf::Vector2f t_right)
{
	sf::Vector2f vectorBetween = t_right - t_left;
	return sqrt((vectorBetween.x * vectorBetween.x) + (vectorBetween.y * vectorBetween.y));
}

void TileManager::setGoal(sf::Vector2i t_goal)
{
	if (withinBounds(t_goal))
	{
		sf::Vector2i temp;
		temp.x = t_goal.x - m_startingPos.x;
		temp.y = t_goal.y - m_startingPos.y;

		Tile* i = getTileAt(temp);
		if (i->getMode() != 3 && i->getMode() != 1)//if it's not an obstacle or a goal
		{
			gridChanged = true;
			resetOldTile(i, 1);
			if (m_start != nullptr)
			{
				m_start->setMode(1);
			}
			m_start = i;
			setUpVectorGrid();
			i->setMode(1);
			
		}
	}
}

void TileManager::setUpVectorGrid()
{
	if (m_start != nullptr)
	{
		sf::Vector2f m_midPoint;
		m_midPoint.x = m_tileSize.x / 2;
		m_midPoint.y = m_tileSize.y / 2;
		for (auto& i : m_grid)
		{
			i->resetSteps();
			i->setHeuristic(length((i->getPos() + m_midPoint), (m_start->getPos() + m_midPoint)));
		}
		m_start->setSteps(0);
		std::deque<Tile*> brushList;
		brushList.push_back(m_start);
		int count = 0;
		m_highestCost = 0;
		while (brushList.empty() != true)
		{
			Tile* currentTile = brushList.front();
			brushList.pop_front();

			std::vector<Tile*> neighbours = currentTile->getNeighbours();

			for (auto& i : neighbours)
			{
				count++;
				if ((currentTile->getSteps() + 1 < i->getSteps() || i->getSteps() == -1) && i->getMode() != 3)
				{
					i->setSteps(currentTile->getSteps() + 1);
					brushList.push_back(i);
					if (currentTile->getSteps() + 1 > m_highestCost)
					{
						m_highestCost = currentTile->getSteps() + 1;
					}
				}
			}
		}
	}

}

void TileManager::setUpVectorField()
{

	for (auto& i : m_grid)
	{
		i->findLowestNeighbour();
	}
}

void TileManager::setUpGrid() {

	int xCount = 0;
	int yCount = 0;
	for (auto& i : m_grid) {
		if (yCount <= m_gridSize.y)
		{
			i->setPos(sf::Vector2f(m_startingPos.x + ((m_tileSize.x + m_tileGap.x) * xCount), m_startingPos.y + ((m_tileSize.y + m_tileGap.y) * yCount)));
			i->setSize(m_tileSize);
			i->setID(sf::Vector2f(xCount, yCount));
			xCount++;

			if (xCount > m_gridSize.x) {
				xCount = 0;
				yCount++;
			}
		}
	}
	for (auto& i : m_grid) {
		sf::Vector2f tempID = i->getID();
		//Starting at the 12 o clock position and working clockwise.
		if (i->getID().y - 1 >= 0) {//Top
			i->setNeighbours(getTile(sf::Vector2f(i->getID().x, i->getID().y - 1)));
		}
		if (i->getID().x + 1 <= m_gridSize.x && i->getID().y - 1 >= 0) {//Top Right
			i->setNeighbours(getTile(sf::Vector2f(i->getID().x + 1, i->getID().y - 1)));
		}
		if (i->getID().x + 1 <= m_gridSize.x) {//Centre Right
			i->setNeighbours(getTile(sf::Vector2f(i->getID().x + 1, i->getID().y)));
		}
		if (i->getID().x + 1 <= m_gridSize.x && i->getID().y + 1 <= m_gridSize.y) {//Bot Right
			i->setNeighbours(getTile(sf::Vector2f(i->getID().x + 1, i->getID().y + 1)));
		}
		if (i->getID().y + 1 <= m_gridSize.y) {//Bot
			i->setNeighbours(getTile(sf::Vector2f(i->getID().x, i->getID().y + 1)));
		}
		if (i->getID().x - 1 >= 0 && i->getID().y + 1 <= m_gridSize.y) {//Bot Left
			i->setNeighbours(getTile(sf::Vector2f(i->getID().x - 1, i->getID().y + 1)));
		}
		if (i->getID().x - 1 >= 0) {//Centre Left
			i->setNeighbours(getTile(sf::Vector2f(i->getID().x - 1, i->getID().y)));
		}
		if (i->getID().x - 1 >= 0 && i->getID().y - 1 >= 0) {//Top Left
			i->setNeighbours(getTile(sf::Vector2f(i->getID().x - 1, i->getID().y - 1)));
		}
	}

}
