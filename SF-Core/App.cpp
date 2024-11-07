#include "Pch.hpp"
#include "App.hpp"


std::vector<WindowManager*> App::m_Windows;
ScreenLoaderMap* App::m_ScreenLoaders;

//static
App& App::Get() {
	static App s_Instance;
	return s_Instance;
}

//static
void App::SetScreenLoaders(ScreenLoaderMap* loaders) {
    m_ScreenLoaders = loaders;
}

// static
void App::SetScreen(int index, Screens screen, bool reload) {
    LoaderWrap* wrap = &m_ScreenLoaders->at(screen);
    if (!wrap->instance || reload)
        wrap->instance = wrap->loader();
    m_Windows[index]->setScreen(wrap->instance);
}

//static 
WindowManager* App::GetWindowManager(int index) {
    return m_Windows[index];
}

//static 
void App::CreateWindows(int count) {
    for (int i = 0; i < count; i++) {
        m_Windows.push_back(new WindowManager());
    }
}

//static
void App::Activate(int index) {
    m_Windows[index]->run();
    // m_Thread = std::thread(&WindowManager::run, m_Windows[index]);
}

//static
void App::Activate(WindowManager* manager) {

}

App::~App() {
    for (WindowManager* window : m_Windows) {
        delete window;
    }
}
