#pragma once

#include "SF-Core/Core.hpp"
#include "LabeledEditBox.hpp"

class MainScreen : public BaseScreen {
public:
	MainScreen();
	void onEvent(const sf::Event& ev) override;
	void onUpdate() override;

	void setupGeometry() override;
	void setupWidgets() override;

	float calculateDistance();
	void applyInstantaneousForce(float accel);
	float controlScheme();

private:
	sf::RectangleShape m_Yoke;
	sf::RectangleShape m_Ground;
	sf::RectangleShape m_RefLine;
	Vec2f m_GroundNorth;

	float m_RefDist;
	float m_CurDist;
	float m_InitDist;

	sf::RectangleShape m_PauseBars[2];
	bool m_Paused;

	float	m_KP;
	float	m_KD;
	float	m_KI;
	float m_PrevErr;

	float m_Dy;
	float m_AppliedAccel;
	float m_GravityAccel;

	tg::Font m_Font;

	Ref<LabeledEditBox> m_RefDistBundle;
	Ref<LabeledEditBox> m_KpBundle;
	Ref<LabeledEditBox> m_KiBundle;
	Ref<LabeledEditBox> m_KdBundle;

	// float m_Blah;
	int COUNT;

	sf::Clock m_Clock;
	float m_RefreshRate;
	sf::RenderStates m_States;

};
