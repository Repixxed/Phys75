#include "World.h"


namespace Phys75 {

    //Object2D

    Object2D::Object2D(uint64_t ID, const std::vector<float>& points)
    {
        m_ID = ID;
        m_Points = points;
    }

    void Object2D::on_collision(CollisionFunc func)
    {
        m_CollisionFunc = func;
    }

    //World2D

    void World2D::set_gravity(const glm::vec2& dir, float strength)
    {
        m_Gravity = {dir, strength};
    }

    Object2D& World2D::add_object(const std::vector<float>& points)
    {
        m_Objects.push_back(Object2D(m_IdCounter, points));
        return m_Objects.back();
    }

}