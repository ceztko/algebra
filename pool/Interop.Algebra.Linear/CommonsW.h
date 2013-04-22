#pragma once

#include <Commons.h>

using namespace System;
using namespace Algebra::Linear;

namespace Interop { namespace Algebra { namespace Linear
{
    public enum class Axis2D
    {
        X = 0,
        Y
    };

    public enum class Axis3D
    {
        X = 0,
        Y,
        Z
    };

    public enum class Direction
    {
        CLOCKWISE = 0,
        COUNTERCLOCKWISE
    };

    public enum class PolarCoord
    {
        RHO = 0,
        PHI
    };

    public enum class CylindricalCoord
    {
        RHO = 0,
        PHI,
        Z
    };

    public enum class SphericalCoord
    {
        RHO = 0,
        PHI,
        THETA
    };
} } }
