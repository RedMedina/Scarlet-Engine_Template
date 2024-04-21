#ifndef __Scene_Manager
#define __Scene_Manager


#include <vector>
#include "Scene.h"
#include "Scene_Hierarchy.h"

class Scene_Manager
{
private:
	Scene_Hierarchy* Hierarchy;
	Scene* Active_Scene;

public:
	std::vector<Scene*> Scenes;

	Scene_Manager()
	{
		Hierarchy = new Scene_Hierarchy;
		Scenes.assign(Hierarchy->Scenes.begin(), Hierarchy->Scenes.end());
		Active_Scene = Scenes[0];
		//Active_Scene->Start();
	}

	Scene* GetActiveScene()
	{
		return Active_Scene;
	}

	void ChangeScene(int index_scene)
	{
		Active_Scene = Scenes[index_scene];
		Active_Scene->Start();
	}

	~Scene_Manager()
	{
		delete Hierarchy;
		delete Active_Scene;
		Scenes.clear();
	}
};

#endif