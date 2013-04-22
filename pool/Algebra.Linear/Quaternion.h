#pragma once

#include "defines.h"
#include "Commons.h"

namespace Algebra
{
    class LINEARALGEBRA_API Quaternion
    {
    public:
        TFLOAT W;
        TFLOAT X;
        TFLOAT Y;
        TFLOAT Z;
        Quaternion();
        Quaternion(TFLOAT w, TFLOAT x, TFLOAT y, TFLOAT z);
        Quaternion(const TFLOAT coeffs[]);
        TFLOAT operator [](int index) const;
    };

    LINEARALGEBRA_API bool operator ==(const Quaternion &p, const Quaternion &q);
    LINEARALGEBRA_API bool operator !=(const Quaternion &p, const Quaternion &q);
    LINEARALGEBRA_API Quaternion operator *(const Quaternion &p, const Quaternion &q);
    LINEARALGEBRA_API Quaternion operator *(const Quaternion &q, TFLOAT scalar);
    LINEARALGEBRA_API Quaternion operator /(const Quaternion &q, TFLOAT scalar);
}
