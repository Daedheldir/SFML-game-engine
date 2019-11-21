
#include "SFMLGameEngine.h"

class test : public dh::SFMLGameEngine {
public:
	test(dh::GameDataRef m_gameData) : m_gameData(m_gameData), SFMLGameEngine(m_gameData, "test", 60, 60, true) {

	}
protected:
	dh::GameDataRef m_gameData;
	void loadResources() {};
	void handleEvents(sf::Event & ev) {};
	void handleInput() {};
	void handleLogic() {  };
	void handleDrawing() { getGraphics().getRenderWindow().clear(); getGraphics().getRenderWindow().draw(sf::RectangleShape({ 80.0f, 20.0f })); getGraphics().getRenderWindow().display(); };
};

int main() {
	dh::GameDataRef m_gameData = std::make_shared<dh::GameData>();
	test t(m_gameData);
	t.Run();
	return 0;
}