#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

#include <glm/glm.hpp>

#include "Basic.h"

namespace Phys75 {

	class Object2D
	{
		friend class World2D;

	public:
		using CollisionFunc = std::function<bool(const Object2D other)>;

		bool COLLIDER = false;
		bool AFFECT_GRAVITY = false;

		void on_collision(CollisionFunc func);

	private:
		Object2D(uint64_t ID, const std::vector<float>& points);

	private:
		uint64_t m_ID = 0;
		CollisionFunc m_CollisionFunc;
		std::vector<float> m_Points;
	};

	struct Gravity
	{
		glm::vec2 DIR = {0.0f, 0.0f};
		float STRENGTH = 0.0f;
	};

	class World2D
	{
		void set_gravity(const glm::vec2& dir, float strength);

		void update(Timestep ts);

		Object2D& add_object(const std::vector<float>& points);

	private:
		std::vector<Object2D> m_Objects;
		Gravity m_Gravity;
		uint64_t m_IdCounter = 0;
	};
}
