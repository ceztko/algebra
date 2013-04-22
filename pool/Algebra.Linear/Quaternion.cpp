#include <exception>

#include <cstring>

#include "Quaternion.h"

using namespace Algebra;
using namespace std;

Quaternion::Quaternion()
{
    W = 0;
    X = 0;
    Y = 0;
    Z = 0;
}

Quaternion::Quaternion(TFLOAT w, TFLOAT x, TFLOAT y, TFLOAT z)
{
    W = w;
    X = x;
    Y = y;
    Z = z;
}

Quaternion::Quaternion(const TFLOAT coeffs[])
{
    W = coeffs[0];
    X = coeffs[1];
    Y = coeffs[2];
    Z = coeffs[3];
}

TFLOAT Quaternion::operator [](int index) const
{
    switch (index)
    {
        case 0:
            return W;
        case 1:
            return X;
        case 2:
            return Y;
        case 3:
            return Z;
        default:
            throw exception("Invalid index");
    }
}

bool Algebra::operator ==(const Quaternion &p, const Quaternion &q)
{
    return p.W == q.W && p.X == q.X && p.Y == q.Y && p.Z == q.Z;
}

bool Algebra::operator !=(const Quaternion &p, const Quaternion &q)
{
    return p.W != q.W || p.X != q.X || p.Y != q.Y || p.Z != q.Z;
}

/*
 * Writing p = pw + pv, q = qw + qv, qr = p * q = wr + vr
 *     wr = pw * qw - pv * qv
 *     vr = pw * qv + qw * pv + pv ^ qv
 * where *,^ are respectively dot and cross products of the associated vectors
 */
Quaternion Algebra::operator *(const Quaternion &p, const Quaternion &q)
{
    TFLOAT pW = p.W;
    TFLOAT pX = p.X;
    TFLOAT pY = p.Y;
    TFLOAT pZ = p.Z;
    TFLOAT qW = q.W;
    TFLOAT qX = q.X;
    TFLOAT qY = q.Y;
    TFLOAT qZ = q.Z;

    return Quaternion(
        pW * qW - pX * qX - pY * qY - pZ * qZ,
        pW * qX + pX * qW + pY * qZ - pZ * qY,
	    pW * qY + pY * qW + pZ * qX - pX * qZ,
	    pW * qZ + pZ * qW + pX * qY - pY * qX);
}

Quaternion Algebra::operator *(const Quaternion &q, TFLOAT scalar)
{
    return Quaternion(q.W * scalar, q.X * scalar, q.Y * scalar, q.Z * scalar);
}

Quaternion Algebra::operator /(const Quaternion &q, TFLOAT scalar)
{
    return Quaternion(q.W / scalar, q.X / scalar, q.Y / scalar, q.Z / scalar);
}

