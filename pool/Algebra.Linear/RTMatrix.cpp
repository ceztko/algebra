#include <exception>

#include <cstring>
#include <cmath>

#include "RTMatrix.h"
#include "Operations.h"

using namespace Algebra;
using namespace Algebra::Linear;
using namespace std;

RTMatrix::RTMatrix()
{
    toIdentity();
	normalizeLastRow();
}

RTMatrix::RTMatrix(const TFLOAT m[])
{
    if (!validate(m))
        throw exception("Invalid RT matrix");

    Assign(m);
	normalizeLastRow();
}

RTMatrix::RTMatrix(const TFLOAT rotation[], const TFLOAT translation[])
{
    Assign(rotation, translation);
	normalizeLastRow();
}

RTMatrix::RTMatrix(const RTMatrix &matrix)
{
    memcpy(this->_M, matrix._M, sizeof(_M));
}

void RTMatrix::Assign(const TFLOAT rotation[], const TFLOAT translation[])
{
    if (rotation != NULL)
    {
        if (!validateRotation(rotation))
            throw exception("Invalid rotation");

        _M[0][0] = rotation[0];
        _M[0][1] = rotation[1];
        _M[0][2] = rotation[2];
        _M[1][0] = rotation[3];
        _M[1][1] = rotation[4];
        _M[1][2] = rotation[5];
        _M[2][0] = rotation[6];
        _M[2][1] = rotation[7];
        _M[2][2] = rotation[8];
    }
    if (translation != NULL)
    {
        _M[0][3] = translation[0];
        _M[1][3] = translation[1];
        _M[2][3] = translation[2];
    }
}

void RTMatrix::Assign(const TFLOAT m[])
{
    if (!validate(m))
        throw exception("Invalid RT matrix");

    memcpy(_M, m, sizeof(TFLOAT) * 12);
}

void RTMatrix::GetRotation(TFLOAT rotation[])
{
    rotation[0] = _M[0][0];
    rotation[1] = _M[0][1];
    rotation[2] = _M[0][2];
    rotation[3] = _M[1][0];
    rotation[4] = _M[1][1];
    rotation[5] = _M[1][2];
    rotation[6] = _M[2][0];
    rotation[7] = _M[2][1];
    rotation[8] = _M[2][2];
}

void RTMatrix::GetTranslation(TFLOAT translation[])
{
    translation[0] = _M[0][3];
    translation[1] = _M[1][3];
    translation[2] = _M[2][3];
}

/*
 * This is really just optimized matrices multiplications
 */
void RTMatrix::SetRotation(EulerAnglesOrder order, TFLOAT alphax, TFLOAT alphay,
    TFLOAT alphaz)
{
    TFLOAT A = cos(alphax);
    TFLOAT B = sin(alphax);
    TFLOAT C = cos(alphay);
    TFLOAT D = sin(alphay);
    TFLOAT E = cos(alphaz);
    TFLOAT F = sin(alphaz);
    switch (order)
    {
        case ORDER_XYZ:
        {
            TFLOAT AE =  A * E;
            TFLOAT AF =  A * F;
            TFLOAT BE =  B * E;
            TFLOAT BF =  B * F;
            _M[0][0]  =  C * E;
            _M[0][1]  = -C * F;
            _M[0][2]  =  D;
            _M[1][0]  =  AF + BE * D;
            _M[1][1]  =  AE - BF * D;
            _M[1][2]  = -B * C;
            _M[2][0]  =  BF - AE * D;
            _M[2][1]  =  BE + AF * D;
            _M[2][2]  =  A * C;
            break;
        }
        case ORDER_XZY:
        {
            TFLOAT AC =  A * C;
            TFLOAT AD =  A * D;
            TFLOAT BC =  B * C;
            TFLOAT BD =  B * D;
            _M[0][0]  =  C * E;
            _M[0][1]  = -F;
            _M[0][2]  =  D * E;
            _M[1][0]  =  BD + AC * F;
            _M[1][1]  =  A * E;
            _M[1][2]  =  AD * F - BC;
            _M[2][0]  =  BC * F - AD;
            _M[2][1]  =  B * E;
            _M[2][2]  =  AC + BD * F;
            break;
        }
        case ORDER_YXZ:
        {
            TFLOAT CE =  C * E;
            TFLOAT CF =  C * F;
            TFLOAT DE =  D * E;
            TFLOAT DF =  D * F;
            _M[0][0]  =  CE + B * DF;
            _M[0][1]  =  B * DE - CF;
            _M[0][2]  =  A * D;
            _M[1][0]  =  A * F;
            _M[1][1]  =  A * E;
            _M[1][2]  = -B;
            _M[2][0]  =  B * CF - DE;
            _M[2][1]  =  DF + B * CE;
            _M[2][2]  =  A * C;
            break;
        }
        case ORDER_YZX:
        {
            TFLOAT AC =  A * C;
            TFLOAT AD =  A * D;
            TFLOAT BC =  B * C;
            TFLOAT BD =  B * D;
            _M[0][0]  =  C * E;
            _M[0][1]  =  BD - AC * F;
            _M[0][2]  =  AD + BC * F;
            _M[1][0]  =  F;
            _M[1][1]  =  A * E;
            _M[1][2]  = -B * E;
            _M[2][0]  = -D * E;
            _M[2][1]  =  BC + AD * F;
            _M[2][2]  =  AC - BD * F;
            break;
        }
        case ORDER_ZXY:
        {
            TFLOAT CE =  C * E;
            TFLOAT CF =  C * F;
            TFLOAT DE =  D * E;
            TFLOAT DF =  D * F;
            _M[0][0]  =  CE - B * DF;
            _M[0][1]  = -A * F;
            _M[0][2]  =  DE + B * CF;
            _M[1][0]  =  CF + B * DE;
            _M[1][1]  =  A * E;
            _M[1][2]  =  DF - B * CE;
            _M[2][0]  =  A * D;
            _M[2][1]  =  B;
            _M[2][2]  =  A * C;
            break;
        }
        case ORDER_ZYX:
        {
            TFLOAT AE =  A * E;
            TFLOAT AF =  A * F;
            TFLOAT BE =  B * E;
            TFLOAT BF =  B * F;
            _M[0][0]  =  C * E;
            _M[0][1]  =  BE * D - AF;
            _M[0][2]  =  BF + AE * D;
            _M[1][0]  =  C * F;
            _M[1][1]  =  AE + BF * D;
            _M[1][2]  =  AF * D - BE;
            _M[2][0]  = -D;
            _M[2][1]  =  B * C;
            _M[2][2]  =  A * C;
            break;
        }
    }
}

void RTMatrix::SetRotation(Axis3D axis, TFLOAT alpha)
{
    TFLOAT sina = sin(alpha);
    TFLOAT cosa = cos(alpha);
    switch (axis)
    {
        case AXIS3D_X:
            _M[0][0] = 1;
            _M[0][1] = 0;
            _M[0][2] = 0;
            _M[1][0] = 0;
            _M[1][1] = cosa;
            _M[1][2] = -sina;
            _M[2][0] = 0;
            _M[2][1] = sina;
            _M[2][2] = cosa;
            break;
        case AXIS3D_Y:
            _M[0][0] = cosa;
            _M[0][1] = 0;
            _M[0][2] = sina;
            _M[1][0] = 0;
            _M[1][1] = 1;
            _M[1][2] = 0;
            _M[2][0] = -sina;
            _M[2][1] = 0;
            _M[2][2] = cosa;
            break;
        case AXIS3D_Z:
            _M[0][0] = cosa;
            _M[0][1] = -sina;
            _M[0][2] = 0;
            _M[1][0] = sina;
            _M[1][1] = cosa;
            _M[1][2] = 0;
            _M[2][0] = 0;
            _M[2][1] = 0;
            _M[2][2] = 0;
            break;
    }
}

void RTMatrix::SetRotation(const Vector3D &axis, TFLOAT alpha)
{
    Quaternion quaternion = Convert(axis, alpha);
    SetRotation(quaternion);
}

void RTMatrix::SetRotation(const Quaternion &q)
{
    TFLOAT x = q.X;
    TFLOAT y = q.Y;
    TFLOAT z = q.Z;
    TFLOAT w = q.W;

    TFLOAT xx = x * x;
    TFLOAT xy = x * y;
    TFLOAT xz = x * z;
    TFLOAT xw = x * w;
    TFLOAT yy = y * y;
    TFLOAT yz = y * z;
    TFLOAT yw = y * w;
    TFLOAT zz = z * z;
    TFLOAT zw = z * w;

    _M[0][0] = 1 - 2 * (yy + zz);
    _M[0][1] =     2 * (xy - zw);
    _M[0][2] =     2 * (xz + yw);
    _M[1][0] =     2 * (xy + zw);
    _M[1][1] = 1 - 2 * (xx + zz);
    _M[1][2] =     2 * (yz - xw);
    _M[2][0] =     2 * (xz - yw);
    _M[2][1] =     2 * (yz + xw);
    _M[2][2] = 1 - 2 * (xx + yy);
}

void RTMatrix::SetTranslation(const Vector3D &translation)
{
    _M[0][3] = translation.X;
    _M[1][3] = translation.Y;
    _M[2][3] = translation.Z;
}

void RTMatrix::SetTranslation(Axis3D axis, TFLOAT value)
{
    switch (axis)
    {
        case AXIS3D_X:
            _M[0][3] = value;
            break;
        case AXIS3D_Y:
            _M[1][3] = value;
            break;
        case AXIS3D_Z:
            _M[2][3] = value;
            break;
    }
}

TFLOAT RTMatrix::GetDeterminant() const
{
    TFLOAT ret =
        - _M[0][2] * _M[1][1] * _M[2][0]
        + _M[0][1] * _M[1][2] * _M[2][0]
        + _M[0][2] * _M[1][0] * _M[2][1]
        - _M[0][0] * _M[1][2] * _M[2][1]
        - _M[0][1] * _M[1][0] * _M[2][2]
        + _M[0][0] * _M[1][1] * _M[2][2];
    return ret;
}

void RTMatrix::Invert()
{
    TFLOAT determinant = GetDeterminant();

    _M[0][0] = (- _M[1][2] * _M[2][1] + _M[1][1] * _M[2][2]) / determinant;
    _M[0][1] = (  _M[0][1] * _M[2][1] - _M[0][1] * _M[2][2]) / determinant;
    _M[0][2] = (- _M[0][2] * _M[1][1] + _M[0][1] * _M[1][2]) / determinant;
    _M[0][3] = (  _M[0][3] * _M[1][2] * _M[2][1]
                - _M[0][2] * _M[1][3] * _M[2][1]
                - _M[0][3] * _M[1][1] * _M[2][2]
                + _M[0][1] * _M[1][3] * _M[2][2]
                + _M[0][2] * _M[1][1] * _M[2][3]
                - _M[0][1] * _M[1][2] * _M[2][3]) / determinant;
    _M[1][0] = (  _M[1][2] * _M[2][0] - _M[1][0] * _M[2][2]) / determinant;
    _M[1][1] = (- _M[0][2] * _M[2][0] + _M[0][0] * _M[2][2]) / determinant;
    _M[1][2] = (  _M[0][2] * _M[1][0] - _M[0][0] * _M[1][2]) / determinant;
    _M[1][3] = (  _M[0][2] * _M[1][3] * _M[2][0]
                - _M[0][3] * _M[1][2] * _M[2][0]
                + _M[0][3] * _M[1][0] * _M[2][2]
                - _M[0][0] * _M[1][3] * _M[2][2]
                - _M[0][2] * _M[1][0] * _M[2][3]
                + _M[0][0] * _M[1][2] * _M[2][3]) / determinant;
    _M[2][0] = (- _M[1][1] * _M[2][0] + _M[1][0] * _M[2][1]) / determinant;
    _M[2][1] = (  _M[0][1] * _M[2][0] - _M[0][0] * _M[2][1]) / determinant;
    _M[2][2] = (- _M[0][1] * _M[1][0] + _M[0][0] * _M[1][1]) / determinant;
    _M[2][3] = (  _M[0][3] * _M[1][1] * _M[2][0]
                - _M[0][1] * _M[1][3] * _M[2][0]
                - _M[0][3] * _M[1][0] * _M[2][1]
                + _M[0][0] * _M[1][3] * _M[2][1]
                + _M[0][1] * _M[1][0] * _M[2][3]
                - _M[0][0] * _M[1][1] * _M[2][3]) / determinant;
}

void RTMatrix::PreMultiply(const RTMatrix &o)
{
    TFLOAT tmp[3][4];

    tmp[0][0] = o._M[0][0] * this->_M[0][0] + o._M[0][1] * this->_M[1][0] + o._M[0][2] * this->_M[2][0];
    tmp[0][1] = o._M[0][0] * this->_M[0][1] + o._M[0][1] * this->_M[1][1] + o._M[0][2] * this->_M[2][1];
    tmp[0][2] = o._M[0][0] * this->_M[0][2] + o._M[0][1] * this->_M[1][2] + o._M[0][2] * this->_M[2][2];
    tmp[0][3] = o._M[0][0] * this->_M[0][3] + o._M[0][1] * this->_M[1][3] + o._M[0][2] * this->_M[2][3] + o._M[0][3];
    tmp[1][0] = o._M[1][0] * this->_M[0][0] + o._M[1][1] * this->_M[1][0] + o._M[1][2] * this->_M[2][0];
    tmp[1][1] = o._M[1][0] * this->_M[0][1] + o._M[1][1] * this->_M[1][1] + o._M[1][2] * this->_M[2][1];
    tmp[1][2] = o._M[1][0] * this->_M[0][2] + o._M[1][1] * this->_M[1][2] + o._M[1][2] * this->_M[2][2];
    tmp[1][3] = o._M[1][0] * this->_M[0][3] + o._M[1][1] * this->_M[1][3] + o._M[1][2] * this->_M[2][3] + o._M[1][3];
    tmp[2][0] = o._M[2][0] * this->_M[0][0] + o._M[2][1] * this->_M[1][0] + o._M[2][2] * this->_M[2][0];
    tmp[2][1] = o._M[2][0] * this->_M[0][1] + o._M[2][1] * this->_M[1][1] + o._M[2][2] * this->_M[2][1];
    tmp[2][2] = o._M[2][0] * this->_M[0][2] + o._M[2][1] * this->_M[1][2] + o._M[2][2] * this->_M[2][2];
    tmp[2][3] = o._M[2][0] * this->_M[0][3] + o._M[2][1] * this->_M[1][3] + o._M[2][2] * this->_M[2][3] + o._M[2][3];

    memcpy(_M, tmp, sizeof(_M));
}

void RTMatrix::PostMultiply(const RTMatrix &o)
{
    TFLOAT tmp[3][4];

    tmp[0][0] = this->_M[0][0] * o._M[0][0] + this->_M[0][1] * o._M[1][0] + this->_M[0][2] * o._M[2][0];
    tmp[0][1] = this->_M[0][0] * o._M[0][1] + this->_M[0][1] * o._M[1][1] + this->_M[0][2] * o._M[2][1];
    tmp[0][2] = this->_M[0][0] * o._M[0][2] + this->_M[0][1] * o._M[1][2] + this->_M[0][2] * o._M[2][2];
    tmp[0][3] = this->_M[0][0] * o._M[0][3] + this->_M[0][1] * o._M[1][3] + this->_M[0][2] * o._M[2][3] + this->_M[0][3];
    tmp[1][0] = this->_M[1][0] * o._M[0][0] + this->_M[1][1] * o._M[1][0] + this->_M[1][2] * o._M[2][0];
    tmp[1][1] = this->_M[1][0] * o._M[0][1] + this->_M[1][1] * o._M[1][1] + this->_M[1][2] * o._M[2][1];
    tmp[1][2] = this->_M[1][0] * o._M[0][2] + this->_M[1][1] * o._M[1][2] + this->_M[1][2] * o._M[2][2];
    tmp[1][3] = this->_M[1][0] * o._M[0][3] + this->_M[1][1] * o._M[1][3] + this->_M[1][2] * o._M[2][3] + this->_M[1][3];
    tmp[2][0] = this->_M[2][0] * o._M[0][0] + this->_M[2][1] * o._M[1][0] + this->_M[2][2] * o._M[2][0];
    tmp[2][1] = this->_M[2][0] * o._M[0][1] + this->_M[2][1] * o._M[1][1] + this->_M[2][2] * o._M[2][1];
    tmp[2][2] = this->_M[2][0] * o._M[0][2] + this->_M[2][1] * o._M[1][2] + this->_M[2][2] * o._M[2][2];
    tmp[2][3] = this->_M[2][0] * o._M[0][3] + this->_M[2][1] * o._M[1][3] + this->_M[2][2] * o._M[2][3] + this->_M[2][3];

    memcpy(_M, tmp, sizeof(_M));
}

void RTMatrix::ToIdentity()
{
    toIdentity();
}

bool RTMatrix::IsIdentity() const
{
    for (int itr = 0; itr < 3; itr++)
    {
        for (int itc = 0; itc < 4; itc++)
        {
            if (itc == itr)
            {
                if (_M[itr][itc] != 1)
                    return false;
            }
            else
            {
                if (_M[itr][itc] != 0)
                    return false;
            }
        }
    }
    return true;
}

const TFLOAT * RTMatrix::operator [](int row) const
{
    return _M[row];
}

bool RTMatrix::operator ==(const RTMatrix &other) const
{
    for (int itr = 0; itr < 3; itr++)
    {
        for (int itc = 0; itc < 4; itc++)
        {
            if (this->_M[itr][itc] != other._M[itr][itc])
                return false;
        }
    }

    return true;
}

bool RTMatrix::operator !=(const RTMatrix &other) const
{
    for (int itr = 0; itr < 3; itr++)
    {
        for (int itc = 0; itc < 4; itc++)
        {
            if (this->_M[itr][itc] != other._M[itr][itc])
                return true;
        }
    }

    return false;
}

void RTMatrix::toIdentity()
{
    _M[0][0] = 1;
    _M[0][1] = 0;
    _M[0][2] = 0;
    _M[0][3] = 0;
    _M[1][0] = 0;
    _M[1][1] = 1;
    _M[1][2] = 0;
    _M[1][3] = 0;
    _M[2][0] = 0;
    _M[2][1] = 0;
    _M[2][2] = 1;
    _M[2][3] = 0;
}

void RTMatrix::normalizeLastRow()
{
    _M[3][0] = 0;
    _M[3][1] = 0;
    _M[3][2] = 0;
    _M[3][3] = 1;
}

bool RTMatrix::validate(const TFLOAT m[])
{
    // TODO: should validate raw coefficients
    return true;
}

bool RTMatrix::validateRotation(const TFLOAT rotation[])
{
    // TODO: should validate rotation coefficients
    return true;
}

RTMatrix Algebra::Linear::operator *(const RTMatrix &A, const RTMatrix &B)
{
    RTMatrix ret(A);
    ret.PostMultiply(B);
    return ret;
}

Vector3D Algebra::Linear::operator *(const RTMatrix &A, const Vector3D &v)
{
    TFLOAT x = v.X;
    TFLOAT y = v.Y;
    TFLOAT z = v.Z;

    TFLOAT coords[3];
    coords[0] = A[0][0] * x + A[0][1] * y + A[0][2] * z + A[0][3];
    coords[1] = A[1][0] * x + A[1][1] * y + A[1][2] * z + A[1][3];
    coords[2] = A[2][0] * x + A[2][1] * y + A[2][2] * z + A[2][3];

    return Vector3D(coords);
}

RTMatrix::operator const MatrixF()
{
    return MatrixF(_M[0], Dims(4, 4), 4 * sizeof(TFLOAT));
}
