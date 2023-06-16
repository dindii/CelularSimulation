#pragma once
#include <iostream>

namespace CS
{
	template<typename T>
	struct vec4
	{
		vec4(T p1, T p2, T p3, T p4) : values{ p1, p2, p3, p4 } {};
		vec4() : x(0), y(0), z(0), w(0) { std::cout << "\nWarning: Use of non-initialized vector, this could lead to problems if you don't initialize it soon.\n";  };

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
