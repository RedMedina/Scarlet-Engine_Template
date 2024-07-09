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
#include "WaterEffect.h"
#include "PlayerController.h"

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
		CameraGameObj->components.push_back(new Camera(&dynamic_cast<Transform*>(CameraGameObj->components[0])->Position, glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, glm::vec3(0.0f, 0.0f, -1.0f), 10.5f, 0.1f, 45.0f, MainSettings::w_window / MainSettings::h_window, 0.1f, 2000.0f, true));
		Scenes[0]->GameObjects.push_back(CameraGameObj);

		//Directional Light
		GameObject* DirLight = new GameObject("Luz Direccional"); //-2.0f, 4.0f, -1.0f   40f
		dynamic_cast<Transform*>(DirLight->components[0])->Rotation = glm::vec3(-5.0f, 70.0f, -90.0f); //-15.0f, 120.0f, -315.0f
		DirLight->components.push_back(new Directional_Light(&dynamic_cast<Transform*>(DirLight->components[0])->Rotation, new glm::vec3(0, 0, 0), new glm::vec3(0.278, 0.278, 0.278), new glm::vec3(0.1588f, 0.1667f, 0.2235f), true));
		Scenes[0]->GameObjects.push_back(DirLight);

		//Point Light Farola 1
		GameObject* PointLight2 = new GameObject("Punto de Luz 2");
		dynamic_cast<Transform*>(PointLight2->components[0])->Position = glm::vec3(-10.0f, 2.0f, 30.0f);
		PointLight2->components.push_back(new Point_Light(&dynamic_cast<Transform*>(PointLight2->components[0])->Position, new glm::vec3(0.9f, 0.9f, 0.5f), new glm::vec3(0.9f, 0.9f, 0.5f), new glm::vec3(0.9f, 0.9f, 0.5f), 0.627f, 0.0f, 0.005f, false));
		dynamic_cast<Point_Light*>(PointLight2->components[1])->UINum = 1;
		Scenes[0]->GameObjects.push_back(PointLight2);

		//Point Light Farola 2
		GameObject* PointLight3 = new GameObject("Punto de Luz 3");
		dynamic_cast<Transform*>(PointLight3->components[0])->Position = glm::vec3(-10.0f, 2.0f, -30.0f);
		PointLight3->components.push_back(new Point_Light(&dynamic_cast<Transform*>(PointLight3->components[0])->Position, new glm::vec3(0.9f, 0.9f, 0.5f), new glm::vec3(0.9f, 0.9f, 0.5f), new glm::vec3(0.9f, 0.9f, 0.5f), 0.627f, 0.0f, 0.005f, false));
		dynamic_cast<Point_Light*>(PointLight3->components[1])->UINum = 2;
		Scenes[0]->GameObjects.push_back(PointLight3);

		//Modelo Arbol 1
		GameObject* ModeloArbol = new GameObject("Modelo Arbol 1");
		dynamic_cast<Transform*>(ModeloArbol->components[0])->Position = glm::vec3(35.0f, -6.0f, -80.0f);
		dynamic_cast<Transform*>(ModeloArbol->components[0])->Scale = glm::vec3(1.8f, 1.8f, 1.8f);
		Material* ArbolMaterial = new Material("model.vs", "model.ps");
		ArbolMaterial->SetTexture2D("basecolor", "Assets/Models/Arbol/ArbolTextura.jpg");
		ArbolMaterial->SetTexture2D("normalmap", "Assets/Models/Arbol/ArbolN.png");
		ModeloArbol->components.push_back(new MeshRenderer("Assets/Models/Arbol/Arbol.obj", &dynamic_cast<Transform*>(ModeloArbol->components[0])->Position, &dynamic_cast<Transform*>(ModeloArbol->components[0])->Rotation, &dynamic_cast<Transform*>(ModeloArbol->components[0])->Scale));
		dynamic_cast<MeshRenderer*>(ModeloArbol->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<MeshRenderer*>(ModeloArbol->components[1])->SetMaterial(ArbolMaterial);
		dynamic_cast<MeshRenderer*>(ModeloArbol->components[1])->HDRColor = true;
		dynamic_cast<MeshRenderer*>(ModeloArbol->components[1])->exposure = 1.142f;
		//ModeloArbol->components.push_back(new BoxCollider(&dynamic_cast<Transform*>(ModeloArbol->components[0])->Position, &dynamic_cast<Transform*>(ModeloArbol->components[0])->Rotation, &dynamic_cast<Transform*>(ModeloArbol->components[0])->Scale));
		Scenes[0]->GameObjects.push_back(ModeloArbol);

		GameObject* PointLightA1 = new GameObject("Punto de Luz 4");
		dynamic_cast<Transform*>(PointLightA1->components[0])->Position = glm::vec3(35.0f, 3.0f, -80.0f);
		PointLightA1->components.push_back(new Point_Light(&dynamic_cast<Transform*>(PointLightA1->components[0])->Position, new glm::vec3(0.0f, 0.7098f, 1.0f), new glm::vec3(0.0f, 0.7098f, 1.0f), new glm::vec3(0.0f, 0.7098f, 1.0f), 0.627f, 0.0f, 0.005f, false));
		dynamic_cast<Point_Light*>(PointLightA1->components[1])->UINum = 3;
		Scenes[0]->GameObjects.push_back(PointLightA1);

		//Modelo Arbol 2
		GameObject* ModeloArbol2 = new GameObject("Modelo Arbol 2");
		dynamic_cast<Transform*>(ModeloArbol2->components[0])->Position = glm::vec3(70.0f, -6.0f, 90.0f);
		dynamic_cast<Transform*>(ModeloArbol2->components[0])->Scale = glm::vec3(1.8f, 1.8f, 1.8f);
		ModeloArbol2->components.push_back(new MeshRenderer("Assets/Models/Arbol/Arbol.obj", &dynamic_cast<Transform*>(ModeloArbol2->components[0])->Position, &dynamic_cast<Transform*>(ModeloArbol2->components[0])->Rotation, &dynamic_cast<Transform*>(ModeloArbol2->components[0])->Scale));
		dynamic_cast<MeshRenderer*>(ModeloArbol2->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<MeshRenderer*>(ModeloArbol2->components[1])->SetMaterial(ArbolMaterial);
		dynamic_cast<MeshRenderer*>(ModeloArbol2->components[1])->HDRColor = true;
		dynamic_cast<MeshRenderer*>(ModeloArbol2->components[1])->UINum = 3;
		dynamic_cast<MeshRenderer*>(ModeloArbol2->components[1])->exposure = 1.142f;
		Scenes[0]->GameObjects.push_back(ModeloArbol2);

		//Point Light
		GameObject* PointLight = new GameObject("Punto de Luz 5");
		dynamic_cast<Transform*>(PointLight->components[0])->Position = glm::vec3(70.0f, 3.0f, 90.0f);
		PointLight->components.push_back(new Point_Light(&dynamic_cast<Transform*>(PointLight->components[0])->Position, new glm::vec3(0.0f, 0.7098f, 1.0f), new glm::vec3(0.0f, 0.7098f, 1.0f), new glm::vec3(0.0f, 0.7098f, 1.0f), 0.627f, 0.0f, 0.005f, false));
		Scenes[0]->GameObjects.push_back(PointLight);

		//Modelo Arbol 3
		GameObject* ModeloArbol3 = new GameObject("Modelo Arbol 3");
		dynamic_cast<Transform*>(ModeloArbol3->components[0])->Position = glm::vec3(10.0f, -6.0f, 120.0f);
		dynamic_cast<Transform*>(ModeloArbol3->components[0])->Scale = glm::vec3(1.8f, 1.8f, 1.8f);
		ModeloArbol3->components.push_back(new MeshRenderer("Assets/Models/Arbol/Arbol.obj", &dynamic_cast<Transform*>(ModeloArbol3->components[0])->Position, &dynamic_cast<Transform*>(ModeloArbol3->components[0])->Rotation, &dynamic_cast<Transform*>(ModeloArbol3->components[0])->Scale));
		dynamic_cast<MeshRenderer*>(ModeloArbol3->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<MeshRenderer*>(ModeloArbol3->components[1])->SetMaterial(ArbolMaterial);
		dynamic_cast<MeshRenderer*>(ModeloArbol3->components[1])->HDRColor = true;
		dynamic_cast<MeshRenderer*>(ModeloArbol3->components[1])->UINum = 4;
		dynamic_cast<MeshRenderer*>(ModeloArbol3->components[1])->exposure = 1.142f;
		Scenes[0]->GameObjects.push_back(ModeloArbol3);

		//Point Light A3
		GameObject* PointLightA3 = new GameObject("Punto de Luz 6");
		dynamic_cast<Transform*>(PointLightA3->components[0])->Position = glm::vec3(10.0f, 3.0f, 120.0f);
		PointLightA3->components.push_back(new Point_Light(&dynamic_cast<Transform*>(PointLightA3->components[0])->Position, new glm::vec3(0.0f, 0.7098f, 1.0f), new glm::vec3(0.0f, 0.7098f, 1.0f), new glm::vec3(0.0f, 0.7098f, 1.0f), 0.627f, 0.0f, 0.005f, false));
		dynamic_cast<Point_Light*>(PointLightA3->components[1])->UINum = 5;
		Scenes[0]->GameObjects.push_back(PointLightA3);

		//Modelo Arbol 4
		GameObject* ModeloArbol4 = new GameObject("Modelo Arbol 4");
		dynamic_cast<Transform*>(ModeloArbol4->components[0])->Position = glm::vec3(95.0f, -6.0f, -40.0f);
		dynamic_cast<Transform*>(ModeloArbol4->components[0])->Scale = glm::vec3(1.8f, 1.8f, 1.8f);
		ModeloArbol4->components.push_back(new MeshRenderer("Assets/Models/Arbol/Arbol.obj", &dynamic_cast<Transform*>(ModeloArbol4->components[0])->Position, &dynamic_cast<Transform*>(ModeloArbol4->components[0])->Rotation, &dynamic_cast<Transform*>(ModeloArbol4->components[0])->Scale));
		dynamic_cast<MeshRenderer*>(ModeloArbol4->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<MeshRenderer*>(ModeloArbol4->components[1])->SetMaterial(ArbolMaterial);
		dynamic_cast<MeshRenderer*>(ModeloArbol4->components[1])->HDRColor = true;
		dynamic_cast<MeshRenderer*>(ModeloArbol4->components[1])->UINum = 5;
		dynamic_cast<MeshRenderer*>(ModeloArbol4->components[1])->exposure = 1.142f;
		Scenes[0]->GameObjects.push_back(ModeloArbol4);

		//Point Light A4
		GameObject* PointLightA4 = new GameObject("Punto de Luz 7");
		dynamic_cast<Transform*>(PointLightA4->components[0])->Position = glm::vec3(95.0f, 3.0f, -40.0f);
		PointLightA4->components.push_back(new Point_Light(&dynamic_cast<Transform*>(PointLightA4->components[0])->Position, new glm::vec3(0.0f, 0.7098f, 1.0f), new glm::vec3(0.0f, 0.7098f, 1.0f), new glm::vec3(0.0f, 0.7098f, 1.0f), 0.627f, 0.0f, 0.005f, false));
		dynamic_cast<Point_Light*>(PointLightA4->components[1])->UINum = 5;
		Scenes[0]->GameObjects.push_back(PointLightA4);

		//Farola 1
		GameObject* Farola1 = new GameObject("Farola 1");
		dynamic_cast<Transform*>(Farola1->components[0])->Position = glm::vec3(-10.0f, -5.0f, 30.0f);
		dynamic_cast<Transform*>(Farola1->components[0])->Scale = glm::vec3(1.8f, 1.8f, 1.8f);
		Material* FarolaMaterial = new Material("model.vs", "model.ps");
		FarolaMaterial->SetTexture2D("basecolor", "Assets/Models/Farola/farola_text.png");
		FarolaMaterial->SetTexture2D("normalmap", "Assets/Models/Farola/farola_textnorm.png");
		FarolaMaterial->SetTexture2D("emissivemap", "Assets/Models/Farola/farola_emissive.png");
		Farola1->components.push_back(new MeshRenderer("Assets/Models/Farola/farola.obj", &dynamic_cast<Transform*>(Farola1->components[0])->Position, &dynamic_cast<Transform*>(Farola1->components[0])->Rotation, &dynamic_cast<Transform*>(Farola1->components[0])->Scale));
		dynamic_cast<MeshRenderer*>(Farola1->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<MeshRenderer*>(Farola1->components[1])->SetMaterial(FarolaMaterial);
		dynamic_cast<MeshRenderer*>(Farola1->components[1])->HDRColor = true;
		dynamic_cast<MeshRenderer*>(Farola1->components[1])->exposure = 2.045f;
		dynamic_cast<MeshRenderer*>(Farola1->components[1])->UINum = 1;
		Scenes[0]->GameObjects.push_back(Farola1);

		//Farola 2
		GameObject* Farola2 = new GameObject("Farola 2");
		dynamic_cast<Transform*>(Farola2->components[0])->Position = glm::vec3(-10.0f, -5.0f, -30.0f);
		dynamic_cast<Transform*>(Farola2->components[0])->Scale = glm::vec3(1.8f, 1.8f, 1.8f);
		Farola2->components.push_back(new MeshRenderer("Assets/Models/Farola/farola.obj", &dynamic_cast<Transform*>(Farola2->components[0])->Position, &dynamic_cast<Transform*>(Farola2->components[0])->Rotation, &dynamic_cast<Transform*>(Farola2->components[0])->Scale));
		dynamic_cast<MeshRenderer*>(Farola2->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<MeshRenderer*>(Farola2->components[1])->SetMaterial(FarolaMaterial);
		dynamic_cast<MeshRenderer*>(Farola2->components[1])->HDRColor = true;
		dynamic_cast<MeshRenderer*>(Farola2->components[1])->exposure = 2.045f;
		dynamic_cast<MeshRenderer*>(Farola2->components[1])->UINum = 2;
		Scenes[0]->GameObjects.push_back(Farola2);


		//Dithering
		GameObject* FarolaDith = new GameObject("Farola Dithering");
		dynamic_cast<Transform*>(FarolaDith->components[0])->Position = glm::vec3(-10.0f, -5.0f, -50.0f);
		dynamic_cast<Transform*>(FarolaDith->components[0])->Scale = glm::vec3(1.8f, 1.8f, 1.8f);
		FarolaDith->components.push_back(new MeshRenderer("Assets/Models/Farola/farola.obj", &dynamic_cast<Transform*>(FarolaDith->components[0])->Position, &dynamic_cast<Transform*>(FarolaDith->components[0])->Rotation, &dynamic_cast<Transform*>(FarolaDith->components[0])->Scale));
		dynamic_cast<MeshRenderer*>(FarolaDith->components[1])->settings = Scenes[0]->Render_Settings;
		Material* DitheringMat = new Material("ditheringOpacity.vs", "ditheringOpacity.ps");
		DitheringMat->SetTexture2D("basecolor", "Assets/Models/Farola/farola_text.png");
		dynamic_cast<MeshRenderer*>(FarolaDith->components[1])->SetMaterial(DitheringMat);
		Scenes[0]->GameObjects.push_back(FarolaDith);

		//AudioSource
		GameObject* AudioSource1 = new GameObject("AudioBGM1");
		AudioSource1->components.push_back(new AudioSource("Assets/Music/CrystalTheme.mp3", glm::vec3(0.0f, 0.0f, 0.0f), true));
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
		TerrainObj->components.push_back(new Terrain("Assets/Terrain/height.png"));
		dynamic_cast<Terrain*>(TerrainObj->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<Terrain*>(TerrainObj->components[1])->SetMaterial(TerrainMat);
		Scenes[0]->GameObjects.push_back(TerrainObj);

		/*Animated Model*/
		//Material
		Material* Animated_Model_Material = new Material("anim_model.vs", "anim_model.ps");
		//Animated_Model_Material->Material_Settings->Transparent
		std::vector<Animation*> animations1;
		GameObject* Animated_Model = new GameObject("Modelo Animado");
		dynamic_cast<Transform*>(Animated_Model->components[0])->Position = glm::vec3(0.0f, -4.0f, 0.0f);
		dynamic_cast<Transform*>(Animated_Model->components[0])->Scale = glm::vec3(0.06f, 0.06f, 0.06f);
		Animated_Model->components.push_back(new AnimatedModel("Assets/Models/Animated_1/Player_Base2.fbx", Animated_Model_Material, &dynamic_cast<Transform*>(Animated_Model->components[0])->Position, &dynamic_cast<Transform*>(Animated_Model->components[0])->Rotation, &dynamic_cast<Transform*>(Animated_Model->components[0])->Scale));
		Animation* anim0 = new Animation("Assets/Models/Animated_1/Idle_Final.fbx", dynamic_cast<AnimatedModel*>(Animated_Model->components[1])->model);
		Animation* anim1 = new Animation("Assets/Models/Animated_1/Run_Final.fbx", dynamic_cast<AnimatedModel*>(Animated_Model->components[1])->model);
		Animation* anim2 = new Animation("Assets/Models/Animated_1/Dodge_Final.fbx", dynamic_cast<AnimatedModel*>(Animated_Model->components[1])->model);
		animations1.push_back(anim0);
		animations1.push_back(anim1);
		animations1.push_back(anim2);
		dynamic_cast<AnimatedModel*>(Animated_Model->components[1])->animations = animations1;
		dynamic_cast<AnimatedModel*>(Animated_Model->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<AnimatedModel*>(Animated_Model->components[1])->SetupAnimator();
		Scenes[0]->GameObjects.push_back(Animated_Model);

		//Player Controller
		Playercontroller* playercontrol = new Playercontroller(dynamic_cast<Transform*>(Animated_Model->components[0])
		, glm::vec3(0.0f, 15.0f, -20.0f), 1.5f, dynamic_cast<Transform*>(CameraGameObj->components[0]));
		playercontrol->MainCam = dynamic_cast<Camera*>(CameraGameObj->components[1]);
		playercontrol->playerAnimator = dynamic_cast<AnimatedModel*>(Animated_Model->components[1])->animator;
		CameraGameObj->components.push_back(playercontrol);
		
		//Modelo plane
		GameObject* PlanoObj = new GameObject("Water");
		dynamic_cast<Transform*>(PlanoObj->components[0])->Position = glm::vec3(-70.0f, -11.0f, 10.0f);
		dynamic_cast<Transform*>(PlanoObj->components[0])->Scale = glm::vec3(4.0f, 4.0f, 9.0f);
		Material* PlaneMat = new Material("water.vs", "water.ps");
		PlaneMat->Material_Settings->Transparent = true;
		PlaneMat->SetTexture2D("Normal1", "Assets/Models/water/AguaN1.png");
		PlaneMat->SetTexture2D("Normal2", "Assets/Models/water/AguaN2.jpg");
		Material::Texture watertex;
		watertex.IdTexture = *MainLightData::POSTMAP;
		watertex.Name = "Render1";
		Material::Texture watertex2;
		watertex2.IdTexture = *MainLightData::POSTMAP_1;
		watertex2.Name = "Render2_HDR";
		Material::Texture watertex3;
		watertex3.IdTexture = *MainLightData::POSTMAP_DEPTH;
		watertex3.Name = "DepthTexture";

		PlaneMat->Textures.push_back(watertex);
		PlaneMat->Textures.push_back(watertex2);
		PlaneMat->Textures.push_back(watertex3);
		PlanoObj->components.push_back(new MeshRenderer("Assets/Models/water/water.obj", &dynamic_cast<Transform*>(PlanoObj->components[0])->Position, &dynamic_cast<Transform*>(PlanoObj->components[0])->Rotation, &dynamic_cast<Transform*>(PlanoObj->components[0])->Scale));
		WaterEffect* water_effect = new WaterEffect();
		water_effect->WaterMaterial = PlaneMat;
		PlanoObj->components.push_back(water_effect);
		dynamic_cast<MeshRenderer*>(PlanoObj->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<MeshRenderer*>(PlanoObj->components[1])->SetMaterial(PlaneMat);
		Scenes[0]->GameObjects.push_back(PlanoObj);
		

		//Texto Fuente Crayola
		Material* TextoMat = new Material("text.vs", "text.ps");
		TextoMat->Material_Settings->Transparent = true;
		GameObject* TextUIBase = new GameObject("Texto UI 1");
		dynamic_cast<Transform*>(TextUIBase->components[0])->Position = glm::vec3(500.0f, 800.0f, 1.0f);
		dynamic_cast<Transform*>(TextUIBase->components[0])->Scale = glm::vec3(1.0f, 1.0f, 1.0f);
		TextUIBase->components.push_back(new TextUI("Assets/Fonts/CrayonLibre.ttf", &dynamic_cast<Transform*>(TextUIBase->components[0])->Position, new glm::vec3(1.0f, 0.0f, 0.0f), "Text de prueba", & dynamic_cast<Transform*>(TextUIBase->components[0])->Scale));
		dynamic_cast<TextUI*>(TextUIBase->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<TextUI*>(TextUIBase->components[1])->SetMaterial(TextoMat);
		//Scenes[0]->GameObjects.push_back(TextUIBase);

		//Texto Fuente KomiAxis
		GameObject* TextUIBase_2 = new GameObject("Texto UI 2");
		dynamic_cast<Transform*>(TextUIBase_2->components[0])->Position = glm::vec3(800.0f, 30.0f, 1.0f);
		dynamic_cast<Transform*>(TextUIBase_2->components[0])->Scale = glm::vec3(0.5f, 0.5f, 0.5f);
		TextUIBase_2->components.push_back(new TextUI("Assets/Fonts/KOMIKAX_.ttf", &dynamic_cast<Transform*>(TextUIBase_2->components[0])->Position, new glm::vec3(0.7f, 0.2f, 0.5f), "Holiii :)", &dynamic_cast<Transform*>(TextUIBase_2->components[0])->Scale));
		dynamic_cast<TextUI*>(TextUIBase_2->components[1])->settings = Scenes[0]->Render_Settings;
		dynamic_cast<TextUI*>(TextUIBase_2->components[1])->SetMaterial(TextoMat);
		//Scenes[0]->GameObjects.push_back(TextUIBase_2);

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