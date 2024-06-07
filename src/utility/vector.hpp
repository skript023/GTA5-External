#pragma once

namespace rage
{
	struct vector2
	{
		vector2() = default;
		vector2(float x, float y): x(x), y(y)
		{}

		float x{};
		float y{};
	};

	struct vector3
	{
		vector3() = default;
		vector3(float x, float y, float z): x(x), y(y), z(z)
		{}

		float x{};
		float y{};
		float z{};
	};

	struct vector4
	{
		vector4() = default;
		vector4(float x, float y, float z, float w): x(x), y(y), z(z), w(w)
		{}
		
		float x{};
		float y{};
		float z{};
		float w{};
	};
}