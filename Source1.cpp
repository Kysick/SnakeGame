#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../Framework/Util/FPSCounter.h"
#include "../Framework/States/StateBase.h"
#include "../Framework/Util/NonMoveable.h"


/**
Main controlling class of the game.
Handles state switches and the main loop, as well
as counting the FPS
*/
class Game : public NonCopyable, public NonMovable
{
public:
	Game();

	void run();

	template<typename T>
	void initGame();

	void pushState(std::unique_ptr<StateBase> state);
	void popState();
	void exitGame();

	template<typename T, typename... Args>
	void pushState(Args&&... args);

	template<typename T, typename... Args>
	void changeState(Args&&... args);

	const sf::RenderWindow& getWindow() const;

	void resizeWindow(unsigned width, unsigned height);

private:
	void handleEvent();
	void tryPop();

	StateBase& getCurrentState();

	sf::RenderWindow m_window;
	std::vector < std::unique_ptr < StateBaseĽ m_states;

	FPSCounter counter;

	bool m_shouldPop = true;
	bool m_shouldExit = false;
	bool m_shouldChageState = false;
	std::unique_ptr<StateBase> m_change;

};

template<typename T>
inline void Game::initGame()
{
	this->pushState<T>(*this);
}

template<typename T, typename... Args>
inline void Game::pushState(Args&&... args)
{
	pushState(std::make_unique<T>(std::forward<Args>(args)...));
}

template<typename T, typename ...Args>
inline void Game::changeState(Args && ...args)
{
	m_change = std::make_unique<T>(std::forward<Args>(args)...);
	m_shouldPop = true;
	m_shouldChageState = true;
}