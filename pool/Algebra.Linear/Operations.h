#pragma once

#include "defines.h"
#include "Commons.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix.h"

namespace Algebra
{
    LINEARALGEBRA_API TFLOAT Magnitude(const Quaternion &q);
    LINEARALGEBRA_API Quaternion Conjugate(const Quaternion &q);
    LINEARALGEBRA_API Quaternion Inverse(const Quaternion &q);
    LINEARALGEBRA_API Quaternion Normalize(const Quaternion &q);
}

namespace Algebra { namespace Linear
{
    LINEARALGEBRA_API Vector2D Versor(Axis2D axis);
    LINEARALGEBRA_API TFLOAT Angle(const Vector2D &u, Axis2D axis);
    LINEARALGEBRA_API TFLOAT Angle(const Vector2D &u, const Vector2D &v);
    LINEARALGEBRA_API Vector2D Rotate(const Vector2D &u, TFLOAT alfa);
    LINEARALGEBRA_API Vector2D Rotate(const Vector2D &u, const Vector2D &origin,
        TFLOAT alfa);
    LINEARALGEBRA_API TFLOAT Distance(const Vector2D &u, const Vector2D &v);
    LINEARALGEBRA_API Vector2D Perpendicular(const Vector2D &u, Direction direction);
    LINEARALGEBRA_API Vector2D Normalize(const Vector2D &u);
    LINEARALGEBRA_API TFLOAT Magnitude(const Vector2D &u);
    LINEARALGEBRA_API Vector3D Versor(Axis3D axis);
    LINEARALGEBRA_API TFLOAT Angle(const Vector3D &u, Axis3D axis);
    LINEARALGEBRA_API TFLOAT Angle(const Vector3D &u, const Vector3D &v);
    LINEARALGEBRA_API TFLOAT Angle(const Vector3D &u, const Vector3D &v, Axis3D axis);
    LINEARALGEBRA_API Vector3D Rotate(const Vector3D &u, const Quaternion &q);
    LINEARALGEBRA_API Vector3D Rotate(const Vector3D &u, const Vector3D &axis, TFLOAT alpha);
    LINEARALGEBRA_API TFLOAT Distance(const Vector3D &u, const Vector3D &v);
    LINEARALGEBRA_API Vector3D Normalize(const Vector3D &u);
    LINEARALGEBRA_API TFLOAT Magnitude(const Vector3D &u);
    LINEARALGEBRA_API Quaternion Convert(Axis3D axis, TFLOAT alpha);
    LINEARALGEBRA_API Quaternion Convert(const Vector3D &axis, TFLOAT alpha);
    LINEARALGEBRA_API void Convert(const Quaternion &quaternion, Vector3D *axis,
        TFLOAT *alpha);
} }
