#include"Game.h"


Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), 
    Keys(),
    camera(),
    map(),
    width(width), height(height)
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

void Game::Init()
{

    ResourceManager::LoadTexture("Bing.png", true, "Doggo");
    ResourceManager::LoadTexture("MinesweeperSpriteSheet.png", true, "MinesweeperSpriteSheet");

void Game::Init()
{
    Shader shader = ResourceManager::LoadShader("2DRenderer.vert", "2DRenderer.frag", nullptr, "test");
    Shader tShader = ResourceManager::LoadShader("TileRenderer.vert", "TileRenderer.frag", nullptr, "tile");

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
        position[1] += speed * dt;
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

    if (prevInput == -1 && (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS))
    {
        if (!firstClick)
        {
            prevInput = GLFW_MOUSE_BUTTON_RIGHT;
            double mouseX, mouseY;
            glm::vec2 cameraPos = camera.GetPosition();
            glm::vec2 fov = camera.GetDimensions();
            glfwGetCursorPos(window, &mouseX, &mouseY);

            int width, height;
            glfwGetWindowSize(window, &width, &height);

            mouseX = mouseX / width * fov[0] - fov[0] / 2 + cameraPos[0];
            mouseY = -mouseY / height * fov[1] + fov[1] / 2 + cameraPos[1];

            map.flag(mouseX, mouseY);
        }
    }
    else if (prevInput == GLFW_MOUSE_BUTTON_RIGHT && (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE))
    {
        prevInput = -1;
    }
}

void Game::Render()
{

}