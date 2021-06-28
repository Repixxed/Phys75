#pragma once

#if defined(__GNUC__) || defined(__clang__)
	#define ALIGN(x) __attribute__((aligned(x)))
#elif defined(_MSC_VER)
	#define ALIGN(x) __declspec(align(x))
#endif

namespace Phys75 {

	template<typename Type = float>
	struct Vec2
	{
		union { Type x, r; };
		union { Type y, g; };
	};

	template<typename Type = float>
	struct Vec3
	{
		union { Type x, r; };
		union { Type y, g; };
		union { Type z, b; };
	};

	template<typename Type = float>
	struct ALIGN(16) Vec4
	{
		union { Type x, r; };
		union { Type y, g; };
		union { Type z, b; };
		union { Type w, a; };
	};
}




