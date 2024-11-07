#pragma once

#include "Pch.hpp"

class BaseScreen {
protected:

    BaseScreen() = default;
public:
    virtual void onUpdate();
    virtual void onEvent(const sf::Event& ev);
    virtual void setupGeometry(); 
    virtual void setupWidgets(); 
};