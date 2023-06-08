#pragma once

namespace CS
{
	template<typename T>
	struct vec4
	{
		vec4<T>(T p1, T p2, T p3, T p4) : values{ p1, p2, p3, p4 } {};
		vec4<T>() = delete;

		union
		{
			struct
			{
				T x; T y; T z; T w;
			};

			struct
			{
				T r; T g; T b; T a;
			};

			struct
			{
				T U; T V; T W; T X;
			};

			struct
			{
				T values[4];
			};
		};
	};
}
