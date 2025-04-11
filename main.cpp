#include <iostream>
#include "Vec2.h"

int main() {
    Vec2<double> v1(2.0, 3.0);
    Vec2<double> v2(4.0, 1.0);

    // Vector + Vector
    Vec2<double> add = v1 + v2;
    std::cout << "v1 + v2 = (" << add.x << ", " << add.y << ")\n";

    // Vector - Vector
    Vec2<double> sub = v1 - v2;
    std::cout << "v1 - v2 = (" << sub.x << ", " << sub.y << ")\n";

    // Vector + Scalar
    Vec2<double> addScalar = v1 + 2.0;
    std::cout << "v1 + 2.0 = (" << addScalar.x << ", " << addScalar.y << ")\n";

    // Vector - Scalar
    Vec2<double> subScalar = v1 - 2.0;
    std::cout << "v1 - 2.0 = (" << subScalar.x << ", " << subScalar.y << ")\n";

    // Vector * Scalar
    Vec2<double> mulScalar = v1 * 2.0;
    std::cout << "v1 * 2.0 = (" << mulScalar.x << ", " << mulScalar.y << ")\n";

    // Vector / Scalar
    Vec2<double> divScalar = v1 / 2.0;
    std::cout << "v1 / 2.0 = (" << divScalar.x << ", " << divScalar.y << ")\n";

    // Compound assignment operators
    Vec2<double> v3 = v1;
    v3 += v2;
    std::cout << "v1 += v2 → v1 = (" << v3.x << ", " << v3.y << ")\n";

    v3 = v1;
    v3 -= v2;
    std::cout << "v1 -= v2 → v1 = (" << v3.x << ", " << v3.y << ")\n";

    v3 = v1;
    v3 *= 2.0;
    std::cout << "v1 *= 2.0 → v1 = (" << v3.x << ", " << v3.y << ")\n";

    v3 = v1;
    v3 /= 2.0;
    std::cout << "v1 /= 2.0 → v1 = (" << v3.x << ", " << v3.y << ")\n";

    return 0;
}
