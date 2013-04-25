#include <exception>

#include <cmath>

#include "Operations.h"

using namespace std;

namespace Algebra
{
    Quaternion Inverse(const Quaternion &q)
    {
        TFLOAT magnitude = Magnitude(q);
        if (magnitude == 0.0)
            throw new exception("Quaternion is degenerate");

        return Quaternion(q.W / magnitude, -q.X / magnitude,
            -q.Y / magnitude, -q.Z / magnitude);
    }

    Quaternion Normalize(const Quaternion &q)
    {
        TFLOAT magnitude = Magnitude(q);
        if (magnitude == 0.0)
            throw new exception("Quaternion is degenerate");
        return q / magnitude;
    }

    TFLOAT Magnitude(const Quaternion &q)
    {
        return sqrt(q.W * q.W + q.X * q.X + q.Y * q.Y + q.Z * q.Z);
    }

    Quaternion Conjugate(const Quaternion &q)
    {
        return Quaternion(q.W, -q.X, -q.Y, -q.Z);
    }
}

namespace Algebra { namespace Linear
{
    static Quaternion convert(const Vector3D &normalized, TFLOAT alpha);

    Vector2D Versor(Axis2D axis)
    {
        switch (axis)
        {
            case AXIS2D_X:
                return Vector2D(1, 0);
            case AXIS2D_Y:
                return Vector2D(0, 1);
            default:
                throw exception("Wrong axis");
        }
    }

    TFLOAT Angle(const Vector2D &u, Axis2D axis)
    {
        throw exception("Not Implemented");
    }

    TFLOAT Angle(const Vector2D &u, const Vector2D &v)
    {
        throw exception("Not Implemented");
    }

    Vector2D Rotate(const Vector2D &u, TFLOAT alfa)
    {
        TFLOAT newX = (cos(alfa) * u.X) - (sin(alfa) * u.Y);
        TFLOAT newY = (sin(alfa) * u.X) + (cos(alfa) * u.Y);
        return Vector2D(newX, newY);
    }

    Vector2D Rotate(const Vector2D &u, const Vector2D &origin, TFLOAT alfa)
    {
        throw exception("Not Implemented");
    }

    TFLOAT Distance(const Vector2D &u, const Vector2D &v)
    {
        TFLOAT ret = sqrt(
            (u.X - v.X) * (u.X - v.X)
            + (u.Y - v.Y) * (u.Y - v.Y));
        return ret;
    }

    Vector2D Perpendicular(const Vector2D &u, Direction direction)
    {
        throw exception("Not Implemented");
    }

    Vector2D Normalize(const Vector2D &u)
    {
        TFLOAT magnitude = Magnitude(u);
        if (magnitude == 0.0)
            throw new exception("Vector is degenerate");
        return u / magnitude;
    }

    TFLOAT Magnitude(const Vector2D &u)
    {
        return sqrt(u.X * u.X + u.Y * u.Y);
    }

    Vector3D Versor(Axis3D axis)
    {
        switch (axis)
        {
            case AXIS3D_X:
                return Vector3D(1, 0, 0);
            case AXIS3D_Y:
                return Vector3D(0, 1, 0);
            case AXIS3D_Z:
                return Vector3D(0, 0, 1);
            default:
                throw exception("Wrong axis");
        }
    }

    TFLOAT Angle(const Vector3D &u, Axis3D axis)
    {
        throw exception("Not Implemented");
    }

    TFLOAT Angle(const Vector3D &u, const Vector3D &v)
    {
        throw exception("Not Implemented");
    }

    TFLOAT Angle(const Vector3D &u, const Vector3D &v, Axis3D axis)
    {
        throw exception("Not Implemented");
    }

    Vector3D Rotate(const Vector3D &u, const Quaternion &q)
    {
        Quaternion quatVec(0, u.X, u.Y, u.Z);

        Quaternion quatRes = q * quatVec * Inverse(q);
        
        return Vector3D(quatRes.X, quatRes.Y, quatRes.Z);
    }

    Vector3D Rotate(const Vector3D &u, const Vector3D &axis, TFLOAT alpha)
    {
        Quaternion quaternion = Convert(axis, alpha);
        return Rotate(u, quaternion);
    }

    TFLOAT Distance(const Vector3D &u, const Vector3D &v)
    {
        throw exception("Not Implemented");
    }

    Vector3D Normalize(const Vector3D &u)
    {
        TFLOAT magnitude = Magnitude(u);
        if (magnitude == 0.0)
            throw new exception("Vector is degenerate");
        return u / magnitude;
    }

    TFLOAT Magnitude(const Vector3D &u)
    {
        return sqrt(u.X * u.X + u.Y * u.Y + u.Z * u.Z);
    }

    Quaternion Convert(const Vector3D &axis, TFLOAT alpha)
    {
        Vector3D normalized = Normalize(axis);
        return convert(normalized, alpha);
    }

    Quaternion Convert(Axis3D axis, TFLOAT alpha)
    {
        Vector3D versor = Versor(axis);
        return convert(versor, alpha);
    }

    void Convert(const Quaternion &quaternion, Vector3D *axis, TFLOAT *alpha)
    {
        TFLOAT magnitude = Magnitude(quaternion);
        TFLOAT x = quaternion.X / magnitude;
	    TFLOAT y = quaternion.Y / magnitude;
	    TFLOAT z = quaternion.Z / magnitude;
        *axis = Vector3D(x, y, z);
        *alpha = acos(quaternion.W) * 2;
    }

    /*
     * Given the rotation around axis u, where u is a unit vector, by the angle a,
     * the quaternion describing the roation is:
     *     q = w + xi + yj + zk = w + (x, y, z) = cos(a/2) + u * sin(a/2)
     *
     */
    Quaternion convert(const Vector3D &normalized, TFLOAT alpha)
    {
        TFLOAT sin_a = sin(alpha / 2);
        TFLOAT cos_a = cos(alpha / 2);
        TFLOAT w = cos_a;
        TFLOAT x = normalized.X * sin_a;
        TFLOAT y = normalized.Y * sin_a;
        TFLOAT z = normalized.Z * sin_a;
        return Quaternion (x, y, z, w);
    }
} }
