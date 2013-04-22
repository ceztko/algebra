#include <vector>

#include "Commons.h"
#include "Vector2D.h"
#include "Vector3D.h"

namespace Algebra { namespace Linear
{
    template class Matrix<TFLOAT>;

    template Matrix<TFLOAT>::Matrix(std::vector<Vector2D> &vec);
    template Matrix<TFLOAT>::Matrix(std::vector<Vector3D> &vec);
    template bool operator ==(const Matrix<TFLOAT> &A, const Matrix<TFLOAT> &B);
    template bool operator !=(const Matrix<TFLOAT> &A, const Matrix<TFLOAT> &B);
    template bool operator ==(const Matrix<TFLOAT> &A, TFLOAT scalar);
    template bool operator !=(const Matrix<TFLOAT> &A, TFLOAT scalar);
    template Matrix<TFLOAT> & operator +=(Matrix<TFLOAT> &A, const Matrix<TFLOAT> &B);
    template Matrix<TFLOAT> & operator +=(Matrix<TFLOAT> &A, TFLOAT scalar);
    template Matrix<TFLOAT> & operator -=(Matrix<TFLOAT> &A, const Matrix<TFLOAT> &B);
    template Matrix<TFLOAT> & operator -=(Matrix<TFLOAT> &A, TFLOAT scalar);
    template Matrix<TFLOAT> & operator *=(Matrix<TFLOAT> &A, const Matrix<TFLOAT> &B);
    template Matrix<TFLOAT> & operator *=(Matrix<TFLOAT> &A, TFLOAT scalar);
    template Matrix<TFLOAT> & operator /=(Matrix<TFLOAT> &A, TFLOAT scalar);
    template Matrix<TFLOAT> operator +<TFLOAT>(const Matrix<TFLOAT> &A, const Matrix<TFLOAT> &B);
    template Matrix<TFLOAT> operator +<TFLOAT>(const Matrix<TFLOAT> &A, TFLOAT scalar);
    template Matrix<TFLOAT> operator -<TFLOAT>(const Matrix<TFLOAT> &A, const Matrix<TFLOAT> &B);
    template Matrix<TFLOAT> operator -<TFLOAT>(const Matrix<TFLOAT> &A, TFLOAT scalar);
    template Matrix<TFLOAT> operator *<TFLOAT>(const Matrix<TFLOAT> &A, const Matrix<TFLOAT> &B);
    template Matrix<TFLOAT> operator *<TFLOAT>(TFLOAT scalar, const Matrix<TFLOAT> &A);
    template Matrix<TFLOAT> operator *<TFLOAT>(const Matrix<TFLOAT> &A, TFLOAT scalar);
    template Matrix<TFLOAT> operator /<TFLOAT>(const Matrix<TFLOAT> &A, TFLOAT scalar);
    template Matrix<TFLOAT> Transpose(const Matrix<TFLOAT> &A);
    template Matrix<TFLOAT> Invert(const Matrix<TFLOAT> &A);
    template TFLOAT Determinant(const Matrix<TFLOAT> &A);
    template void HorizSum<TFLOAT>(Matrix<TFLOAT> &A, const Matrix<TFLOAT> &v);
    template void HorizSub<TFLOAT>(Matrix<TFLOAT> &A, const Matrix<TFLOAT> &v);
    template void HorizMul<TFLOAT>(Matrix<TFLOAT> &A, const Matrix<TFLOAT> &v);
    template void HorizDiv<TFLOAT>(Matrix<TFLOAT> &A, const Matrix<TFLOAT> &v);
    template Matrix<TFLOAT> HorizSumEd<TFLOAT>(const Matrix<TFLOAT> &A, const Matrix<TFLOAT> &v);
    template Matrix<TFLOAT> HorizSubEd<TFLOAT>(const Matrix<TFLOAT> &A, const Matrix<TFLOAT> &v);
    template Matrix<TFLOAT> HorizMulEd<TFLOAT>(const Matrix<TFLOAT> &A, const Matrix<TFLOAT> &v);
    template Matrix<TFLOAT> HorizDivEd<TFLOAT>(const Matrix<TFLOAT> &A, const Matrix<TFLOAT> &v);
} }
