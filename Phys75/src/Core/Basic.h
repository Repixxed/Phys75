#pragma once

#include <stdint.h>

namespace Phys75
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time), m_LastTime(0) {}

		void update(float currentTime)
		{
			m_Time = currentTime - m_LastTime;
			m_LastTime = currentTime;
		}

		operator float() const { return m_Time; }

		float get_seconds() const { return m_Time; }
		float get_millis() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
		float m_LastTime;
	};
}
