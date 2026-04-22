//
// Created by Dashiell on 2026-04-20.
//

#ifndef JOLTAN_INSTANCES_HPP
#define JOLTAN_INSTANCES_HPP

#include "render.hpp"
#include "../external/include/GL/glew.h"

struct Component {
    virtual void init() {}
    virtual void update(float dt) {}
    virtual void render() {}

    virtual ~Component() = default;
};


struct MeshRender : Component {
    std::vector<float> verts;
    GLuint shader;
    GLuint VAO, VBO;
    GLuint MVP_loc;

    void init() override {
        render_init();
    }
    void update() override {
        render_draw();
    }
    
}

#endif //JOLTAN_INSTANCES_HPP
