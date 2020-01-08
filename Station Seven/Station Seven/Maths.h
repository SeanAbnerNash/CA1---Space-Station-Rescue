#ifndef MATHS_H
#define MATHS_H
#include "SFML/Graphics.hpp"
static const float PI = 3.14159265358979323846;
class Maths
{
public:

	static inline float getNewOrientation(float t_rot, sf::Vector2f t_vel)
	{
		if (getLength(t_vel) > 0)
		{
			return (atan2(t_vel.y, t_vel.x)) * (180 / PI);
		}
		else
		{
			return t_rot;
		}
	}

	static inline float getLength(sf::Vector2f t_v)
	{
		return sqrt((t_v.x * t_v.x) + (t_v.y * t_v.y));
	}

	static inline sf::Vector2f normalize(sf::Vector2f t_v)
	{
		float length = getLength(t_v);

		if (length != 0)
		{
			t_v.x = t_v.x / length;
			t_v.y = t_v.y / length;
		}
		return t_v;
	}

	static inline  float dist(sf::Vector2f t_v1, sf::Vector2f t_v2)
	{
		float distance = std::sqrt(((t_v1.x - t_v2.x) * (t_v1.x - t_v2.x)) + ((t_v1.y - t_v2.y) * (t_v1.y - t_v2.y)));
		return distance;
	}
};
	

#endif //!MATHS_H