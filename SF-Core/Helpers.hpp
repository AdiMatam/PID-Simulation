#pragma once

#include "Pch.hpp"

typedef int ScreenKey;

template <typename K, typename V>
bool mapContains(const HashMap<K, V>& map, K item) {
    return (map.find(item) != map.end());
}

// void relTo(sf::Transformable* object, const Vec2f& rels);
Vec2f layToVec(const Lay2d& lay);
void scaleTo(sf::Transformable* object, const Vec2f& srcSize, const Vec2f& targSize);
float distance(const Vec2f& p1, const Vec2f& p2);

template <typename T>
void setAlpha(T* object, int alpha) {
    sf::Color c = object->getFillColor();
    c.a = alpha;
    object->setFillColor(c);
}

template <typename T>
int getAlpha(T* object) {
    return object->getFillColor().a;
}

bool keyPressed(const sf::Event& ev, sf::Keyboard::Key code);
//inline char charFromKeyCode(sf::Keyboard::Key code) {
//
//}

Vec2f operator*(const Vec2f& left, const Vec2f& right);


float clamp(float val, float floorVal, float ceilVal);

int enumBitCount(int x);
inline bool containsFlag(int value, int check) {
    return ((value & check) == check);
}

void printColor(const tgui::Color& c);

template <typename T>
void printVector(const T& vec) {
    std::cout << "[" << vec.x << ", " << vec.y << "]\n";
}

float toDegrees(float radians);