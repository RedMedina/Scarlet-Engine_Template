#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include "Render.h"
#include "Scene.h"
#include "Scene_Manager.h"
#include "Post_processing.h"
#include "MainSettings.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

using namespace std;

int main()
{
	Render* Game_Engine = new Render(1300, 950, "Scarlet Template", 300, 50);
	Post_processing* pos = new Post_processing;
	Scene_Manager* Scene_Control = new Scene_Manager;
	
	while(true)
	{
		// Iniciar el frame de ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		Game_Engine->Draw(Scene_Control->GetActiveScene());
		pos->SetRender(Game_Engine, Scene_Control);
		MainSettings::render_ui = false;
		Game_Engine->Update(Scene_Control->GetActiveScene());
		MainSettings::render_ui = true;
		MainSettings::RenderN = 0;

		// Renderizar ImGui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(Input::window);
		glfwPollEvents();
	}

	delete Scene_Control;
	delete Game_Engine;

	return 0;
}