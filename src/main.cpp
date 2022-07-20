/**
 * @file main.cpp
 * @author MoriokaReimen
 * @brief VLC + GLFW + OpenGL + Imgui sample
 * @version 0.1
 * @date 2022-07-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <glad/glad.h>

#ifdef WIN32
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#else
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#endif
#include <cstdio>
#include <GLFW/glfw3.h>

#include "vlc_texture.hpp"


/**
 * @brief Error Handler for GLFW window
 * 
 * @param error      error id
 * @param description  error description
 */
static void glfw_error_callback(int error, const char* description)
{
    std::fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

/**
 * @brief main function
 * 
 * @return return code(Always 0) 
 */
int main(int, char**)
{
    /* Setup window */
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;


    /* GL 3.0 + GLSL 130 */
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create window with graphics context */
    GLFWwindow* window = glfwCreateWindow(1280, 720, "VLC Captured data", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

#ifdef WIN32
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::fprintf(stderr, "Failed to initialize OpenGL context\n");
        return -1;
    }
#endif
    /* Setup Dear ImGui context */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    /* Setup Dear ImGui style */
    ImGui::StyleColorsDark();

    /* Setup Platform/Renderer backends */
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    /* Widow Clear Color */
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

    /* Create VLC Texture Object */
#ifdef WIN32
    VLC_Texture vlc("dshow://");
#else
    VLC_Texture vlc("v4l2:///dev/video0");
#endif

    /* Main Loop */
    while (!glfwWindowShouldClose(window))
    {
        /* Handle event */
        glfwPollEvents();

        /* Start the Dear ImGui frame */
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /* Reder Captured Video */
        ImGui::Begin("Captured Data", NULL, ImGuiWindowFlags_NoScrollbar);
        vlc.update();
        auto tex_id = vlc.get_texture_id();
        auto tex_size = ImGui::GetContentRegionMax();
        ImGui::Image((void*)(intptr_t)tex_id, tex_size);
        ImGui::End();

        /* Rendering */
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    /* Cleanup Imgui*/
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    /* Close window */
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}