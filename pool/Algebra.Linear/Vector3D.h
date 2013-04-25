#pragma once

#include <IPersistable.h>

#include "defines.h"
#include "Commons.h"

namespace Algebra { namespace Linear
{
    class LINEARALGEBRA_API  alignas(16) Vector3D
		: Persistence::IPersistable<Vector3D>
    {
    public:
        union
        {
            TFLOAT _c[3];
            struct
            {
                TFLOAT X;
                TFLOAT Y;
                TFLOAT Z;
            };
        };
        Vector3D();
        Vector3D(TFLOAT x, TFLOAT y, TFLOAT z);
        Vector3D(const TFLOAT coeffs[]);
        TFLOAT operator [](Axis3D axis) const;
        TFLOAT operator [](int index) const;
        operator const MatrixF();

		void Serialize(Persistence::SerializerStream &writer);
        void Deserialize(Persistence::DeserializerStream &reader);
        void Revise(Persistence::ReviseMode mode);
    };

    LINEARALGEBRA_API bool operator ==(const Vector3D &u, const Vector3D &v);
    LINEARALGEBRA_API bool operator !=(const Vector3D &u, const Vector3D &v);
    LINEARALGEBRA_API Vector3D operator +(const Vector3D &u);
    LINEARALGEBRA_API Vector3D operator -(const Vector3D &u);
    LINEARALGEBRA_API Vector3D operator +(const Vector3D &u, const Vector3D &v);
    LINEARALGEBRA_API Vector3D operator -(const Vector3D &u, const Vector3D &v);
    LINEARALGEBRA_API Vector3D operator *(const Vector3D &u, TFLOAT scalar);
    LINEARALGEBRA_API Vector3D operator /(const Vector3D &u, TFLOAT scalar);
    LINEARALGEBRA_API TFLOAT operator *(const Vector3D &u, const Vector3D &v);
    LINEARALGEBRA_API Vector3D operator ^(const Vector3D &u, const Vector3D &v);
} }
