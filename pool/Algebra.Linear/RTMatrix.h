#pragma once

#include "defines.h"
#include "Commons.h"
#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix.h"

namespace Algebra { namespace Linear
{
    class LINEARALGEBRA_API alignas(16) RTMatrix
    {
    private:
        TFLOAT _M[4][4];
        static bool validate(const TFLOAT m[]);
        static bool validateRotation(const TFLOAT rotation[]);
        void toIdentity();
		void normalizeLastRow();
    public:
        RTMatrix();
        RTMatrix(const TFLOAT m[]);
        RTMatrix(const TFLOAT rotation[], const TFLOAT translation[]);
        RTMatrix(const RTMatrix &matrix);
        void Assign(const TFLOAT m[]);
        void Assign(const TFLOAT rotation[], const TFLOAT translation[]);
        void GetRotation(TFLOAT rotation[]);
        void GetTranslation(TFLOAT translation[]);
        void SetRotation(EulerAnglesOrder order, TFLOAT alphax, TFLOAT alphay,
            TFLOAT alphaz);
        void SetRotation(const Vector3D &axis, TFLOAT alpha);
        void SetRotation(Axis3D axis, TFLOAT alpha);
        void SetRotation(const Quaternion &quaternion);
        void SetTranslation(const Vector3D &translation);
        void SetTranslation(Axis3D axis, TFLOAT delta);
        TFLOAT GetDeterminant() const;
        void Invert();
        void PreMultiply(const RTMatrix &other);
        void PostMultiply(const RTMatrix &other);
        void ToIdentity();
        bool IsIdentity() const;
        const TFLOAT * operator [](int row) const;
        bool operator ==(const RTMatrix &other) const;
        bool operator !=(const RTMatrix &other) const;
        operator const MatrixF();
    };

    LINEARALGEBRA_API RTMatrix operator *(const RTMatrix &A, const RTMatrix &B);
    LINEARALGEBRA_API Vector3D operator *(const RTMatrix &A, const Vector3D &v);
} }
