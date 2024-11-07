#include "MainScreen.hpp"

MainScreen::MainScreen() {
	std::cout << "Main Screen Loaded\n";

	m_RefDist = 400.;
	m_InitDist = 100.;
	m_KP = 0.01;

	m_RefreshRate = 10.;	
	m_Dy = 0.f;
	m_CurrentAccel = 2.5f;

	setupGeometry();
	// m_Blah =0.f;
	// COUNT = 0;
}

void MainScreen::onEvent(const sf::Event& ev) {
	BaseScreen::onEvent(ev);
	if (keyPressed(ev, sf::Keyboard::Down)) {
		m_CurrentAccel += 1.0f;
	}
	else if (keyPressed(ev, sf::Keyboard::Up)) {
		m_CurrentAccel -= 1.0f;
	}
}

void MainScreen::onUpdate() {
	sf::RenderWindow* window = App::GetWindowManager(0)->getWindow();
	window->clear();

	if (m_Clock.getElapsedTime().asMilliseconds() >= m_RefreshRate) {
		m_Clock.restart();
		
		m_CurDist = this->calculateDistance();
		m_CurrentAccel = this->controlScheme();
		this->applyInstantaneousForce();

		std::cout << std::fixed << std::setprecision(2)    // Fixed-point notation with 2 decimal places
			<< std::setw(12) << m_CurrentAccel
			<< std::setw(12) << m_CurDist << '\n';

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

float MainScreen::controlScheme() {
	// CLAMPED ACCELERATION TO 2.5
	float err = m_CurDist - m_RefDist;
	float accel = m_KP * err;
	accel = clamp(accel, -2.5f, 2.5f);
	return accel;
}

void MainScreen::applyInstantaneousForce() {
	// INVALID CASE TO BE HANDLED BY IF
	if (m_CurDist <= 0.f) {
		m_Dy = 0;		
	}

	// try 5 pixel/s	
	// float dy = 5.f / (1000/m_RefreshRate);
	// m_Yoke.move(Vec2f(0.0f, dy));	

	// try 5 pixel/s^2
    float timeInterval = m_RefreshRate / 1000.0f;
    m_Dy += (m_CurrentAccel * timeInterval);

	// m_Blah += m_Dy;
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
	setOrigin(&m_Yoke, m_Yoke.getSize(), Origin::South);
	
	Vec2f gnd = getCorner(&m_Ground, m_Ground.getGlobalBounds(), Origin::North);
	m_Yoke.setPosition(REL_VIEW_X(0.5), gnd.y - m_InitDist);

	m_CurDist = this->calculateDistance();
}



