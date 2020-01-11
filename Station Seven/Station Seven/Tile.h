#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
public:
	Tile(int t_x, int t_y, int t_size, int t_obstacle);
	~Tile();
	double getVectX();
	int getPositionX();
	int getPositionY();
	double getVectY();
	void setCost(double t_cost);
	void setDistance(int t_x, int t_y);
	void setVector(double t_v1, double t_v2);
	void setIntegrationField(double t_field);
	void costSet(int num);
	double getCost();
	double getIntegrationField();
	bool isCostSet();
	int getRectSize();
	void draw(sf::RenderWindow& t_window);

private:
	int m_rectSize;
	double m_vectX = 0;
	double m_vectY = 0;
	double m_integrationField = 0;
	sf::RectangleShape m_rect;
	bool m_setCost;
	double m_cost = 0;
};