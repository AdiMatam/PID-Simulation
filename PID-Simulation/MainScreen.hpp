#pragma once

#include "SF-Core/Core.hpp"

class MainScreen : public BaseScreen {
public:
	MainScreen();
	void onEvent(const sf::Event& ev) override;
	void onUpdate() override;

	void setupGeometry();
	float calculateDistance();
	void applyInstantaneousForce();
	float controlScheme();

private:
	sf::RectangleShape m_Yoke;
	sf::RectangleShape m_Ground;
	float m_RefDist;
	float m_CurDist;
	float m_InitDist;

	float	m_KP;

	float m_Dy;
	float m_CurrentAccel;

	// float m_Blah;
	// int COUNT;

	sf::Clock m_Clock;
	float m_RefreshRate;

};

