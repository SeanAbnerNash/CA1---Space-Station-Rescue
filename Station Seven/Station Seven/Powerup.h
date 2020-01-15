#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "Maths.h"
enum POWERUPTYPE
{
	SHIELD,
	SHOT360
};

class Powerup
{
	public:
		Powerup(sf::Vector2f t_pos,POWERUPTYPE t_type, ResourceManager& t_resources);
		~Powerup();
		void render(sf::RenderWindow &t_window);
		void update();
		void setAlive(bool t_alive);
		bool getAlive();
		POWERUPTYPE getPowerupType();
		bool collisionDetection(sf::Vector2f t_playerPos);
	private:
		sf::Vector2f m_position;
		sf::Vector2f m_spriteDimensions{ 100,100 };
		bool m_isAlive;
		sf::Sprite m_powerupSprite;
		POWERUPTYPE m_powerUpType;
		ResourceManager& m_resourceMng;
	
};