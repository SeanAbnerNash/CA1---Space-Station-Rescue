/// <summary>
/// Patryk Wysocki - C00213855
/// 
/// </summary>

#include "ResourceManager.h"

ResourceManager::ResourceManager() // default constructor
{
	// load all assets into holders
	loadTextures();
	//loadFonts();
	//loadBuffers();
}

ResourceManager::~ResourceManager() // default destructor
{
}

sf::Texture & ResourceManager::getTexture(TextureID t_textureID)
{
	return m_textureHolder[t_textureID];
}

sf::Font & ResourceManager::getFont(FontID t_fontID)
{
	return m_fontHolder[t_fontID];
}

sf::SoundBuffer & ResourceManager::getBuffer(SoundBufferID t_bufferID)
{
	return m_bufferHolder[t_bufferID];
}

void ResourceManager::loadTextures()
{
	try
	{
		m_textureHolder.acquire(TextureID::PLAYERSPRITE, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\player.png"));
		m_textureHolder.acquire(TextureID::BULLET, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\bullet.png"));
		m_textureHolder.acquire(TextureID::WORKER, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\worker.png"));
		m_textureHolder.acquire(TextureID::BOMB, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\bomb.png"));
		m_textureHolder.acquire(TextureID::SHIELD, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\shield.png"));
		m_textureHolder.acquire(TextureID::MAPGRID11, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\Map_1-1.png"));
		m_textureHolder.acquire(TextureID::MAPGRID21, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\Map_2-1.png"));
		m_textureHolder.acquire(TextureID::MAPGRID31, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\Map_3-1.png"));

		m_textureHolder.acquire(TextureID::MAPGRID12, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\Map_1-2.png"));
		m_textureHolder.acquire(TextureID::MAPGRID22, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\Map_2-2.png"));
		m_textureHolder.acquire(TextureID::MAPGRID32, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\Map_3-2.png"));

		m_textureHolder.acquire(TextureID::MAPGRID13, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\Map_1-3.png"));
		m_textureHolder.acquire(TextureID::MAPGRID23, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\Map_2-3.png"));
		m_textureHolder.acquire(TextureID::MAPGRID33, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\Map_3-3.png"));

		m_textureHolder.acquire(TextureID::MISSILE, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\missile.png"));
		m_textureHolder.acquire(TextureID::NEST, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\nest.png"));

		//TODO: create the texture
		//m_textureHolder.acquire(TextureID::WORLDMAP, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\worldMap.png"));
	}
	catch (thor::ResourceLoadingException& e)
	{
		std::cout << "Error with texture: " << e.what() << std::endl;
	}
}

void ResourceManager::loadFonts()
{
	try
	{
		//m_fontHolder.acquire(FontID::ARIBLK, thor::Resources::fromFile<sf::Font>("ASSETS\\FONTS\\ariblk.ttf"));
		//m_fontHolder.acquire(FontID::ORDINARY, thor::Resources::fromFile<sf::Font>("ASSETS\\FONTS\\Ordinary.ttf"));

	}
	catch (thor::ResourceLoadingException& e)
	{
		//std::cout << "Error with font: " << e.what() << std::endl;
	}
}

void ResourceManager::loadBuffers()
{
	try
	{
		//m_bufferHolder.acquire(SoundBufferID::BUTTON_CLICK, thor::Resources::fromFile<sf::SoundBuffer>("ASSETS\\SOUNDS\\buttonClick.wav"));
	}
	catch (thor::ResourceLoadingException& e)
	{
		//std::cout << "Error with buffer: " << e.what() << std::endl;
	}
}

