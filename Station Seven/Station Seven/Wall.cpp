#include "Wall.h"

/// <summary>
/// Wall Constructor
/// </summary>
/// <returns></returns>
Wall::Wall(sf::Vector2f t_pos, ResourceManager& t_resources, sf::Vector2f t_otherCorner)
{
	m_position = t_pos;
	//m_resourceMng = t_resources;
	m_size.x = t_otherCorner.x - t_pos.x;
	m_size.y = t_otherCorner.y - t_pos.y;
	m_shape.setFillColor(m_colour);
	m_shape.setPosition(m_position);
	m_shape.setSize(m_size);
	m_centre = { m_position.x + m_size.x / 2, m_position.y + m_size.y / 2 };
}

Wall::~Wall()
{
}


/// <summary>
/// Collision between a Circle and a Rectangle. 
/// Inputs: Circle centre as t_pos, and circle Radius as t_radius
/// </summary>
/// <returns></returns>
bool Wall::collisionWithSphere(sf::Vector2f t_pos, float t_radius)
{
	sf::Vector2f circleDistance;
	 circleDistance.x = abs(t_pos.x - m_centre.x);
	 circleDistance.y = abs(t_pos.y - m_centre.y);

	if (circleDistance.x > (m_size.x / 2 + t_radius)) { return false; }
	if (circleDistance.y > (m_size.y / 2 + t_radius)) { return false; }

	if (circleDistance.x <= (m_size.x / 2)) { return true; }
	if (circleDistance.y <= (m_size.y / 2)) { return true; }

	float cornerDistance_sq = ((circleDistance.x - m_size.x / 2) * (circleDistance.x - m_size.x / 2));
	cornerDistance_sq += (circleDistance.y - m_size.y / 2) * (circleDistance.y - m_size.y / 2);

	return (cornerDistance_sq <= (t_radius * t_radius));
}

void Wall::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_shape);
}
