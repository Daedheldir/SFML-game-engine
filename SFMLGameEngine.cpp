#include "SFMLGameEngine.h"

dh::SFMLGameEngine::SFMLGameEngine(GameDataRef m_gameData, sf::Vector2u uWindowSize, std::string appName, unsigned int maxUpdatesPerSecond, uint8_t fpsLimit, bool fullscreen) :
	m_gameData(m_gameData),
	graphics(m_gameData, uWindowSize, appName, fullscreen, 1.0f / static_cast<float>(fpsLimit)),
	logic(m_gameData, 1.0f / static_cast<float>(maxUpdatesPerSecond))
{
	std::cout << "Engine constructed.\n" << std::endl;
}

dh::SFMLGameEngine::SFMLGameEngine(GameDataRef m_gameData, std::string appName, unsigned int maxUpdatesPerSecond, uint8_t fpsLimit, bool fullscreen) :
	m_gameData(m_gameData),
	graphics(m_gameData,appName, fullscreen, 1.0f / static_cast<float>(fpsLimit)),
	logic(m_gameData, 1.0f / static_cast<float>(maxUpdatesPerSecond))
{
	std::cout << "Engine constructed.\n" << std::endl;
}


dh::SFMLGameEngine::~SFMLGameEngine()
{
}

dh::GraphicsEngine & dh::SFMLGameEngine::getGraphics()
{
	return graphics;
}

bool dh::SFMLGameEngine::isGameRunning()
{
	return this->m_gameData->bGameRunning;
}

void dh::SFMLGameEngine::Run()
{
	this->m_gameData->bGameRunning = true;

	graphics.getRenderWindow().setActive(false);

	std::cout << "Creating threads..." << std::endl;

	graphics.startRenderingThread(std::bind(&dh::SFMLGameEngine::handleDrawing, this));
	logic.startLogicThread(std::bind(&dh::SFMLGameEngine::handleLogic, this));

	std::cout << "\tThreads created.\n" << std::endl;

	std::cout << "Engine started!" << std::endl;

	while (this->m_gameData->bGameRunning)
	{
		fEventsElapsedTime = eventsClk.restart().asSeconds();
		m_pollEvents();
	}
}

void dh::SFMLGameEngine::m_pollEvents()
{
	sf::Event events;

	while (graphics.getRenderWindow().pollEvent(events)) {

		handleEvents(events);
	}

	handleInput();
}


