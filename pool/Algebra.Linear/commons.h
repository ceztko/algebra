#pragma once

#include "defines.h"

#include "Matrix.h"

namespace Algebra { namespace Linear
{
    typedef Matrix<TFLOAT> MatrixF;

    enum Axis2D
    {
        AXIS2D_X = 0,
        AXIS2D_Y
    };

    enum Axis3D
    {
        AXIS3D_X = 0,
        AXIS3D_Y,
        AXIS3D_Z
    };

    enum Direction
    {
        DIR_CLOCKWISE = 0,
        DIR_COUNTERCLOCKWISE
    };

    enum EulerAnglesOrder
    {
        ORDER_XYZ = 0,
        ORDER_XZY,
        ORDER_YXZ,
        ORDER_YZX,
        ORDER_ZXY,
        ORDER_ZYX
    };
} }
