#include "Gameobject.h"

GameObject::GameObject(const char* name_gm)
{
    components.push_back(new Transform(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f));
    name = name_gm;
}

void GameObject::Update()
{
    for (Component* component : components) {
        component->Update();
    }

    for (GameObject* child : children) {
        child->Update();
    }
}

void GameObject::Draw()
{
    //ImGui
    if(MainSettings::RenderN == MainSettings::NumRenders)
    {
        ImGui::Text(name);
        ImGui::InputFloat3((std::string("Pos ") + name).c_str(), &dynamic_cast<Transform*>(components[0])->Position.x);
        ImGui::InputFloat3((std::string("Rot ") + name).c_str(), &dynamic_cast<Transform*>(components[0])->Rotation.x);
        ImGui::InputFloat3((std::string("Scale ") + name).c_str(), &dynamic_cast<Transform*>(components[0])->Scale.x);
    }
    
    for (Component* component : components) {
        component->Draw();
    }

    for (GameObject* child : children) {
        child->Draw();
    }
}