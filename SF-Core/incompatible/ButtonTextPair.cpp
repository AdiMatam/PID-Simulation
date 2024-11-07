#include "Pch.hpp"
#include "ButtonTextPair.hpp"

void moveWidget(tg::Widget::Ptr widget, Vec2f moveFactor) {
	widget->setPosition(
		widget->getPosition() + REL_GUI(moveFactor.x, moveFactor.y)
	);
}

void ButtonTextPair::setup(const std::string& message) {
	auto& rend = WindowManager::Get();
	
	label = tg::Label::create(message);
	// label->getSharedRenderer()->setFont(rend.getResources().font);
	label->getSharedRenderer()->setTextColor(tg::Color::Black);
	label->ignoreMouseEvents();
	setOrigin(label, Origin::Center);
	label->setTextSize(rend.relToGuiView(0.05f, _Impl_Direction::Y));

	button = tg::Button::create();
	// button->setRenderer(rend.getResources().theme.getRenderer("Button"));

	tgConfig(button, Texture,      Color, tg::Color(227, 225, 132));
	tgConfig(button, TextureDown,  Color, tg::Color::White);
	tgConfig(button, TextureHover, Color, tg::Color(255, 252, 130));

	button->setSize(rend.relToGuiView({ 0.4f, 0.3f }));
	setOrigin(button, Origin::Center);

	button->onMousePress(
		[&]() { pressed = true; moveWidget(label, { 0.0f, +TXT_JUMP }); }
	);
	button->onMouseRelease(
		[&]() { pressed = false; moveWidget(label, { 0.0f, -TXT_JUMP }); }
	);
	button->onMouseEnter(
		[&]() { if (pressed) moveWidget(label, { 0.0f, +TXT_JUMP }); }
	);
	button->onMouseLeave(
		[&]() { if (pressed) moveWidget(label, { 0.0f, -TXT_JUMP }); }
	);
}

void ButtonTextPair::setPosition(Vec2f pos) {
	auto actualPos = REL_GUI(pos.x, pos.y);
	button->setPosition(actualPos);
	
	setOrigin(label, Origin::Center);
	label->setPosition(getCorner(button, Origin::Center) - REL_GUI(0.0f, 0.01f));
}

// void ButtonTextPair::addToRenderer() {
// 	WindowManager::Get().add(button);
// 	WindowManager::Get().add(label);
// }

// void ButtonTextPair::removeFromRenderer() {
// 	WindowManager::Get().remove(button);
// 	WindowManager::Get().remove(label);
// }

