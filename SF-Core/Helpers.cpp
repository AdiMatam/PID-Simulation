#include "Pch.hpp"
#include "Helpers.hpp"

Vec2f layToVec(const Lay2d& lay) {
    return Vec2f(lay.x.getValue(), lay.y.getValue());
}

void scaleTo(sf::Transformable* object, const Vec2f& srcSize, const Vec2f& targSize) {
    Vec2f scaleFactors = Vec2f(targSize.x / srcSize.x, targSize.y / srcSize.y);
    object->setScale(scaleFactors);
}

float distance(const Vec2f& p1, const Vec2f& p2) {
    float inRadical = powf(p2.x - p1.x, 2) + powf(p2.y - p1.y, 2);
    return powf(inRadical, 0.5f);
}

bool keyPressed(const sf::Event& ev, sf::Keyboard::Key code) {
    return (ev.type == sf::Event::KeyPressed and
        ev.key.code == code);
}

Vec2f operator*(const Vec2f& left, const Vec2f& right) {
    return Vec2f(left.x * right.x, left.y * right.y);
}

float clamp(float val, float floorVal, float ceilVal) {
	return std::min(std::max(val, floorVal), ceilVal);
}

int enumBitCount(int x) {
    int count = 0;
    while(x != 0) {
        if((x & 1) != 0) 
            count++;
        x >>= 1;
    }
    return count;
}

void printColor(const tgui::Color& c) {
    std::cout << "[" <<
        int(c.getRed())   << ", " <<
        int(c.getGreen()) << ", " <<
        int(c.getBlue())  << ", " <<
        int(c.getAlpha()) << "]\n";
}

float toDegrees(float radians) {
    return (180 / M_PI) * radians;
}