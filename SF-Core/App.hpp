#pragma once
#include "Pch.hpp"
#include "Helpers.hpp"
#include "WindowManager.hpp"

enum class Screens;
using ScreenLoader = std::function<BaseScreen*()>;

struct LoaderWrap {
public:
    ScreenLoader loader;
    BaseScreen* instance = nullptr;
    LoaderWrap(ScreenLoader loader)
        : loader(loader) {}
};

using ScreenLoaderMap = std::unordered_map<Screens, LoaderWrap>;

class App {
private:
    static std::vector<WindowManager*> m_Windows;
    static ScreenLoaderMap* m_ScreenLoaders;

private:
	App() = default;
	App(const App&) = delete;
    ~App();

public:
	static App& Get();
    static void SetScreenLoaders(ScreenLoaderMap* loaders);
    static void SetScreen(int index, Screens screen, bool reload);
    static WindowManager* GetWindowManager(int index);
    static void CreateWindows(int count);
    static void Activate(int index);
    static void Activate(WindowManager* manager);
};


#define REL_VIEW_X(x)  App::GetWindowManager(0)->relToView(x, _Impl_Direction::X)
#define REL_VIEW_Y(y)  App::GetWindowManager(0)->relToView(y, _Impl_Direction::Y)
#define REL_GUI_X(x)   App::GetWindowManager(0)->relToGuiView(x, _Impl_Direction::X)
#define REL_GUI_Y(y)   App::GetWindowManager(0)->relToGuiView(y, _Impl_Direction::Y)

#define REL_VIEW(x, y) App::GetWindowManager(0)->relToView({x, y})
#define REL_GUI(x, y)  App::GetWindowManager(0)->relToGuiView({x, y})