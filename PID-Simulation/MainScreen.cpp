#include "MainScreen.hpp"
#include "LabeledEditBox.hpp"

MainScreen::MainScreen() {
	std::cout << "Main Screen Loaded\n";

	m_RefDist = 400.;
	m_InitDist = 150.;
	m_KP = 0.2;
	m_KD = 2.0;
	m_KI = 5.0;

	m_RefreshRate = 10.;	
	m_Dy = 0.f;
	m_AppliedAccel = 0.0f;
	m_GravityAccel = 2.5f;

	m_PrevErr = 0.f;

	m_Font = tg::Font("../../font/Barlow-Regular.ttf");
	m_Paused = true;

	setupGeometry();
	setupWidgets();
	// m_Blah =0.f;
	// COUNT = 0;
}

void MainScreen::onEvent(const sf::Event& ev) {
	BaseScreen::onEvent(ev);
	if (keyPressed(ev, sf::Keyboard::Space)) {
		m_Paused = !m_Paused;
	}
	else if (keyPressed(ev, sf::Keyboard::Q)) {
		App::GetWindowManager(0)->close();
	}
	else if (keyPressed(ev, sf::Keyboard::Down)) {
		m_RefDist -= 10.0f;
	}
	else if (keyPressed(ev, sf::Keyboard::Up)) {
		m_RefDist += 10.0f;
	}
}

void MainScreen::onUpdate() {
	sf::RenderWindow* window = App::GetWindowManager(0)->getWindow();
	tg::Gui* gui = App::GetWindowManager(0)->getGui();

	if (m_Clock.getElapsedTime().asMilliseconds() >= m_RefreshRate && !m_Paused) {
		m_Clock.restart();
		
		m_CurDist = this->calculateDistance();
		m_AppliedAccel = this->controlScheme();
		this->applyInstantaneousForce(m_GravityAccel + m_AppliedAccel);

		std::cout << std::fixed << std::setprecision(2)    // Fixed-point notation with 2 decimal places
			<< std::setw(12) << m_AppliedAccel
			<< std::setw(12) << m_Dy << '\n';

		// if (COUNT == 100) {
			// std::cout << m_Blah << std::endl;
			// COUNT = 0;
		// }

		// Vec2f yoke = getCorner(&m_Yoke, m_Yoke.getGlobalBounds(), Origin::South);
		// std::cout << yoke.y << std::endl;

		// COUNT++;
	}

	CallbackManager::Get().Poll(this);

	window->clear();

	if (m_Paused) {
		window->draw(m_PauseBars[0]);
		window->draw(m_PauseBars[1]);
	}

	window->draw(m_Ground);
	window->draw(m_RefLine);
	window->draw(m_Yoke);

	gui->draw();

	window->display();
}

float MainScreen::controlScheme() {
	// CLAMPED ACCELERATION
	float accel;
	float err = m_CurDist - m_RefDist;
	float derr = err - m_PrevErr;
	float ierr = 0.f;

	if (abs(derr) < 0.1)  {
		ierr = m_PrevErr + err;
		ierr = clamp(ierr, -0.5f, 0.5f);
	}
	// else {
		// printf("hmm: %d\n", COUNT);
		// COUNT++;
	// }

	accel = m_KP * err + m_KD * derr + m_KI * ierr;
	m_PrevErr = err; 

	float bound = m_GravityAccel * 4.f;
	accel = clamp(accel, -bound, bound);
	return accel;
}

void MainScreen::applyInstantaneousForce(float accel) {
	// INVALID CASE TO BE HANDLED BY IF
	if (m_CurDist <= 0.f) {
		m_Dy = 0;		
	}

	// try 5 pixel/s	
	// float dy = 5.f / (1000/m_RefreshRate);
	// m_Yoke.move(Vec2f(0.0f, dy));	

	// try 5 pixel/s^2
    float timeInterval = m_RefreshRate / 1000.0f;
    m_Dy += (accel * timeInterval);

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
	
	m_GroundNorth = getCorner(&m_Ground, m_Ground.getGlobalBounds(), Origin::North);
	m_Yoke.setPosition(REL_VIEW_X(0.5), m_GroundNorth.y - m_InitDist);

	m_CurDist = this->calculateDistance();

	m_RefLine.setFillColor(sf::Color::Blue);;
	m_RefLine.setSize(REL_VIEW(1.0f, 0.01f));
	setOrigin(&m_RefLine, m_RefLine.getGlobalBounds(), Origin::Center);
	
	CallbackManager::Get().Add(
		Callback(
			this, &m_RefDist, CallbackTrigger::OnChange,
			[this]() { m_RefLine.setPosition(REL_VIEW_X(0.5f), m_GroundNorth.y - m_RefDist); },
			true
		)
	);

	for (int i = 0; i < 2; i++) {
		m_PauseBars[i].setFillColor(sf::Color::White);
		m_PauseBars[i].setSize(REL_VIEW(0.01f, 0.07f));
		setOrigin(&m_PauseBars[i], m_PauseBars[i].getGlobalBounds(), Origin::North | Origin::West);
		m_PauseBars[i].setPosition(REL_VIEW(0.02f, 0.02f));
	}
	m_PauseBars[1].move(REL_VIEW_X(0.02f), 0.f);
}


void MainScreen::setupWidgets() {
	tg::Gui* gui = App::GetWindowManager(0)->getGui();
	gui->setFont(m_Font);
	gui->setTextSize(REL_GUI_Y(0.03f));

	float relx = 0.80f;

	auto liveDistLabel = tgui::Label::create();
	liveDistLabel->setSize(REL_GUI(0.2f, 0.05f));
	liveDistLabel->setPosition(REL_GUI(relx, 0.02f));
	liveDistLabel->getSharedRenderer()->setTextColor(tg::Color::White);

	CallbackManager::Get().Add(
		Callback(
			this, &m_CurDist, CallbackTrigger::OnChange,
			[this,liveDistLabel]() { 
				char str[32];
				sprintf(str, "Dist:          %.2f, %.2f", m_CurDist, m_CurDist-m_RefDist);
				liveDistLabel->setText(tg::String(str));
			},
			true
		)
	);
	gui->add(liveDistLabel);

	m_RefDistBundle = NewRef<LabeledEditBox>(this, REL_GUI(relx, 0.07f), "Ref Dist: ", &m_RefDist);
	m_RefDistBundle->addToRenderer(gui);

	m_KpBundle = NewRef<LabeledEditBox>(this, REL_GUI(relx, 0.13f), "KP: ", &m_KP);
	m_KpBundle->addToRenderer(gui);

	m_KiBundle = NewRef<LabeledEditBox>(this, REL_GUI(relx, 0.19f), "KI: ", &m_KI);
	m_KiBundle->addToRenderer(gui);

	m_KdBundle = NewRef<LabeledEditBox>(this, REL_GUI(relx, 0.25f), "KD: ", &m_KD);
	m_KdBundle->addToRenderer(gui);





	// HORRIBLE SCOPING BUT IDFC
	{
		m_RefDistBundle->edit->getSharedRenderer()->setBorderColor(tg::Color::White);
		m_RefDistBundle->edit->getSharedRenderer()->setBorderColorHover(tg::Color::White);
		m_RefDistBundle->edit->getSharedRenderer()->setBorderColorFocused(tg::Color::White);
		m_RefDistBundle->edit->getSharedRenderer()->setBackgroundColor(tg::Color::Transparent);
		m_RefDistBundle->edit->getSharedRenderer()->setBackgroundColorHover(tg::Color(25, 25, 25));
		m_RefDistBundle->edit->getSharedRenderer()->setBackgroundColorFocused(tg::Color(25, 25, 25));
		m_RefDistBundle->edit->getSharedRenderer()->setTextColor(tg::Color::White);
		m_RefDistBundle->edit->getSharedRenderer()->setCaretColor(tg::Color::White);
		m_RefDistBundle->edit->getSharedRenderer()->setCaretColorHover(tg::Color::White);
		m_RefDistBundle->edit->getSharedRenderer()->setCaretColorFocused(tg::Color::White);

	}
}


