#pragma once

#include "SF-Core/Core.hpp"

class MainScreen : public BaseScreen {
public:
	MainScreen();
	void onEvent(const sf::Event& ev) override;
	void onUpdate() override;

	void setupGeometry();
	float calculateDistance();
	void gravity();

private:
	sf::RectangleShape m_Yoke;
	sf::RectangleShape m_Ground;
	float m_RefDist;
	float m_CurDist;
	float m_Dy;

	float m_Blah;
	int COUNT;

	sf::Clock m_Clock;
	float m_RefreshRate;

};

