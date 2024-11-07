set(LIB_NAME SF-Core)

add_library (
    ${LIB_NAME} 
    STATIC
    Animation.cpp
    BaseScreen.cpp
    Helpers.cpp
    Image.cpp
    OriginFunc.cpp
    RoundedRectangle.cpp
    WindowManager.cpp
    App.cpp
)

target_compile_definitions(${LIB_NAME} PUBLIC SFML_STATIC TGUI_STATIC)
target_precompile_headers(${LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/SF-Core/Pch.hpp)
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/SFML-TGUI/include)