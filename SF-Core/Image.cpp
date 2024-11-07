#include "Pch.hpp"
#include "Image.hpp"

Image::Image(const std::string& file) {
    load(file);
}

void Image::load(const std::string& file) {
    m_Texture.loadFromFile(file);
    m_File = file;
    m_Size = (sf::Vector2f)m_Texture.getSize();
    m_Texture.setSmooth(true);
}

sf::Sprite* Image::newSprite() {
    m_Sprites.push_back(sf::Sprite());
    sf::Sprite& sp = m_Sprites.back();
    sp.setTexture(m_Texture);
    return &sp;
}

void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const sf::Sprite& sp : m_Sprites) {
        target.draw(sp, states);
    }
}

sf::Vector2f Image::getSize() {
    return m_Size;
}

