#pragma once

#include "Pch.hpp"
#include "Core.hpp"
//#include <SFML/Audio.hpp>

void moveWidget(tg::Widget::Ptr widget, Vec2f moveFactor);

struct ButtonTextPair {
public:
	tg::Button::Ptr button;
	tg::Label::Ptr label;
	bool pressed = false;

	static constexpr float TXT_JUMP = 0.01f;

	ButtonTextPair() = default;
	void setup(const std::string& message);
	void setPosition(Vec2f pos);
	// void addToRenderer();
	// void removeFromRenderer();
};