#pragma once
#include "Pch.hpp"
#include "Helpers.hpp"

enum Origin {
    North  = 1 << 0,
    West   = 1 << 1,
    South  = 1 << 2,
    East   = 1 << 3,
    Center = 1 << 4,
};

void setOrigin(sf::Transformable* object, const Vec2f& size, int anchor);
void setOrigin(sf::Transformable* object, const sf::FloatRect& rect, int anchor);
void setOrigin(tgui::Widget::Ptr widget, int anchor);
Vec2f originIMPL_(const Vec2f& size, int anchor);

Vec2f getCorner(sf::Transformable* object, const sf::FloatRect& rect, int anchor);
Lay2d getCorner(tg::Widget::Ptr widget, int anchor);