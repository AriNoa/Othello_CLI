#pragma once


namespace otl {
	struct Point {
		int x;
		int y;

        Point operator +() const
        {
            return *this;
        }

        Point operator -() const
        {
            return{ -x, -y };
        }

        Point operator +(const Point& other) const
        {
            return{ x + other.x, y + other.y };
        }

        Point operator -(const Point& other) const
        {
            return{ x - other.x, y - other.y };
        }

        Point operator *(int s) const {
            return{ x * s, y * s };
        }

        Point operator /(int s) const {
            return{ x / s, y / s };
        }

        Point& operator +=(const Point& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        Point& operator -=(const Point& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Point& operator *=(int s)
        {
            x *= s;
            y *= s;
            return *this;
        }

        Point& operator /=(int s)
        {
            x /= s;
            y /= s;
            return *this;
        }
	};
}