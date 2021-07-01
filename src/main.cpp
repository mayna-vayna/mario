#include<iostream>
#include<glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

//Global var for size Window

int g_WindowSizeX = 640;
int g_WindowSizeY = 480;

//window size callback
void glWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {

    g_WindowSizeX = width;
    g_WindowSizeY = height;

    glViewport(0, 0, g_WindowSizeX, g_WindowSizeY);

}

void glfwKeyCallback(GLFWwindow* pWindow,int key, int scancode,int action,int mode) {

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }

}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit()) {

        cout << "glfwInit failed" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_WindowSizeX, g_WindowSizeY, "Mario", nullptr, nullptr);
    if (!pWindow)
    {

        cout << "glfwInit failed"<<endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL()) {
        cout << "Can load Glad" << endl;
        return -1;
    }

    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL version: " << glGetString(GL_VERSION);

    glClearColor(1, 1, 0, 1);
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
       glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}