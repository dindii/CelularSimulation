#pragma once

namespace SC
{
	template<typename T>
	struct vec3
	{
		vec3<T>(T p1, T p2, T p3) : values{ p1, p2, p3 } {};
		vec3<T>() = delete;

		union
		{
			struct
			{
				T x; T y; T z;
			};

			struct
			{
				T r; T g; T b;
			};

			struct
			{
				T U; T V; T W;
			};

			struct
			{
				T values[3];
			};
		};
	};
}
