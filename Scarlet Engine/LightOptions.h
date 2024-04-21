#ifndef __LightOptions
#define __LightOptions

#include "RenderOptions.h"
#include "Material.h"
#include "Skybox.h"

class LightOptions
{
private:
	Material* skybox_mat;
	Skybox* skybox;


public:
	void Set_Skybox_Material(Material* mat)
	{
		skybox_mat = mat;
	}

	void Create_Skybox()
	{
		skybox = new Skybox();
	}

	void Draw_Skybox()
	{
		skybox->Draw();
	}

	void Update_Skybox()
	{

	}

	~LightOptions()
	{
		delete skybox_mat;
		delete skybox;
	}
};

#endif