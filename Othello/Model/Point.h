#pragma once


namespace otl {
	struct Point {
		int x;
		int y;

        constexpr Point operator +() const
        {
            return *this;
        }

        constexpr Point operator -() const
        {
            return{ -x, -y };
        }

        constexpr Point operator +(const Point& other) const
        {
            return{ x + other.x, y + other.y };
        }

        constexpr Point operator -(const Point& other) const
        {
            return{ x - other.x, y - other.y };
        }

        constexpr Point operator *(int s) const {
            return{ x * s, y * s };
        }

        constexpr Point operator /(int s) const {
            return{ x / s, y / s };
        }

        constexpr Point& operator +=(const Point& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        constexpr Point& operator -=(const Point& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        constexpr Point& operator *=(int s)
        {
            x *= s;
            y *= s;
            return *this;
        }

        constexpr Point& operator /=(int s)
        {
            x /= s;
            y /= s;
            return *this;
        }

        constexpr bool operator ==(const Point& other) const {
            return x == other.x && other.x;
        }
	};
}