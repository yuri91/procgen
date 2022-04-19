#pragma once

#define Q_CORE_EXPORT
#define Q_GUI_EXPORT
#define Q_DECL_CONSTEXPR constexpr
#define Q_DECL_RELAXED_CONSTEXPR constexpr
#define Q_DECL_CONST_FUNCTION __attribute__((const))
#define Q_REQUIRED_RESULT [[nodiscard]]

typedef double qreal;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;

#include <cstring>
#include <vector>
#include <map>
