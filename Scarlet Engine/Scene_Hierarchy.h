#ifndef __Scene_Hierarchy
#define __Scene_Hierarchy

#include "Camera.h"
#include "Material.h"
#include "Scene.h"
#include "Point_Light.h"
#include "MeshRenderer.h"
#include "Directional_Light.h"
#include "BoxCollider.h"
#include "AudioSource.h"
#include "TextUI.h"
#include "Billboard.h"
#include "Terrain.h"
#include "LOD.h"
#include "AnimatedModel.h"

class Scene_Hierarchy
{
public:
	std::vector<Scene*> Scenes;
	Scene_Hierarchy()
	{
		//Aqui se carga todo con su herarquía
		DefaultScene = new Scene;
		Scenes.push_back(DefaultScene);
		Scenes[0]->Start();

		//Creación de Camara
		GameObject* CameraGameObj = new GameObject("Camara Princiapal");
		CameraGameObj->components.push_back(new Camera(&dynamic_cast<Transform*>(CameraGameObj->components[0])->Position, glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, glm::vec3(0.0f, 0.0f, -1.0f), 10.5f, 0.1f, 45.0f, 4.0f / 3.0f,0.1f, 2000.0f, true));
		Scenes[0]->GameObjects.push_back(CameraGameObj);

		//Directional Light
		GameObject* DirLight = new GameObject("Luz Direccional"); //-2.0f, 4.0f, -1.0f
		dynamic_cast<Transform*>(DirLight->components[0])->Rotation = glm::vec3(-15.0f, 40.0f, -25.0f);
		DirLight->components.push_back(new Directional_Light(&dynamic_cast<Transform*>(DirLight->components[0])->Rotation, new glm::vec3(0.7f, 0.7f, 0.7f), new glm::vec3(0.8f, 0.8f, 0.8f), new glm::vec3(0.6f, 0.6f, 0.6f), true));
		Scenes[0]->GameObjects.push_back(DirLight);

		//Point Light
		GameObject* PointLight = new GameObject("Punto de Luz 1");
		dynamic_cast<Transform*>(PointLight->components[0])->Position = glm::vec3(0.0f, 3.0f, 0.0f);
		PointLight->components.push_back(new Point_Light(&dynamic_cast<Transform*>(PointLight->components[0])->Position, new glm::vec3(0.0f, 0.7098f, 1.0f), new glm::vec3(0.0f, 0.7098f, 1.0f), new glm::vec3(0.0f, 0.7098f, 1.0f), 1.0f, 0.09f, 0.032f, false));
		Scenes[0]->GameObjects.push_back(PointLight);

		//Primer modelo_3d
		GameObject* ModeloArbol = new GameObject("Modelo Arbol 1");

		Material* ArbolMaterial = new Material("model.vs", "model.ps");
		ArbolMaterial->Material_Settings->Transparent = true;
		ArbolMaterial->SetTexture2D("basecolor", "Assets/Models/Arbol/ArbolTextura.jpg");
		ArbolMaterial->SetTexture2D("normalmap", "Assets/Models/Arbol/ArbolN.png");
		
		ModeloArbol->components.push_back(new MeshRenderer("Assets/Models/Arbol/Arbol.obj", &dynamic_cast<Transform*>(ModeloArbol->components[0])->Position, &dynamic_cast<Transform*>(ModeloArbol->components[0])->Rotation, &dynamic_cast<Transform*>(ModeloArbol->components[0])->Scale));
		dynamic_cast<MeshRenderer*>(ModeloArbol->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<MeshRenderer*>(ModeloArbol->components[1])->SetMaterial(ArbolMaterial);
		dynamic_cast<MeshRenderer*>(ModeloArbol->components[1])->HDRColor = true;
		ModeloArbol->components.push_back(new BoxCollider(&dynamic_cast<Transform*>(ModeloArbol->components[0])->Position, &dynamic_cast<Transform*>(ModeloArbol->components[0])->Rotation, &dynamic_cast<Transform*>(ModeloArbol->components[0])->Scale));
		Scenes[0]->GameObjects.push_back(ModeloArbol);
		
		//Modelo plane
		GameObject* PlanoObj = new GameObject("Plane");

		Material* PlaneMat = new Material("model.vs", "model.ps");
		PlaneMat->Material_Settings->Transparent = true;
		PlaneMat->SetTexture2D("basecolor", "Assets/Models/Plane/GroundBasecolor.jpg");
		PlaneMat->SetTexture2D("normalmap", "Assets/Models/Plane/GroundNormal.jpg");

		PlanoObj->components.push_back(new MeshRenderer("Assets/Models/Plane/plane.obj", &dynamic_cast<Transform*>(PlanoObj->components[0])->Position, &dynamic_cast<Transform*>(PlanoObj->components[0])->Rotation, &dynamic_cast<Transform*>(PlanoObj->components[0])->Scale));
		dynamic_cast<MeshRenderer*>(PlanoObj->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<MeshRenderer*>(PlanoObj->components[1])->SetMaterial(PlaneMat);
		Scenes[0]->GameObjects.push_back(PlanoObj);

		//AudioSource
		GameObject* AudioSource1 = new GameObject("AudioBGM1");
		AudioSource1->components.push_back(new AudioSource("Assets/Music/BackgroundBirds.mp3", glm::vec3(0.0f, 0.0f, 0.0f), true));
		dynamic_cast<AudioSource*>(AudioSource1->components[1])->SetLoop();
		dynamic_cast<AudioSource*>(AudioSource1->components[1])->play();
		Scenes[0]->GameObjects.push_back(AudioSource1);

		//Creacion de LODS
		Material* SphereLODMat = new Material("model.vs", "model.ps");
		SphereLODMat->SetTexture2D("basecolor", "Assets/Terrain/mon.png");
		SphereLODMat->SetTexture2D("normalmap", "Assets/Terrain/monN.png");

		//Sphere HQ
		GameObject* Sphere_HighQ = new GameObject("Sphere_LOD");
		Sphere_HighQ->components.push_back(new MeshRenderer("Assets/Models/LOD_Sohere/Sphere_1.obj", &dynamic_cast<Transform*>(Sphere_HighQ->components[0])->Position, &dynamic_cast<Transform*>(Sphere_HighQ->components[0])->Rotation, &dynamic_cast<Transform*>(Sphere_HighQ->components[0])->Scale));
		dynamic_cast<MeshRenderer*>(Sphere_HighQ->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<MeshRenderer*>(Sphere_HighQ->components[1])->SetMaterial(SphereLODMat);
		
		//Sphere MQ
		GameObject* Sphere_MediumQ = new GameObject("Sphere_LOD");
		Sphere_MediumQ->components.push_back(new MeshRenderer("Assets/Models/LOD_Sohere/Sphere_3.obj", &dynamic_cast<Transform*>(Sphere_MediumQ->components[0])->Position, &dynamic_cast<Transform*>(Sphere_MediumQ->components[0])->Rotation, &dynamic_cast<Transform*>(Sphere_MediumQ->components[0])->Scale));
		dynamic_cast<MeshRenderer*>(Sphere_MediumQ->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<MeshRenderer*>(Sphere_MediumQ->components[1])->SetMaterial(SphereLODMat);

		//Sphere LQ
		GameObject* Sphere_LowQ = new GameObject("Sphere_LOD");
		Sphere_LowQ->components.push_back(new MeshRenderer("Assets/Models/LOD_Sohere/Sphere_4.obj", &dynamic_cast<Transform*>(Sphere_LowQ->components[0])->Position, &dynamic_cast<Transform*>(Sphere_LowQ->components[0])->Rotation, &dynamic_cast<Transform*>(Sphere_LowQ->components[0])->Scale));
		dynamic_cast<MeshRenderer*>(Sphere_LowQ->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<MeshRenderer*>(Sphere_LowQ->components[1])->SetMaterial(SphereLODMat);

		//Sphere Bill
		/*
		Material* BillSpherem = new Material("billboard.vs", "billboard.ps");
		BillSpherem->SetTexture2D("basecolor", "Assets/Models/LOD_Sohere/Sphere_bill.png");
		GameObject* BillSphere = new GameObject("Sphere_LOD");
		dynamic_cast<Transform*>(BillSphere->components[0])->Scale = glm::vec3(15.0f, 15.0f, 0.0f);
		BillSphere->components.push_back(new Billboard(&dynamic_cast<Transform*>(BillSphere->components[0])->Position, &dynamic_cast<Transform*>(BillSphere->components[0])->Scale));
		dynamic_cast<Billboard*>(BillSphere->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<Billboard*>(BillSphere->components[1])->SetMaterial(BillSpherem);
		*/

		//Spheres LOD
		GameObject* LOD_Spheres = new GameObject("Sphere_LOD1");
		dynamic_cast<Transform*>(LOD_Spheres->components[0])->Position = glm::vec3(0.0f, 10.0f, 0.0f);
		LOD_Spheres->components.push_back(new LOD(&dynamic_cast<Transform*>(LOD_Spheres->components[0])->Position, &dynamic_cast<Transform*>(LOD_Spheres->components[0])->Rotation, &dynamic_cast<Transform*>(LOD_Spheres->components[0])->Scale));
		LOD::LodItem S_HQ;
		S_HQ.objLod = Sphere_HighQ;
		S_HQ.MAX_RENDER_distance = 25.0f;
		LOD::LodItem S_MQ;
		S_MQ.objLod = Sphere_MediumQ;
		S_MQ.MAX_RENDER_distance = 50.0f;
		LOD::LodItem S_LQ;
		S_LQ.objLod = Sphere_LowQ;
		S_LQ.MAX_RENDER_distance = 90.0f;
		//LOD::LodItem S_Bill;
		//S_LQ.objLod = BillSphere;
		//S_LQ.MAX_RENDER_distance = 70.0f;
		dynamic_cast<LOD*>(LOD_Spheres->components[1])->LOD_Levels.push_back(S_HQ);
		dynamic_cast<LOD*>(LOD_Spheres->components[1])->LOD_Levels.push_back(S_MQ);
		dynamic_cast<LOD*>(LOD_Spheres->components[1])->LOD_Levels.push_back(S_LQ);
		//dynamic_cast<LOD*>(LOD_Spheres->components[1])->LOD_Levels.push_back(S_Bill);
		Scenes[0]->GameObjects.push_back(LOD_Spheres);

		//Terrain Material
		Material* TerrainMat = new Material("terrain.vs", "terrain.ps");
		TerrainMat->SetTexture2D("basecolor1", "Assets/Terrain/mon.png");
		TerrainMat->SetTexture2D("basecolor2", "Assets/Terrain/octostoneAlbedo.png");
		TerrainMat->SetTexture2D("basecolor3", "Assets/Terrain/grass.png");
		TerrainMat->SetTexture2D("normalmap1", "Assets/Terrain/monN.png");
		TerrainMat->SetTexture2D("normalmap2", "Assets/Terrain/octostoneNormalc.png");
		TerrainMat->SetTexture2D("normalmap3", "Assets/Terrain/grassN.png");
		TerrainMat->SetTexture2D("blendmap", "Assets/Terrain/Blend1.png");
		TerrainMat->Material_Settings->Cull_Front = true;

		//Terrain
		GameObject* TerrainObj = new GameObject("Terreno Principal");
		TerrainObj->components.push_back(new Terrain("Assets/Terrain/heigh.png"));
		dynamic_cast<Terrain*>(TerrainObj->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<Terrain*>(TerrainObj->components[1])->SetMaterial(TerrainMat);
		Scenes[0]->GameObjects.push_back(TerrainObj);

		/*Animated Model*/
		//Material
		Material* Animated_Model_Material = new Material("anim_model.vs", "anim_model.ps");
		//Animated_Model_Material->Material_Settings->Transparent
		std::vector<Animation*> animations1;
		GameObject* Animated_Model = new GameObject("Modelo Animado");
		dynamic_cast<Transform*>(Animated_Model->components[0])->Position = glm::vec3(0.0f, 9.0f, 0.0f);
		dynamic_cast<Transform*>(Animated_Model->components[0])->Scale = glm::vec3(0.06f, 0.06f, 0.06f);
		Animated_Model->components.push_back(new AnimatedModel("Assets/Models/Animated_1/Player_Base2.fbx", Animated_Model_Material, &dynamic_cast<Transform*>(Animated_Model->components[0])->Position, &dynamic_cast<Transform*>(Animated_Model->components[0])->Rotation, &dynamic_cast<Transform*>(Animated_Model->components[0])->Scale));
		Animation* anim1 = new Animation("Assets/Models/Animated_1/Run_Final.fbx", dynamic_cast<AnimatedModel*>(Animated_Model->components[1])->model);
		animations1.push_back(anim1);
		dynamic_cast<AnimatedModel*>(Animated_Model->components[1])->animations = animations1;
		dynamic_cast<AnimatedModel*>(Animated_Model->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<AnimatedModel*>(Animated_Model->components[1])->SetupAnimator();
		Scenes[0]->GameObjects.push_back(Animated_Model);

		//Texto Fuente Crayola
		Material* TextoMat = new Material("text.vs", "text.ps");
		TextoMat->Material_Settings->Transparent = true;
		GameObject* TextUIBase = new GameObject("Texto UI 1");
		dynamic_cast<Transform*>(TextUIBase->components[0])->Position = glm::vec3(500.0f, 800.0f, 1.0f);
		dynamic_cast<Transform*>(TextUIBase->components[0])->Scale = glm::vec3(1.0f, 1.0f, 1.0f);
		TextUIBase->components.push_back(new TextUI("Assets/Fonts/CrayonLibre.ttf", &dynamic_cast<Transform*>(TextUIBase->components[0])->Position, new glm::vec3(1.0f, 0.0f, 0.0f), "Text de prueba", & dynamic_cast<Transform*>(TextUIBase->components[0])->Scale));
		dynamic_cast<TextUI*>(TextUIBase->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<TextUI*>(TextUIBase->components[1])->SetMaterial(TextoMat);
		Scenes[0]->GameObjects.push_back(TextUIBase);

		//Texto Fuente KomiAxis
		GameObject* TextUIBase_2 = new GameObject("Texto UI 2");
		dynamic_cast<Transform*>(TextUIBase_2->components[0])->Position = glm::vec3(800.0f, 30.0f, 1.0f);
		dynamic_cast<Transform*>(TextUIBase_2->components[0])->Scale = glm::vec3(0.5f, 0.5f, 0.5f);
		TextUIBase_2->components.push_back(new TextUI("Assets/Fonts/KOMIKAX_.ttf", &dynamic_cast<Transform*>(TextUIBase_2->components[0])->Position, new glm::vec3(0.7f, 0.2f, 0.5f), "Holiii :)", &dynamic_cast<Transform*>(TextUIBase_2->components[0])->Scale));
		dynamic_cast<TextUI*>(TextUIBase_2->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<TextUI*>(TextUIBase_2->components[1])->SetMaterial(TextoMat);
		Scenes[0]->GameObjects.push_back(TextUIBase_2);

		//Material Billboard 1
		Material* Bill1Mat = new Material("billboard.vs", "billboard.ps");
		Bill1Mat->Material_Settings->Transparent = true;
		Bill1Mat->SetTexture2D("basecolor", "Assets/Billboard/Arbol.png");

		//Billboard 1
		GameObject* Billboard1 = new GameObject("Billboard 1");
		dynamic_cast<Transform*>(Billboard1->components[0])->Position = glm::vec3(-11.0f, -8.0f, 0.0f);
		dynamic_cast<Transform*>(Billboard1->components[0])->Scale = glm::vec3(15.0f, 15.0f, 0.0f);
		Billboard1->components.push_back(new Billboard( &dynamic_cast<Transform*>(Billboard1->components[0])->Position, &dynamic_cast<Transform*>(Billboard1->components[0])->Scale ));
		dynamic_cast<Billboard*>(Billboard1->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<Billboard*>(Billboard1->components[1])->SetMaterial(Bill1Mat);
		Scenes[0]->GameObjects.push_back(Billboard1);

		//Test Reflejo 1
		/*
		GameObject* ReflexGameObj = new GameObject("Test Reflejo 1");
		dynamic_cast<Transform*>(ReflexGameObj->components[0])->Position = glm::vec3(30.0f, 0.0f, 0.0f);
		Material* ReflexMat = new Material("model.vs", "model.ps");
		Material::Texture tex;
		//tex.IdTexture = *MainLightData::POSTMAP;
		tex.IdTexture = *MainLightData::POSTMAP_1;
		tex.Name = "basecolor";
		ReflexMat->Textures.push_back(tex);
		ReflexMat->SetTexture2D("normalmap", "Assets/Models/Plane/GroundNormal.jpg");

		ReflexGameObj->components.push_back(new MeshRenderer("Assets/Models/Plane/plane.obj", &dynamic_cast<Transform*>(ReflexGameObj->components[0])->Position, &dynamic_cast<Transform*>(ReflexGameObj->components[0])->Rotation, &dynamic_cast<Transform*>(ReflexGameObj->components[0])->Scale));
		dynamic_cast<MeshRenderer*>(ReflexGameObj->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<MeshRenderer*>(ReflexGameObj->components[1])->SetMaterial(ReflexMat);
		Scenes[0]->GameObjects.push_back(ReflexGameObj);
		*/

	}

	
	~Scene_Hierarchy()
	{
		delete DefaultScene;
		for (Scene* scn : Scenes) {
			delete scn;
		}

		Scenes.clear();
	}

private:
	//Todas las Escenas
	Scene* DefaultScene;
};

#endif