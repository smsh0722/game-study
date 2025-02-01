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