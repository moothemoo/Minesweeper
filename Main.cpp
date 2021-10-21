#include <iostream>
#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"VBO.h"
#include"VAO.h"
#include"EBO.h"
#include"Shader.h"
#include"Texture.h"
#include"Camera2D.h"
#include"ResourceManager.h"
#include"Window.h"
#include"Renderer.h"
#include"TileRenderer.h"
#include"Map.h"
#include"Tile.h"

// Prototype for input
void processInput(GLFWwindow* window, float dt);

void initGlfw();

const unsigned int width = 800;
const unsigned int height = 800;

float speed = 2.0f;

bool regenProj = false;

glm::vec2 position = glm::vec2(0.0f, 0.0f);

int main()
{
    // Initializes glfw
    initGlfw();
    
    // New window object, width 800, height 600, Titled LearnOpenGL, last two parameters irrelevant
    Window window = Window(width, height, "Window", NULL, NULL);

    // Initialize GLAD and returns error if fails
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Triangle corners
    GLfloat vertices[] =
    {// Vertex Positions     /  Tex Pos                           / Vertex
        -0.5f, -0.5f,           0.0f, 0.0f,         //0
        -0.5f, 0.5f,            0.0f, 1.0f,         //1
        0.5f, 0.5f,             1.0f, 1.0f,         //2
        0.5f, -0.5f,            1.0f, 0.0f          //3
    };

    // Indices of 3 triangles
    GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3
    };

    // Opens window, x,y of lower left corner of window, width, height of window
    glViewport(0, 0, width, height);

    //Initializes shaders
    Shader shader = ResourceManager::LoadShader("2DRenderer.vert", "2DRenderer.frag", nullptr, "test");
    Shader tShader = ResourceManager::LoadShader("TileRenderer.vert", "TileRenderer.frag", nullptr, "tile");

    //Sets up vertex and element objects
    SpriteRenderer renderer(shader, vertices, sizeof(vertices), indices, sizeof(indices));

    // Specify color 
    // Clean back buffer and assign new color to it
    // Swap the back buffer and front buffer
    window.setBackgroundColor(1.0f, 1.0f, 1.0f, 1.0f);
    window.clearScreen();
    window.newFrame();

    Texture2D sSheetTex = ResourceManager::LoadTexture("MinesweeperSpriteSheet.png", true, "S");

    SpriteSheet sSheet = SpriteSheet(4, 4, sSheetTex);

    Camera2D camera(4.0f, 4.0f, glm::vec2(0.0f, 0.0f));
    //glm::mat4 view = glm::mat4(1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float prevFrame = 0;
    float deltaTime = 0;
    //unsigned int frameRate = 240;
    //float frameTime = 1000 / frameRate;
    // Render Loop
    prevFrame = glfwGetTime();
    float time;

    Map map("Hex", sSheet, tShader, 0.5f, 0.5f);

    while (!glfwWindowShouldClose(window.window))
    {
        time = glfwGetTime();
        deltaTime = time - prevFrame;
        prevFrame = time;

        //std::cout << 1 / deltaTime << std::endl;

        // input
        processInput(window.window, deltaTime);

        if (regenProj)
        {
            camera.SetPosition(position, regenProj);
            regenProj = false;
        }

        // Redraws Background, starts shader, sets VAO1 to active vertex array object, and draws
        camera.SetPosition(position);
        window.clearScreen();

        camera.Matrix(tShader, "camera");

        map.drawMap();

        camera.Matrix(shader, "camera");

        // Swaps back buffer and front buffer
        window.newFrame();
        // Checks for keyboard or mouse events
        glfwPollEvents();
        //Sleep((long)(frameTime - deltaTime));
    }

    // Cleaning
    shader.Delete();
    tShader.Delete();

    // Delete window
    window.terminateWindow();
    // Cleans evertthing up
    glfwTerminate();
	return 0;
}

//Take inputs
void processInput(GLFWwindow* window, float dt)
{
    // Sets event handler for esc key
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position[1] += speed * dt;
        regenProj = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position[0] -= speed * dt;
        regenProj = true;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position[1] -= speed * dt;
        regenProj = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        position[0] += speed * dt;
        regenProj = true;
    }
}

void initGlfw()
{
    // Initialize GLFW
    glfwInit();

    // Ver 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}