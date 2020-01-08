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
		//m_textureHolder.acquire(TextureID::SPLASH, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\splash.jpg"));
		m_textureHolder.acquire(TextureID::PLAYERSPRITE, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\player.png"));
		m_textureHolder.acquire(TextureID::BULLET, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\bullet.png"));
		m_textureHolder.acquire(TextureID::WORKER, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\worker.png"));
		//m_textureHolder.acquire(TextureID::PLANETSOLID, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\Solid.png"));
		//m_textureHolder.acquire(TextureID::GOALSPRITE, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\EndPoint.png"));
		//m_textureHolder.acquire(TextureID::ARROW_INDICATOR, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\arrowDirection.png"));
		//m_textureHolder.acquire(TextureID::PORTALSPRITE, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\Portal.png"));
		//m_textureHolder.acquire(TextureID::PLAYER_SHEET, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\spriteSheet.png"));

		//m_textureHolder.acquire(TextureID::PLANETGAS, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\Gas.png"));
		//m_textureHolder.acquire(TextureID::PLANETLIQUID, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\Liquid.png"));

		//m_textureHolder.acquire(TextureID::PLAYER_SHEET_LEFT, thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\spriteSheetLeft.png"));
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

