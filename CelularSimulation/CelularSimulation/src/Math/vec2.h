#pragma once

namespace SC
{
	template<typename T>
	struct vec2
	{
		vec2<T>(T p1, T p2) : values{ p1, p2 } {};
		vec2<T>() = delete;

		union
		{
			struct
			{
				T x; T y;
			};
	
			struct
			{
				T r; T g;
			};
	
			struct
			{
				T U; T V;
			};
	
			struct
			{
				T values[2];
			};
		};
	};
}