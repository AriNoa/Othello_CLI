#pragma once
#include <array>
#include <cassert>
#include "Point.h"


namespace otl {
	class DirVector : public Point {
	public:
		DirVector() = default;

		constexpr DirVector(const int& dx, const int& dy)
			: Point{ dx, dy } {
			assert(dx == -1 || dx == 0 || dx == 1);
			assert(dy == -1 || dy == 0 || dy == 1);
			assert(dx != 0 || dy != 0);
		}
	};

	constexpr std::array<DirVector, 8> createDirVectors() {
		return {
			DirVector
			{ -1, -1 },	{ 0, -1 },	{ 1, -1 },
			{ -1, 0  },				{ 1, 0  },
			{ -1, 1  },	{ 0, 1  },	{ 1, 1  }
		};
	}
}