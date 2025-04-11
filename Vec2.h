#include <cmath>
template<typename T>
class Vec2 {
public:
    T x, y;

    Vec2() :x(0), y(0) {}
	Vec2(T x, T y) : x(x), y(y) {}
	Vec2& operator=(const Vec2& v) {
    // Copy the values from 'v' to 'this' object
    this->x = v.x;
    this->y = v.y;

    // Return the object itself, not a copy!
    return *this;
   }
   Vec2& operator+=(const Vec2& v) {
    // Add the values from 'v' to 'this' object
    this->x += v.x;
    this->y += v.y;

    // Return the object itself, not a copy!
    return *this;
   }
   Vec2 operator+(Vec2& v) {
		return Vec2(x + v.x, y + v.y);
	}
	Vec2 operator-(Vec2& v) {
		return Vec2(x - v.x, y - v.y);
	}

   Vec2 operator+(double s) {
		return Vec2(x + s, y + s);
	}
	Vec2 operator-(double s) {
		return Vec2(x - s, y - s);
	}
	Vec2 operator*(double s) {
		return Vec2(x * s, y * s);
	}
	Vec2 operator/(double s) {
		return Vec2(x / s, y / s);
	}

   Vec2& operator-=(const Vec2& v) {
    // Subtract the values from 'v' to 'this' object
    this->x -= v.x;
    this->y -= v.y;

    // Return the object itself, not a copy!
    return *this;
   }
   Vec2& operator*=(T scalar) {
    // Multiply the values from 'scalar' to 'this' object
    this->x *= scalar;
    this->y *= scalar;

    // Return the object itself, not a copy!
    return *this;
   }
   Vec2& operator/=(T scalar) {
    // Divide the values from 'scalar' to 'this' object
    this->x /= scalar;
    this->y /= scalar;

    // Return the object itself, not a copy!
    return *this;
   }
};
