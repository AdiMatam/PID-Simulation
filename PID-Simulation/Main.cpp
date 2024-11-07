#include "SF-Core/Core.hpp"
#include "MainScreen.hpp"

enum class Screens {
    MAIN_SCREEN,
};

ScreenLoaderMap screenLoaders = {
    { Screens::MAIN_SCREEN, LoaderWrap([]() { return new MainScreen(); }) }
};



int main() {
    App::CreateWindows(1);
    App::SetScreenLoaders(&screenLoaders);

    // NEEDS TO BE REFACTORED -- indicies vs Screen Enums. Might be redundant 
    WindowManager* simulation = App::GetWindowManager(0);

    simulation->init();
    simulation->center();

    App::SetScreen(0, Screens::MAIN_SCREEN, true);
    App::Activate(0);
    // ^ BLOCKING FUNCTION

    // std::thread t1(&WindowManager::run, colorPicker);
    // t1.join();
}
