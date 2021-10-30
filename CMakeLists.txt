cmake_minimum_required(VERSION 3.14)
project(AngryBirdsSFML)

set(CMAKE_CXX_STANDARD 14)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()


find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
set(SOURCE_FILES src/main.cpp src/Engine.cpp src/Engine.h src/EngineComponents.cpp src/EngineComponents.h src/EngineMethods.cpp src/EngineMethods.h src/Game/MainMenuScene.cpp src/Game/MainMenuScene.h src/Game/LevelSelectScene.cpp src/Game/LevelSelectScene.h src/Game/GameObjects/MusicManager.cpp src/Game/GameObjects/MusicManager.h src/Game/Levels/Level1.cpp src/Game/Levels/Level1.h src/Game/Levels/Level2.cpp src/Game/Levels/Level2.h src/Game/Levels/Level3.cpp src/Game/Levels/Level3.h src/Game/GameObjects/Slingshot.cpp src/Game/GameObjects/Slingshot.h src/Game/GameObjects/Bird.cpp src/Game/GameObjects/Bird.h src/Game/Levels/LevelBase.cpp src/Game/Levels/LevelBase.h src/Game/GameObjects/Pig.cpp src/Game/GameObjects/Pig.h src/Game/GameObjects/Block.cpp src/Game/GameObjects/Block.h src/Game/GameObjects/Poof.cpp src/Game/GameObjects/Poof.h)
add_executable(AngryBirdsSFML ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (AngryBirdsSFML sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)