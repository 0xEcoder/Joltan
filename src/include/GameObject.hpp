#ifndef JOLTAN_GAMEOBJECT_HPP
#define JOLTAN_GAMEOBJECT_HPP

#include <vector>
#include <memory>

#include "external/universal/glm/glm/glm.hpp"
#include "external/universal/glm/glm/gtc/matrix_transform.hpp"
#include "external/universal/glm/glm/gtc/type_ptr.hpp"
#include "Instances.hpp"

struct Component; // forward declare

struct GameObject
{
    glm::vec3 position {0.0f, 0.0f, 0.0f};
    glm::vec3 rotation {0.0f, 0.0f, 0.0f};
    glm::vec3 scale    {1.0f, 1.0f, 1.0f};

    std::vector<std::unique_ptr<Component>> components;

    glm::mat4 getModelMatrix() const
    {
        glm::mat4 model(1.0f);

        model = glm::translate(model, position);
        model = glm::rotate(model, rotation.x, glm::vec3(1,0,0));
        model = glm::rotate(model, rotation.y, glm::vec3(0,1,0));
        model = glm::rotate(model, rotation.z, glm::vec3(0,0,1));
        model = glm::scale(model, scale);

        return model;
    }

    template<typename T, typename... Args>
    T* AddComponent(Args&&... args)
    {
        T* comp = new T(std::forward<Args>(args)...);

        comp->owner = this; // IMPORTANT

        components.emplace_back(comp);

        return comp;
    }

    void Init()
    {
        for (auto& c : components)
            c->init();
    }

    void Update(float dt)
    {
        for (auto& c : components)
            c->update(dt);
    }

    void Render()
    {
        for (auto& c : components)
            c->render();
    }
};

#endif