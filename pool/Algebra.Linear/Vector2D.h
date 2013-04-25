#pragma once

#include <IPersistable.h>

#include "defines.h"
#include "Commons.h"

namespace Algebra { namespace Linear
{
    class LINEARALGEBRA_API alignas(16) Vector2D
		: Persistence::IPersistable<Vector2D>
    {
    public:
        union
        {
            TFLOAT _c[2];
            struct
            {
                TFLOAT X;
                TFLOAT Y;
            };
        };
        Vector2D();
        Vector2D(TFLOAT x, TFLOAT y);
        Vector2D(const TFLOAT coeffs[]);
        TFLOAT operator [](Axis2D axis) const;
        TFLOAT operator [](int index) const;
        operator const MatrixF();

		void Serialize(Persistence::SerializerStream &writer);
        void Deserialize(Persistence::DeserializerStream &reader);
        void Revise(Persistence::ReviseMode mode);
    };

    LINEARALGEBRA_API bool operator ==(const Vector2D &u, const Vector2D &v);
    LINEARALGEBRA_API bool operator !=(const Vector2D &u, const Vector2D &v);
    LINEARALGEBRA_API Vector2D operator +(const Vector2D &u);
    LINEARALGEBRA_API Vector2D operator -(const Vector2D &u);
    LINEARALGEBRA_API Vector2D operator +(const Vector2D &u, const Vector2D &v);
    LINEARALGEBRA_API Vector2D operator -(const Vector2D &u, const Vector2D &v);
    LINEARALGEBRA_API Vector2D operator *(const Vector2D &u, TFLOAT scalar);
    LINEARALGEBRA_API Vector2D operator /(const Vector2D &u, TFLOAT scalar);
    LINEARALGEBRA_API TFLOAT operator *(const Vector2D &u, const Vector2D &v);
    LINEARALGEBRA_API TFLOAT operator ^(const Vector2D &u, const Vector2D &v);
} }
