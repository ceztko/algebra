#pragma once

#include "defines.h"

namespace Algebra { namespace Linear
{
    struct LINEARALGEBRA_API Dims
    {
    public:
        Dims();
        Dims(int rows, int cols);
        int Rows;
        int Cols;
    };
} }
