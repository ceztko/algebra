#pragma once

#ifdef LINEARALGEBRA_EXPORTS
#define LINEARALGEBRA_API __declspec(dllexport)
#else
#define LINEARALGEBRA_API __declspec(dllimport)
#endif

#ifndef TFLOAT
#define TFLOAT float
#endif
