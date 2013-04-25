#pragma once

#ifdef LINEARALGEBRA_EXPORTS
#define LINEARALGEBRA_API __declspec(dllexport)
#else
#define LINEARALGEBRA_API __declspec(dllimport)
#endif

#ifndef TFLOAT
#define TFLOAT float
#endif

#ifndef _ALLOW_KEYWORD_MACROS
#define _ALLOW_KEYWORD_MACROS
#endif

#ifndef alignas
#define alignas(x) __declspec(align(x))
#endif
