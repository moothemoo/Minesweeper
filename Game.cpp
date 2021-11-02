#include"Game.h"


Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), 
    Keys(),
    camera(),
    map(),
    width(width), height(height)
{

}

Game::~Game()
{
    
}

void Game::Init()
{
    ResourceManager::LoadShader("2DRenderer.vert", "2DRenderer.frag", nullptr, "shader");
    ResourceManager::LoadShader("TileRenderer.vert", "TileRenderer.frag", nullptr, "tShader");

    ResourceManager::LoadTexture("Bing.png", true, "Doggo");
    ResourceManager::LoadTexture("MinesweeperSpriteSheet.png", true, "MinesweeperSpriteSheet");

    ResourceManager::LoadSpriteSheet("MinesweeperSpriteSheet", 4, 4, "MineSheet");

    camera = Camera2D(4.0f, 4.0f, glm::vec2(0.0f, 0.0f));

    map = Map(255, 255, 9, ResourceManager::GetSpriteSheet("MineSheet"), ResourceManager::GetShader("tShader"));

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
    camera.RegenProj();

    if (firstClick && (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS))
    {
        firstClick = false;
        double mouseX, mouseY;
        glm::vec2 cameraPos = camera.GetPosition();
        glm::vec2 fov = camera.GetDimensions();
        glfwGetCursorPos(window, &mouseX, &mouseY);
       
        mouseX = mouseX / width * fov[0] - fov[0] / 2 + cameraPos[0];
        mouseY = -mouseY / height * fov[1] + fov[1] / 2 + cameraPos[1];

        map.click(mouseX, mouseY);
    }
    else if (!firstClick && (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE))
    {
        firstClick = true;
    }
}

void Game::Render()
{
    map.Render(camera.GetProjection());
}