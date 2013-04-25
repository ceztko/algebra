#include <exception>

#include <cstring>

#include "Vector3D.h"

using namespace std;
using namespace Persistence;
using namespace Algebra::Linear;

Vector3D::Vector3D()
{
}

Vector3D::Vector3D(TFLOAT x, TFLOAT y, TFLOAT z)
{
    X = x;
    Y = y;
    Z = z;
}

Vector3D::Vector3D(const TFLOAT coeffs[])
{
    memcpy(_c, coeffs, sizeof(_c));
}

TFLOAT Vector3D::operator [](Axis3D axis) const
{
    switch (axis)
    {
        case AXIS3D_X:
            return X;
        case AXIS3D_Y:
            return Y;
        case AXIS3D_Z:
            return Z;
        default:
            throw exception("Invalid axis");
    }
}

TFLOAT Vector3D::operator [](int index) const
{
    switch (index)
    {
        case 0:
            return X;
        case 1:
            return Y;
        case 2:
            return Z;
        default:
            throw exception("Invalid index");
    }
}

Vector3D::operator const MatrixF()
{
    return MatrixF(_c, Dims(1, 3), sizeof(Vector3D));
}

bool Algebra::Linear::operator ==(const Vector3D &u, const Vector3D &v)
{
    return u.X == v.X && u.Y == v.Y && u.Z == v.Z;
}

bool Algebra::Linear::operator !=(const Vector3D &u, const Vector3D &v)
{
    return u.X != v.X || u.Y != v.Y || u.Z != v.Z;
}

Vector3D Algebra::Linear::operator +(const Vector3D &u)
{
    return Vector3D(u.X, u.Y, u.Z);
}

Vector3D Algebra::Linear::operator -(const Vector3D &u)
{
    return Vector3D(-u.X, -u.Y, -u.Z);
}

Vector3D Algebra::Linear::operator +(const Vector3D &u, const Vector3D &v)
{
    return Vector3D(u.X + v.X, u.Y + v.Y, u.Z + v.Z);
}

Vector3D Algebra::Linear::operator -(const Vector3D &u, const Vector3D &v)
{
    return Vector3D(u.X - v.X, u.Y - v.Y, u.Z - v.Z);
}

Vector3D Algebra::Linear::operator *(const Vector3D &u, TFLOAT scalar)
{
    return Vector3D(u.X * scalar, u.Y * scalar, u.Z * scalar);
}

Vector3D Algebra::Linear::operator /(const Vector3D &u, TFLOAT scalar)
{
    return Vector3D(u.X / scalar, u.Y / scalar, u.Z * scalar);
}

/*
 * Giving a the angle between u and v:
 *     u * v = |u| * |v| * cos(a)
 * It corresponds to the orthogonal projection of u upon v
 */
TFLOAT Algebra::Linear::operator *(const Vector3D &u, const Vector3D &v)
{
    return u.X * v.X + u.Y * v.Y + u.Z * v.Z;
}

/*
 * Giving a the angle between u and v:
 *     u ^ v = n * |u| * |v| * sin(a)
 * Where n is the unit vector that results from the right-hand rule applied to
 * u and v.
 *
 * The magnitude of u ^ v is given by:
 *     |u ^ v| = |u| * |v| * sin(a)
 * It corresponds to the area of the parallelogram composed by the vectors u
 * and v.
 */
Vector3D Algebra::Linear::operator ^(const Vector3D &u, const Vector3D &v)
{
    TFLOAT uX = u.X;
    TFLOAT uY = u.Y;
    TFLOAT uZ = u.Z;
    TFLOAT vX = v.X;
    TFLOAT vY = v.Y;
    TFLOAT vZ = v.Z;

    return Vector3D(
        uY * vZ - uZ * vY,
        uZ * vX - uX * vZ,
        uX * vY - uY * vX);
}

void Vector3D::Serialize(SerializerStream &writer)
{
	writer.WriteElement(_c[0]);
	writer.WriteElement(_c[1]);
	writer.WriteElement(_c[2]);
}

void Vector3D::Deserialize(DeserializerStream &reader)
{
	reader.ReadElementAs(&_c[0]);
	reader.ReadElementAs(&_c[1]);
	reader.ReadElementAs(&_c[2]);
}

void Vector3D::Revise(ReviseMode mode)
{
}