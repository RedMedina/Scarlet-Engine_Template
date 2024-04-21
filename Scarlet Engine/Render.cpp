#include "Render.h"


Render::Render(int w_Screen, int h_Screen, const char* Name_Screen, int WindowPosX, int WindowPosY)
{
	wScreen = w_Screen;
	hScreen = h_Screen;

	MainSettings::w_window = w_Screen;
	MainSettings::h_window = h_Screen;

	//Setup Scene
	if (!glfwInit())
	{
		cout << "Error inicializando GLFW" << endl;
		exit(0);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //MacOS
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(wScreen, hScreen, Name_Screen, NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(0);
	}

	//Inicializar FMOD
	FMOD::System_Create(&system);
	system->init(512, FMOD_INIT_NORMAL, nullptr);


	glfwSetWindowPos(window, WindowPosX, WindowPosY);
	// Set Window in context
	glfwMakeContextCurrent(window);
	
	glewExperimental = true;

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		exit(0);
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	//glfwSetKeyCallback(window, key_callback);
	Input::window = window;
	Input::Screen_lastX = wScreen / 2.0f;
	Input::Screen_lastY = hScreen / 2.0f;
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwPollEvents();
	//glfwSetCursorPos(window, wScreen / 2, hScreen / 2);
	
	//Set Engine State
	Debug::SetDebugMode(true);

	//ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	//ImGui Style
	ImGui::StyleColorsDark();
}


void Render::Update(Scene* RenderScene)
{
	glfwGetCursorPos(window, &Input::Mouse_PosX, &Input::Mouse_PosY);
	
	RenderScene->Update();
	system->update();

	if(Input::GetKeyDown(InputKey::Escape))
	{
		glfwTerminate();
	}
}

void Render::Draw(Scene* RenderScene)
{
	float currentFrame = static_cast<float>(glfwGetTime());
	Time::deltatime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	RenderScene->Draw(Time::deltatime);

	float fps = 1.0f / Time::deltatime;
	FPS = "FPS: " + to_string(fps);
	Coord = "Coordenadas: x= " + to_string(CameraMatrix::CameraPosition->x)
		+ " y= " + to_string(CameraMatrix::CameraPosition->y)
		+ " z= " + to_string(CameraMatrix::CameraPosition->z);

	ImGui::Begin("Scarlet Engine: OpenGL Template");
	if(MainSettings::render_ui)
	{
		ImGui::Text(FPS.c_str());
		ImGui::Text(Coord.c_str());
	}
	ImGui::End();
}

Render::~Render()
{
	delete window;
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	system->close();
	system->release();
}