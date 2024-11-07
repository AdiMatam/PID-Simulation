#include "MainScreen.hpp"

MainScreen::MainScreen() {
	std::cout << "Main Screen Loaded\n";

	m_RefDist = 200.;
	m_CurDist = this->calculateDistance();
	m_RefreshRate = 10.;	
	m_Dy = 0.f;
	m_Blah =0.f;
	COUNT = 0;

	setupGeometry();
}

void MainScreen::onEvent(const sf::Event& ev) {
	BaseScreen::onEvent(ev);
}

void MainScreen::onUpdate() {
	sf::RenderWindow* window = App::GetWindowManager(0)->getWindow();
	window->clear();

	if (m_Clock.getElapsedTime().asMilliseconds() >= m_RefreshRate) {
		m_Clock.restart();
		this->gravity();

		// if (COUNT == 100) {
			// std::cout << m_Blah << std::endl;
			// COUNT = 0;
		// }

		// Vec2f yoke = getCorner(&m_Yoke, m_Yoke.getGlobalBounds(), Origin::South);
		// std::cout << yoke.y << std::endl;

		// COUNT++;
	}

	window->draw(m_Ground);
	window->draw(m_Yoke);

	window->display();
}

void MainScreen::gravity() {
	// try 5 pixel/s	
	// float dy = 5.f / (1000/m_RefreshRate);
	// m_Yoke.move(Vec2f(0.0f, dy));	

	// try 5 pixel/s^2
    const float acceleration = 5.0f;
    float timeInterval = m_RefreshRate / 1000.0f;
    m_Dy += (acceleration * timeInterval);

	// m_Blah += m_Dy;
	if (this->calculateDistance() > 0.f)
		m_Yoke.move(Vec2f(0.0f, m_Dy));
}

float MainScreen::calculateDistance() {
	Vec2f yoke = getCorner(&m_Yoke, m_Yoke.getGlobalBounds(), Origin::South);
	Vec2f gnd = getCorner(&m_Ground, m_Ground.getGlobalBounds(), Origin::North);

	float dist = gnd.y - yoke.y;
	return  dist;
}

void MainScreen::setupGeometry() {
	m_Ground.setFillColor(sf::Color::White);	
	m_Ground.setSize(REL_VIEW(1.0f, 0.15f));
	setOrigin(&m_Ground, m_Ground.getSize(), Origin::North | Origin::West);
	m_Ground.setPosition(REL_VIEW(0.0f, 0.85f));


	m_Yoke.setFillColor(sf::Color::Red);
	m_Yoke.setSize( Vec2f(REL_VIEW_Y(0.2f), REL_VIEW_Y(0.2f)) );
	setOrigin(&m_Yoke, m_Yoke.getSize(), Origin::Center);
	m_Yoke.setPosition(REL_VIEW(0.5, 0.33));
}



