//
// Created by Dashiell on 2026-04-20.
//

#ifndef JOLTAN_INSTANCES_HPP
#define JOLTAN_INSTANCES_HPP

struct Component {
    virtual void init() {}
    virtual void update(float dt) {}
    virtual void render() {}

    virtual ~Component() = default;
};


struct MeshRender : Component {
    float Verts[] {}
}

#endif //JOLTAN_INSTANCES_HPP
