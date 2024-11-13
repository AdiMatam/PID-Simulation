set(PROJECT_NOM PID-Simulation)
add_executable(
    ${PROJECT_NOM}
    Main.cpp
    MainScreen.cpp
    LabeledEditBox.cpp
    MagModel.cpp
)

target_compile_definitions(${PROJECT_NOM} PUBLIC SFML_STATIC TGUI_STATIC)
target_include_directories(
    ${PROJECT_NOM} PUBLIC 
    ${CMAKE_SOURCE_DIR}/SFML-TGUI/include
    ${CMAKE_SOURCE_DIR}
)
target_link_directories(${PROJECT_NOM} PUBLIC ${CMAKE_SOURCE_DIR}/SFML-TGUI/lib)
target_link_libraries(
    ${PROJECT_NOM} PUBLIC
    SF-Core 
)

target_link_libraries(
    ${PROJECT_NOM} PUBLIC
    tgui-s
    sfml-graphics-s
    sfml-window-s
    sfml-system-s
    freetype
    ogg
    opengl32
    gdi32
    winmm
)
