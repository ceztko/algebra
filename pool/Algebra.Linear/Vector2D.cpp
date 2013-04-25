#include <exception>

#include <cstring>

#include "Vector2D.h"

using namespace std;
using namespace Persistence;
using namespace Algebra::Linear;

Vector2D::Vector2D()
{ }

Vector2D::Vector2D(TFLOAT x, TFLOAT y)
{
    X = x;
    Y = y;
}

Vector2D::Vector2D(const TFLOAT coeffs[])
{
    memcpy(_c, coeffs, sizeof(_c));
}

TFLOAT Vector2D::operator [](Axis2D axis) const
{
    switch (axis)
    {
        case AXIS2D_X:
            return X;
        case AXIS2D_Y:
            return Y;
        default:
            throw exception("Invalid axis");
    }
}

TFLOAT Vector2D::operator [](int index) const
{
    switch (index)
    {
        case 0:
            return X;
        case 1:
            return Y;
        default:
            throw exception("Invalid index");
    }
}

Vector2D::operator const MatrixF()
{
    return MatrixF(_c, Dims(1, 2), sizeof(Vector2D));
}

bool Algebra::Linear::operator ==(const Vector2D &u, const Vector2D &v)
{
    return u.X == v.X && u.Y == v.Y;
}

bool Algebra::Linear::operator !=(const Vector2D &u, const Vector2D &v)
{
    return u.X != v.X || u.Y != v.Y;
}

Vector2D Algebra::Linear::operator +(const Vector2D &u)
{
    return Vector2D(u.X, u.Y);
}

Vector2D Algebra::Linear::operator -(const Vector2D &u)
{
    return Vector2D(-u.X, -u.Y);
}

Vector2D Algebra::Linear::operator +(const Vector2D &u, const Vector2D &v)
{
    return Vector2D(u.X + v.X, u.Y + v.Y);
}

Vector2D Algebra::Linear::operator -(const Vector2D &u, const Vector2D &v)
{
     return Vector2D(u.X - v.X, u.Y - v.Y);
}

Vector2D Algebra::Linear::operator *(const Vector2D &u, TFLOAT scalar)
{
    return Vector2D(u.X * scalar, u.Y * scalar);
}

Vector2D Algebra::Linear::operator /(const Vector2D &u, TFLOAT scalar)
{
    return Vector2D(u.X / scalar, u.Y / scalar);
}

/*
 * Given a the angle between u and v:
 *     u * v = |u| * |v| * cos(a)
 * It corresponds to the orthogonal projection of u upon v.
 */
TFLOAT Algebra::Linear::operator *(const Vector2D &u, const Vector2D &v)
{
    return u.X * v.X + u.Y * v.Y;
}

/*
 * Cross product vector in 2D returns the magnitude of the orthogonal vector
 * resulted from cross product operation as it were 3D space.
 * Given a the angle between u and v:
 *     u ^ v = |u| * |v| * sin(a)
 * It corresponds to the area of the parallelogram composed by the vectors u
 * and v.
 */
TFLOAT Algebra::Linear::operator ^(const Vector2D &u, const Vector2D &v)
{
    return u.X * v.X - u.Y * v.Y;
}

void Vector2D::Serialize(SerializerStream &writer)
{
	writer.WriteElement(_c[0]);
	writer.WriteElement(_c[1]);
}

void Vector2D::Deserialize(DeserializerStream &reader)
{
	reader.ReadElementAs(&_c[0]);
	reader.ReadElementAs(&_c[1]);
}

void Vector2D::Revise(ReviseMode mode)
{
}