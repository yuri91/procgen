#pragma once

#include "defs.h"
#include <string>
#include <tuple>

class Q_GUI_EXPORT QColor
{
public:
    Q_DECL_CONSTEXPR QColor() noexcept
        : r(0), g(0), b(0), a(0)
    {}
    Q_DECL_CONSTEXPR QColor(int r, int g, int b, int a = 255) noexcept
        : r(r), g(g), b(b), a(a)
    {}

    int red() const noexcept {
        return r;
    }
    int green() const noexcept {
        return g;
    }
    int blue() const noexcept {
        return b;
    }
    int alpha() const noexcept {
        return a;
    }

    bool operator==(const QColor &c) const noexcept {
        return std::tie(r,g,b,a) == std::tie(c.r,c.g,c.b,c.a);
    }
    bool operator!=(const QColor &c) const noexcept {
        return ! (*this == c);
    }
    void setAlpha(qreal a) {
        this->a = a;
    }

    std::string toString() const {
        std::string ret = "rgba(";
        ret += std::to_string(r);
        ret += ",";
        ret += std::to_string(g);
        ret += ",";
        ret += std::to_string(b);
        ret += ",";
        ret += std::to_string(a);
        ret += ")";
        return ret;
    }

private:
    uchar r;
    uchar g;
    uchar b;
    uchar a;
};
