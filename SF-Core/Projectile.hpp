#pragma once

#include "Pch.hpp"
#include "Animation.hpp"
#include <queue>

// NOTE: IS A 'PROJECTILE' JUST A TYPE OF ANIMATION (CUSTOM FUNC?)
// MAYBE PROJECTILE FUNC SHOULD RETURN LAMBDA -> PASS TO ANIMATION SYSTEM.

class Projectile {
private:
    sf::Clock clock;
    sf::Time refreshRate;
    std::unordered_map<sf::Transformable*, sf::Time> timeStates;
public:
    Projectile() = default;
    void setPosition(Vec2f pos);
    void setTrajectory(float theta);
    void setTrajectory(Vec2f directionVector);
    
    // either more overloads or template
    void control(sf::Transformable* object);


};