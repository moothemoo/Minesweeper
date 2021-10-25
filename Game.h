#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Map.h"
#include "Camera2D.h"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    GameState               State;
    bool                    Keys[1024];
    Map                     map;
    Camera2D                camera;

    float fovWidth, fovHeight;
    float mPosX, mPosY;
    float speed;
    bool firstClick = true;


    // constructor/destructor
    Game();
    Game(Map& map, Camera2D& camera);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(GLFWwindow* window, float dt);
    void Update(float dt);
    void Render();
};

#endif