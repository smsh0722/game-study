#pragma once
#include <cmath>
#include <memory.h>
#include <limits>

// 2D vector
class Vector2
{
public:
    float x;
    float y;

    Vector2()
        :x(0.0f), y(0.0f) {}
    explicit Vector2( float xFloat, float yFloat)
        : x(xFloat), y(yFloat) {}
    
    // a - b
    friend Vector2& operator-( const Vector2& a, const Vector2& b )
    {
        return Vector2( a.x - b.x, a.y - b.y );
    };

    // Length squared of vector
	float LengthSq() const
	{
		return (x*x + y*y);
	}

    // Length of vector
	float Length() const
	{
		return (sqrtf(LengthSq()));
	}

    static const Vector2 Zero;
};

namespace Math
{
    const float PI = 3.1415926535f;

    inline float ToDegrees( float radians )
    {   // 180 degree = 1PI
        return (radians / PI) * 180.0f;
    }
}