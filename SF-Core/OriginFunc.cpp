#include "Pch.hpp"
#include "OriginFunc.hpp"

void setOrigin(sf::Transformable* object, const Vec2f& size, int anchor) {
    Vec2f out = originIMPL_(size, anchor);
    object->setOrigin(out);
}

void setOrigin(sf::Transformable* object, const sf::FloatRect& rect, int anchor) {
    Vec2f size(rect.width, rect.height);
    Vec2f out = originIMPL_(size, anchor);
    object->setOrigin(out);
}

void setOrigin(tgui::Widget::Ptr object, int anchor) {
    Vec2f out = originIMPL_(Vec2f(1.0f, 1.0f), anchor);
    object->setOrigin(out);
}

Vec2f originIMPL_(const Vec2f& size, int anchor) {
    if (anchor == Origin::Center)
        return (size / 2.f);
    
    auto hasFlag = std::bind(&containsFlag, anchor, std::placeholders::_1);

    float x = -1.f, y = -1.f;
    for (int i = 0; i < 2; i++) {
        if (hasFlag(Origin::North))
            y = 0.f;
        else if (hasFlag(Origin::South))
            y = size.y;
        if (hasFlag(Origin::West))
            x = 0.f;
        else if (hasFlag(Origin::East))
            x = size.x;
    }
    if (x == -1.f) 
        x = size.x / 2.f;
    if (y == -1.f) 
        y = size.y / 2.f;

    return Vec2f(x, y);
}

Vec2f getCorner(sf::Transformable* object, const sf::FloatRect& rect, int anchor) {
    Vec2f size(rect.width, rect.height);
    Vec2f pos(rect.left, rect.top);
    return pos + originIMPL_(size, anchor);
}

Lay2d getCorner(tg::Widget::Ptr widget, int anchor) {
    auto size = widget->getSize();
    auto leftTop = widget->getAbsolutePosition();
    return leftTop + Lay2d(originIMPL_(size, anchor));
}
