#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>
#include <cmath>
#include <TGUI/TGUI.hpp>
#include <thread>

namespace tg = tgui;

using Vec2f = sf::Vector2f;
using Vec2i = sf::Vector2i;
using Vec2u = sf::Vector2u;
using Lay2d = tg::Layout2d;

template <typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename... Args>
constexpr Ref<T> NewRef(Args&&... args) {
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
using UniqueRef = std::unique_ptr<T>;

template<typename T, typename... Args>
constexpr UniqueRef<T> NewUniqueRef(Args&&... args) {
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename K, typename V>
using HashMap = std::unordered_map<K, V>;