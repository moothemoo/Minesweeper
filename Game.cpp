#include"Game.h"


Game::Game()
    : State(GAME_ACTIVE), 
    Keys(),
    mPosX(), mPosY(),
    camera(),
    map()
{

}

Game::Game(Map& map, Camera2D& camera)
    : State(GAME_ACTIVE),
    Keys(),
    mPosX(), mPosY(),
    camera(camera),
    map(map)
{

}

Game::~Game()
{

}

void Game::Init()
{
    Shader shader = ResourceManager::LoadShader("2DRenderer.vert", "2DRenderer.frag", nullptr, "test");
    Shader tShader = ResourceManager::LoadShader("TileRenderer.vert", "TileRenderer.frag", nullptr, "tile");

    SpriteSheet s = SpriteSheet();
    map = Map(s);
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(GLFWwindow* window, float dt)
{
    glm::vec2 position = glm::vec2(0.0f, 0.0f);

    // Sets event handler for esc key
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position[0] += speed * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position[0] -= speed * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position[1] -= speed * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        position[0] += speed * dt;
    }

    camera.Move(position);

    if (firstClick && (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS))
    {
        firstClick = false;
    }
    else if (!firstClick && (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE))
    {
        firstClick = true;
    }
}

void Game::Render()
{

}