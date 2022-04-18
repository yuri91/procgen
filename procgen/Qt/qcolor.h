#pragma once

#include "defs.h"

class Q_GUI_EXPORT QColor
{
public:
    Q_DECL_CONSTEXPR QColor() noexcept
        : r(0), g(0), b(0), a(0)
    {}
    Q_DECL_CONSTEXPR QColor(int r, int g, int b, int a = 255) noexcept
        : r(r), g(g), b(b), a(a)
    {}

    int red() const noexcept;
    int green() const noexcept;
    int blue() const noexcept;

    bool operator==(const QColor &c) const noexcept;
    bool operator!=(const QColor &c) const noexcept;
    void setAlpha(qreal a);

private:
    uchar r;
    uchar g;
    uchar b;
    uchar a;
};
