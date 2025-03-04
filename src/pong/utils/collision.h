#pragma once
#include "../object.h"

namespace collision {

inline bool AABB(const Object &obj1, const Object &obj2) {
    return (
        obj1.position_.x < obj2.position_.x + obj2.size_.x &&
        obj1.position_.x + obj1.size_.x > obj2.position_.x &&
        obj1.position_.y < obj2.position_.y + obj2.size_.y &&
        obj1.position_.y + obj1.size_.y > obj2.position_.y
    );
}


} // namespace collision

