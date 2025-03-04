#pragma once
#include "../object.h"


namespace collision {

inline bool AABB(const Object &obj1, const Object &obj2) {
    const float halfWidth1 = obj1.size_.x * 0.5f;
    const float halfHeight1 = obj1.size_.y * 0.5f;
    const float halfWidth2 = obj2.size_.x * 0.5f;
    const float halfHeight2 = obj2.size_.y * 0.5f;

    return (
        (obj1.position_.x - halfWidth1) < (obj2.position_.x + halfWidth2) &&
        (obj1.position_.x + halfWidth1) > (obj2.position_.x - halfWidth2) &&
        (obj1.position_.y - halfHeight1) < (obj2.position_.y + halfHeight2) &&
        (obj1.position_.y + halfHeight1) > (obj2.position_.y - halfHeight2)
    );
}

} // namespace collision

