#pragma once

#include "Pch.hpp"

class Image : public sf::Drawable {
private:
    sf::Texture m_Texture;
    sf::Vector2f m_Size;
    std::string m_File;
    std::vector<sf::Sprite> m_Sprites;
public:
    Image() = default;
    Image(const std::string& file);
    void load(const std::string& file);
    sf::Sprite* newSprite();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Vector2f getSize();
};