#pragma once

#include <glm/glm.hpp>

namespace Phys75 {

	struct Transformation2D
	{
		glm::vec2 m_Position;
		glm::vec2 m_Size;
		float m_Rotation;
	};

	struct Vertex2D
	{
		glm::vec2 m_Position;
	};

	struct Shape
	{
		enum class Type { Circle, Polygon };

		Vertex2D* m_Begin;
		uint8_t m_Size;
	};

	struct Collider
	{
		char* m_Shapes;
	};

	struct Entity
	{
		int m_ID;
	};

}