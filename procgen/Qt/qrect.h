#pragma once

#include "defs.h"

class Q_CORE_EXPORT QPoint
{
public:
    Q_DECL_CONSTEXPR QPoint();
    Q_DECL_CONSTEXPR QPoint(int xpos, int ypos);

    Q_DECL_CONSTEXPR inline bool isNull() const;

    Q_DECL_CONSTEXPR inline int x() const;
    Q_DECL_CONSTEXPR inline int y() const;
    Q_DECL_RELAXED_CONSTEXPR inline void setX(int x);
    Q_DECL_RELAXED_CONSTEXPR inline void setY(int y);

    Q_DECL_CONSTEXPR QPoint transposed() const noexcept { return {yp, xp}; }

    Q_DECL_RELAXED_CONSTEXPR inline int &rx();
    Q_DECL_RELAXED_CONSTEXPR inline int &ry();

    Q_DECL_RELAXED_CONSTEXPR inline QPoint &operator+=(const QPoint &p);
    Q_DECL_RELAXED_CONSTEXPR inline QPoint &operator-=(const QPoint &p);

    Q_DECL_RELAXED_CONSTEXPR inline QPoint &operator*=(float factor);
    Q_DECL_RELAXED_CONSTEXPR inline QPoint &operator*=(double factor);
    Q_DECL_RELAXED_CONSTEXPR inline QPoint &operator*=(int factor);

    Q_DECL_RELAXED_CONSTEXPR inline QPoint &operator/=(qreal divisor);

    Q_DECL_CONSTEXPR static inline int dotProduct(const QPoint &p1, const QPoint &p2)
    { return p1.xp * p2.xp + p1.yp * p2.yp; }

    friend Q_DECL_CONSTEXPR inline bool operator==(const QPoint &, const QPoint &);
    friend Q_DECL_CONSTEXPR inline bool operator!=(const QPoint &, const QPoint &);
    friend Q_DECL_CONSTEXPR inline const QPoint operator+(const QPoint &, const QPoint &);
    friend Q_DECL_CONSTEXPR inline const QPoint operator-(const QPoint &, const QPoint &);
    friend Q_DECL_CONSTEXPR inline const QPoint operator*(const QPoint &, float);
    friend Q_DECL_CONSTEXPR inline const QPoint operator*(float, const QPoint &);
    friend Q_DECL_CONSTEXPR inline const QPoint operator*(const QPoint &, double);
    friend Q_DECL_CONSTEXPR inline const QPoint operator*(double, const QPoint &);
    friend Q_DECL_CONSTEXPR inline const QPoint operator*(const QPoint &, int);
    friend Q_DECL_CONSTEXPR inline const QPoint operator*(int, const QPoint &);
    friend Q_DECL_CONSTEXPR inline const QPoint operator+(const QPoint &);
    friend Q_DECL_CONSTEXPR inline const QPoint operator-(const QPoint &);
    friend Q_DECL_CONSTEXPR inline const QPoint operator/(const QPoint &, qreal);

    int xp;
    int yp;
};

Q_DECL_CONSTEXPR inline QPoint::QPoint() : xp(0), yp(0) {}

Q_DECL_CONSTEXPR inline QPoint::QPoint(int xpos, int ypos) : xp(xpos), yp(ypos) {}

Q_DECL_CONSTEXPR inline bool QPoint::isNull() const
{ return xp == 0 && yp == 0; }

Q_DECL_CONSTEXPR inline int QPoint::x() const
{ return xp; }

Q_DECL_CONSTEXPR inline int QPoint::y() const
{ return yp; }

Q_DECL_RELAXED_CONSTEXPR inline void QPoint::setX(int xpos)
{ xp = xpos; }

Q_DECL_RELAXED_CONSTEXPR inline void QPoint::setY(int ypos)
{ yp = ypos; }

Q_DECL_RELAXED_CONSTEXPR inline int &QPoint::rx()
{ return xp; }

Q_DECL_RELAXED_CONSTEXPR inline int &QPoint::ry()
{ return yp; }

Q_DECL_RELAXED_CONSTEXPR inline QPoint &QPoint::operator+=(const QPoint &p)
{ xp+=p.xp; yp+=p.yp; return *this; }

Q_DECL_RELAXED_CONSTEXPR inline QPoint &QPoint::operator-=(const QPoint &p)
{ xp-=p.xp; yp-=p.yp; return *this; }

Q_DECL_RELAXED_CONSTEXPR inline QPoint &QPoint::operator*=(int factor)
{ xp = xp*factor; yp = yp*factor; return *this; }

Q_DECL_CONSTEXPR inline bool operator==(const QPoint &p1, const QPoint &p2)
{ return p1.xp == p2.xp && p1.yp == p2.yp; }

Q_DECL_CONSTEXPR inline bool operator!=(const QPoint &p1, const QPoint &p2)
{ return p1.xp != p2.xp || p1.yp != p2.yp; }

Q_DECL_CONSTEXPR inline const QPoint operator+(const QPoint &p1, const QPoint &p2)
{ return QPoint(p1.xp+p2.xp, p1.yp+p2.yp); }

Q_DECL_CONSTEXPR inline const QPoint operator-(const QPoint &p1, const QPoint &p2)
{ return QPoint(p1.xp-p2.xp, p1.yp-p2.yp); }

Q_DECL_CONSTEXPR inline const QPoint operator*(const QPoint &p, int factor)
{ return QPoint(p.xp*factor, p.yp*factor); }

Q_DECL_CONSTEXPR inline const QPoint operator*(int factor, const QPoint &p)
{ return QPoint(p.xp*factor, p.yp*factor); }

Q_DECL_CONSTEXPR inline const QPoint operator+(const QPoint &p)
{ return p; }

Q_DECL_CONSTEXPR inline const QPoint operator-(const QPoint &p)
{ return QPoint(-p.xp, -p.yp); }


class Q_CORE_EXPORT QRect
{
public:
    Q_DECL_CONSTEXPR QRect() noexcept : x1(0), y1(0), x2(-1), y2(-1) {}
    Q_DECL_CONSTEXPR QRect(const QPoint &topleft, const QPoint &bottomright) noexcept;
    Q_DECL_CONSTEXPR QRect(int left, int top, int width, int height) noexcept;

    Q_DECL_CONSTEXPR inline bool isNull() const noexcept;
    Q_DECL_CONSTEXPR inline bool isEmpty() const noexcept;
    Q_DECL_CONSTEXPR inline bool isValid() const noexcept;

    Q_DECL_CONSTEXPR inline int left() const noexcept;
    Q_DECL_CONSTEXPR inline int top() const noexcept;
    Q_DECL_CONSTEXPR inline int right() const noexcept;
    Q_DECL_CONSTEXPR inline int bottom() const noexcept;
    Q_REQUIRED_RESULT QRect normalized() const noexcept;

    Q_DECL_CONSTEXPR inline int x() const noexcept;
    Q_DECL_CONSTEXPR inline int y() const noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setLeft(int pos) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setTop(int pos) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setRight(int pos) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setBottom(int pos) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setX(int x) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setY(int y) noexcept;

    Q_DECL_RELAXED_CONSTEXPR inline void setTopLeft(const QPoint &p) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setBottomRight(const QPoint &p) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setTopRight(const QPoint &p) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setBottomLeft(const QPoint &p) noexcept;

    Q_DECL_CONSTEXPR inline QPoint topLeft() const noexcept;
    Q_DECL_CONSTEXPR inline QPoint bottomRight() const noexcept;
    Q_DECL_CONSTEXPR inline QPoint topRight() const noexcept;
    Q_DECL_CONSTEXPR inline QPoint bottomLeft() const noexcept;
    Q_DECL_CONSTEXPR inline QPoint center() const noexcept;

    Q_DECL_RELAXED_CONSTEXPR inline void moveLeft(int pos) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveTop(int pos) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveRight(int pos) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveBottom(int pos) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveTopLeft(const QPoint &p) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveBottomRight(const QPoint &p) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveTopRight(const QPoint &p) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveBottomLeft(const QPoint &p) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveCenter(const QPoint &p) noexcept;

    Q_DECL_RELAXED_CONSTEXPR inline void translate(int dx, int dy) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void translate(const QPoint &p) noexcept;
    Q_REQUIRED_RESULT Q_DECL_CONSTEXPR inline QRect translated(int dx, int dy) const noexcept;
    Q_REQUIRED_RESULT Q_DECL_CONSTEXPR inline QRect translated(const QPoint &p) const noexcept;
    Q_REQUIRED_RESULT Q_DECL_CONSTEXPR inline QRect transposed() const noexcept;

    Q_DECL_RELAXED_CONSTEXPR inline void moveTo(int x, int t) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveTo(const QPoint &p) noexcept;

    Q_DECL_RELAXED_CONSTEXPR inline void setRect(int x, int y, int w, int h) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void getRect(int *x, int *y, int *w, int *h) const;

    Q_DECL_RELAXED_CONSTEXPR inline void setCoords(int x1, int y1, int x2, int y2) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void getCoords(int *x1, int *y1, int *x2, int *y2) const;

    Q_DECL_RELAXED_CONSTEXPR inline void adjust(int x1, int y1, int x2, int y2) noexcept;
    Q_REQUIRED_RESULT Q_DECL_CONSTEXPR inline QRect adjusted(int x1, int y1, int x2, int y2) const noexcept;

    Q_DECL_CONSTEXPR inline int width() const noexcept;
    Q_DECL_CONSTEXPR inline int height() const noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setWidth(int w) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setHeight(int h) noexcept;

    QRect operator|(const QRect &r) const noexcept;
    QRect operator&(const QRect &r) const noexcept;
    inline QRect& operator|=(const QRect &r) noexcept;
    inline QRect& operator&=(const QRect &r) noexcept;

    bool contains(const QRect &r, bool proper = false) const noexcept;
    bool contains(const QPoint &p, bool proper=false) const noexcept;
    inline bool contains(int x, int y) const noexcept;
    inline bool contains(int x, int y, bool proper) const noexcept;
    Q_REQUIRED_RESULT inline QRect united(const QRect &other) const noexcept;
    Q_REQUIRED_RESULT inline QRect intersected(const QRect &other) const noexcept;
    bool intersects(const QRect &r) const noexcept;

    friend Q_DECL_CONSTEXPR inline bool operator==(const QRect &, const QRect &) noexcept;
    friend Q_DECL_CONSTEXPR inline bool operator!=(const QRect &, const QRect &) noexcept;

private:
    int x1;
    int y1;
    int x2;
    int y2;
};

Q_DECL_CONSTEXPR inline bool operator==(const QRect &, const QRect &) noexcept;
Q_DECL_CONSTEXPR inline bool operator!=(const QRect &, const QRect &) noexcept;


Q_DECL_CONSTEXPR inline QRect::QRect(int aleft, int atop, int awidth, int aheight) noexcept
    : x1(aleft), y1(atop), x2(aleft + awidth - 1), y2(atop + aheight - 1) {}

Q_DECL_CONSTEXPR inline QRect::QRect(const QPoint &atopLeft, const QPoint &abottomRight) noexcept
    : x1(atopLeft.x()), y1(atopLeft.y()), x2(abottomRight.x()), y2(abottomRight.y()) {}

Q_DECL_CONSTEXPR inline bool QRect::isNull() const noexcept
{ return x2 == x1 - 1 && y2 == y1 - 1; }

Q_DECL_CONSTEXPR inline bool QRect::isEmpty() const noexcept
{ return x1 > x2 || y1 > y2; }

Q_DECL_CONSTEXPR inline bool QRect::isValid() const noexcept
{ return x1 <= x2 && y1 <= y2; }

Q_DECL_CONSTEXPR inline int QRect::left() const noexcept
{ return x1; }

Q_DECL_CONSTEXPR inline int QRect::top() const noexcept
{ return y1; }

Q_DECL_CONSTEXPR inline int QRect::right() const noexcept
{ return x2; }

Q_DECL_CONSTEXPR inline int QRect::bottom() const noexcept
{ return y2; }

Q_DECL_CONSTEXPR inline int QRect::x() const noexcept
{ return x1; }

Q_DECL_CONSTEXPR inline int QRect::y() const noexcept
{ return y1; }

Q_DECL_RELAXED_CONSTEXPR inline void QRect::setLeft(int pos) noexcept
{ x1 = pos; }

Q_DECL_RELAXED_CONSTEXPR inline void QRect::setTop(int pos) noexcept
{ y1 = pos; }

Q_DECL_RELAXED_CONSTEXPR inline void QRect::setRight(int pos) noexcept
{ x2 = pos; }

Q_DECL_RELAXED_CONSTEXPR inline void QRect::setBottom(int pos) noexcept
{ y2 = pos; }

Q_DECL_RELAXED_CONSTEXPR inline void QRect::setTopLeft(const QPoint &p) noexcept
{ x1 = p.x(); y1 = p.y(); }

Q_DECL_RELAXED_CONSTEXPR inline void QRect::setBottomRight(const QPoint &p) noexcept
{ x2 = p.x(); y2 = p.y(); }

Q_DECL_RELAXED_CONSTEXPR inline void QRect::setTopRight(const QPoint &p) noexcept
{ x2 = p.x(); y1 = p.y(); }

Q_DECL_RELAXED_CONSTEXPR inline void QRect::setBottomLeft(const QPoint &p) noexcept
{ x1 = p.x(); y2 = p.y(); }

Q_DECL_RELAXED_CONSTEXPR inline void QRect::setX(int ax) noexcept
{ x1 = ax; }

Q_DECL_RELAXED_CONSTEXPR inline void QRect::setY(int ay) noexcept
{ y1 = ay; }

Q_DECL_CONSTEXPR inline QPoint QRect::topLeft() const noexcept
{ return QPoint(x1, y1); }

Q_DECL_CONSTEXPR inline QPoint QRect::bottomRight() const noexcept
{ return QPoint(x2, y2); }

Q_DECL_CONSTEXPR inline QPoint QRect::topRight() const noexcept
{ return QPoint(x2, y1); }

Q_DECL_CONSTEXPR inline QPoint QRect::bottomLeft() const noexcept
{ return QPoint(x1, y2); }

Q_DECL_CONSTEXPR inline int QRect::width() const noexcept
{ return  x2 - x1 + 1; }

Q_DECL_CONSTEXPR inline int QRect::height() const noexcept
{ return  y2 - y1 + 1; }

Q_DECL_RELAXED_CONSTEXPR inline void QRect::translate(int dx, int dy) noexcept
{
    x1 += dx;
    y1 += dy;
    x2 += dx;
    y2 += dy;
}

Q_DECL_RELAXED_CONSTEXPR inline void QRect::translate(const QPoint &p) noexcept
{
    x1 += p.x();
    y1 += p.y();
    x2 += p.x();
    y2 += p.y();
}

Q_DECL_CONSTEXPR inline QRect QRect::translated(int dx, int dy) const noexcept
{ return QRect(QPoint(x1 + dx, y1 + dy), QPoint(x2 + dx, y2 + dy)); }

Q_DECL_CONSTEXPR inline QRect QRect::translated(const QPoint &p) const noexcept
{ return QRect(QPoint(x1 + p.x(), y1 + p.y()), QPoint(x2 + p.x(), y2 + p.y())); }

Q_DECL_RELAXED_CONSTEXPR inline void QRect::moveTo(int ax, int ay) noexcept
{
    x2 += ax - x1;
    y2 += ay - y1;
    x1 = ax;
    y1 = ay;
}

Q_DECL_RELAXED_CONSTEXPR inline void QRect::moveTo(const QPoint &p) noexcept
{
    x2 += p.x() - x1;
    y2 += p.y() - y1;
    x1 = p.x();
    y1 = p.y();
}

Q_DECL_RELAXED_CONSTEXPR inline void QRect::moveLeft(int pos) noexcept
{ x2 += (pos - x1); x1 = pos; }

Q_DECL_RELAXED_CONSTEXPR inline void QRect::moveTop(int pos) noexcept
{ y2 += (pos - y1); y1 = pos; }

Q_DECL_RELAXED_CONSTEXPR inline void QRect::moveRight(int pos) noexcept
{
    x1 += (pos - x2);
    x2 = pos;
}

Q_DECL_RELAXED_CONSTEXPR inline void QRect::moveBottom(int pos) noexcept
{
    y1 += (pos - y2);
    y2 = pos;
}

Q_DECL_RELAXED_CONSTEXPR inline void QRect::moveTopLeft(const QPoint &p) noexcept
{
    moveLeft(p.x());
    moveTop(p.y());
}

Q_DECL_RELAXED_CONSTEXPR inline void QRect::moveBottomRight(const QPoint &p) noexcept
{
    moveRight(p.x());
    moveBottom(p.y());
}

Q_DECL_RELAXED_CONSTEXPR inline void QRect::moveTopRight(const QPoint &p) noexcept
{
    moveRight(p.x());
    moveTop(p.y());
}

Q_DECL_RELAXED_CONSTEXPR inline void QRect::moveBottomLeft(const QPoint &p) noexcept
{
    moveLeft(p.x());
    moveBottom(p.y());
}

Q_DECL_RELAXED_CONSTEXPR inline void QRect::moveCenter(const QPoint &p) noexcept
{
    int w = x2 - x1;
    int h = y2 - y1;
    x1 = p.x() - w/2;
    y1 = p.y() - h/2;
    x2 = x1 + w;
    y2 = y1 + h;
}

Q_DECL_RELAXED_CONSTEXPR inline void QRect::getRect(int *ax, int *ay, int *aw, int *ah) const
{
    *ax = x1;
    *ay = y1;
    *aw = x2 - x1 + 1;
    *ah = y2 - y1 + 1;
}

Q_DECL_RELAXED_CONSTEXPR inline void QRect::setRect(int ax, int ay, int aw, int ah) noexcept
{
    x1 = ax;
    y1 = ay;
    x2 = (ax + aw - 1);
    y2 = (ay + ah - 1);
}

Q_DECL_RELAXED_CONSTEXPR inline void QRect::getCoords(int *xp1, int *yp1, int *xp2, int *yp2) const
{
    *xp1 = x1;
    *yp1 = y1;
    *xp2 = x2;
    *yp2 = y2;
}

Q_DECL_RELAXED_CONSTEXPR inline void QRect::setCoords(int xp1, int yp1, int xp2, int yp2) noexcept
{
    x1 = xp1;
    y1 = yp1;
    x2 = xp2;
    y2 = yp2;
}

Q_DECL_CONSTEXPR inline QRect QRect::adjusted(int xp1, int yp1, int xp2, int yp2) const noexcept
{ return QRect(QPoint(x1 + xp1, y1 + yp1), QPoint(x2 + xp2, y2 + yp2)); }

Q_DECL_RELAXED_CONSTEXPR inline void QRect::adjust(int dx1, int dy1, int dx2, int dy2) noexcept
{
    x1 += dx1;
    y1 += dy1;
    x2 += dx2;
    y2 += dy2;
}

Q_DECL_RELAXED_CONSTEXPR inline void QRect::setWidth(int w) noexcept
{ x2 = (x1 + w - 1); }

Q_DECL_RELAXED_CONSTEXPR inline void QRect::setHeight(int h) noexcept
{ y2 = (y1 + h - 1); }

inline bool QRect::contains(int ax, int ay, bool aproper) const noexcept
{
    return contains(QPoint(ax, ay), aproper);
}

inline bool QRect::contains(int ax, int ay) const noexcept
{
    return contains(QPoint(ax, ay), false);
}

inline QRect& QRect::operator|=(const QRect &r) noexcept
{
    *this = *this | r;
    return *this;
}

inline QRect& QRect::operator&=(const QRect &r) noexcept
{
    *this = *this & r;
    return *this;
}

inline QRect QRect::intersected(const QRect &other) const noexcept
{
    return *this & other;
}

inline QRect QRect::united(const QRect &r) const noexcept
{
    return *this | r;
}

Q_DECL_CONSTEXPR inline bool operator==(const QRect &r1, const QRect &r2) noexcept
{
    return r1.x1==r2.x1 && r1.x2==r2.x2 && r1.y1==r2.y1 && r1.y2==r2.y2;
}

Q_DECL_CONSTEXPR inline bool operator!=(const QRect &r1, const QRect &r2) noexcept
{
    return r1.x1!=r2.x1 || r1.x2!=r2.x2 || r1.y1!=r2.y1 || r1.y2!=r2.y2;
}

class Q_CORE_EXPORT QPointF
{
public:
    Q_DECL_CONSTEXPR QPointF();
    Q_DECL_CONSTEXPR QPointF(qreal xpos, qreal ypos);

    inline bool isNull() const;

    Q_DECL_CONSTEXPR inline qreal x() const;
    Q_DECL_CONSTEXPR inline qreal y() const;
    Q_DECL_RELAXED_CONSTEXPR inline void setX(qreal x);
    Q_DECL_RELAXED_CONSTEXPR inline void setY(qreal y);

    Q_DECL_CONSTEXPR QPointF transposed() const noexcept { return {yp, xp}; }

    Q_DECL_RELAXED_CONSTEXPR inline qreal &rx();
    Q_DECL_RELAXED_CONSTEXPR inline qreal &ry();

    Q_DECL_RELAXED_CONSTEXPR inline QPointF &operator+=(const QPointF &p);
    Q_DECL_RELAXED_CONSTEXPR inline QPointF &operator-=(const QPointF &p);
    Q_DECL_RELAXED_CONSTEXPR inline QPointF &operator*=(qreal c);
    Q_DECL_RELAXED_CONSTEXPR inline QPointF &operator/=(qreal c);

    Q_DECL_CONSTEXPR static inline qreal dotProduct(const QPointF &p1, const QPointF &p2)
    { return p1.xp * p2.xp + p1.yp * p2.yp; }

    friend Q_DECL_CONSTEXPR inline const QPointF operator+(const QPointF &, const QPointF &);
    friend Q_DECL_CONSTEXPR inline const QPointF operator-(const QPointF &, const QPointF &);
    friend Q_DECL_CONSTEXPR inline const QPointF operator*(qreal, const QPointF &);
    friend Q_DECL_CONSTEXPR inline const QPointF operator*(const QPointF &, qreal);
    friend Q_DECL_CONSTEXPR inline const QPointF operator+(const QPointF &);
    friend Q_DECL_CONSTEXPR inline const QPointF operator-(const QPointF &);
    friend Q_DECL_CONSTEXPR inline const QPointF operator/(const QPointF &, qreal);

private:
    friend class QMatrix;
    friend class QTransform;

    qreal xp;
    qreal yp;
};

Q_DECL_CONSTEXPR inline QPointF::QPointF() : xp(0), yp(0) { }

Q_DECL_CONSTEXPR inline QPointF::QPointF(qreal xpos, qreal ypos) : xp(xpos), yp(ypos) { }

Q_DECL_CONSTEXPR inline qreal QPointF::x() const
{
    return xp;
}

Q_DECL_CONSTEXPR inline qreal QPointF::y() const
{
    return yp;
}

Q_DECL_RELAXED_CONSTEXPR inline void QPointF::setX(qreal xpos)
{
    xp = xpos;
}

Q_DECL_RELAXED_CONSTEXPR inline void QPointF::setY(qreal ypos)
{
    yp = ypos;
}

Q_DECL_RELAXED_CONSTEXPR inline qreal &QPointF::rx()
{
    return xp;
}

Q_DECL_RELAXED_CONSTEXPR inline qreal &QPointF::ry()
{
    return yp;
}

Q_DECL_RELAXED_CONSTEXPR inline QPointF &QPointF::operator+=(const QPointF &p)
{
    xp+=p.xp;
    yp+=p.yp;
    return *this;
}

Q_DECL_RELAXED_CONSTEXPR inline QPointF &QPointF::operator-=(const QPointF &p)
{
    xp-=p.xp; yp-=p.yp; return *this;
}

Q_DECL_RELAXED_CONSTEXPR inline QPointF &QPointF::operator*=(qreal c)
{
    xp*=c; yp*=c; return *this;
}

Q_DECL_CONSTEXPR inline const QPointF operator+(const QPointF &p1, const QPointF &p2)
{
    return QPointF(p1.xp+p2.xp, p1.yp+p2.yp);
}

Q_DECL_CONSTEXPR inline const QPointF operator-(const QPointF &p1, const QPointF &p2)
{
    return QPointF(p1.xp-p2.xp, p1.yp-p2.yp);
}

Q_DECL_CONSTEXPR inline const QPointF operator*(const QPointF &p, qreal c)
{
    return QPointF(p.xp*c, p.yp*c);
}

Q_DECL_CONSTEXPR inline const QPointF operator*(qreal c, const QPointF &p)
{
    return QPointF(p.xp*c, p.yp*c);
}

Q_DECL_CONSTEXPR inline const QPointF operator+(const QPointF &p)
{
    return p;
}

Q_DECL_CONSTEXPR inline const QPointF operator-(const QPointF &p)
{
    return QPointF(-p.xp, -p.yp);
}

Q_DECL_RELAXED_CONSTEXPR inline QPointF &QPointF::operator/=(qreal divisor)
{
    xp/=divisor;
    yp/=divisor;
    return *this;
}

Q_DECL_CONSTEXPR inline const QPointF operator/(const QPointF &p, qreal divisor)
{
    return QPointF(p.xp/divisor, p.yp/divisor);
}

class Q_CORE_EXPORT QRectF
{
public:
    Q_DECL_CONSTEXPR QRectF() noexcept : xp(0.), yp(0.), w(0.), h(0.) {}
    Q_DECL_CONSTEXPR QRectF(const QPointF &topleft, const QPointF &bottomRight) noexcept;
    Q_DECL_CONSTEXPR QRectF(qreal left, qreal top, qreal width, qreal height) noexcept;

    Q_DECL_CONSTEXPR inline bool isNull() const noexcept;
    Q_DECL_CONSTEXPR inline bool isEmpty() const noexcept;
    Q_DECL_CONSTEXPR inline bool isValid() const noexcept;
    Q_REQUIRED_RESULT QRectF normalized() const noexcept;

    Q_DECL_CONSTEXPR inline qreal left() const noexcept { return xp; }
    Q_DECL_CONSTEXPR inline qreal top() const noexcept { return yp; }
    Q_DECL_CONSTEXPR inline qreal right() const noexcept { return xp + w; }
    Q_DECL_CONSTEXPR inline qreal bottom() const noexcept { return yp + h; }

    Q_DECL_CONSTEXPR inline qreal x() const noexcept;
    Q_DECL_CONSTEXPR inline qreal y() const noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setLeft(qreal pos) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setTop(qreal pos) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setRight(qreal pos) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setBottom(qreal pos) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setX(qreal pos) noexcept { setLeft(pos); }
    Q_DECL_RELAXED_CONSTEXPR inline void setY(qreal pos) noexcept { setTop(pos); }

    Q_DECL_CONSTEXPR inline QPointF topLeft() const noexcept { return QPointF(xp, yp); }
    Q_DECL_CONSTEXPR inline QPointF bottomRight() const noexcept { return QPointF(xp+w, yp+h); }
    Q_DECL_CONSTEXPR inline QPointF topRight() const noexcept { return QPointF(xp+w, yp); }
    Q_DECL_CONSTEXPR inline QPointF bottomLeft() const noexcept { return QPointF(xp, yp+h); }
    Q_DECL_CONSTEXPR inline QPointF center() const noexcept;

    Q_DECL_RELAXED_CONSTEXPR inline void setTopLeft(const QPointF &p) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setBottomRight(const QPointF &p) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setTopRight(const QPointF &p) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setBottomLeft(const QPointF &p) noexcept;

    Q_DECL_RELAXED_CONSTEXPR inline void moveLeft(qreal pos) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveTop(qreal pos) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveRight(qreal pos) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveBottom(qreal pos) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveTopLeft(const QPointF &p) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveBottomRight(const QPointF &p) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveTopRight(const QPointF &p) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveBottomLeft(const QPointF &p) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveCenter(const QPointF &p) noexcept;

    Q_DECL_RELAXED_CONSTEXPR inline void translate(qreal dx, qreal dy) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void translate(const QPointF &p) noexcept;

    Q_REQUIRED_RESULT Q_DECL_CONSTEXPR inline QRectF translated(qreal dx, qreal dy) const noexcept;
    Q_REQUIRED_RESULT Q_DECL_CONSTEXPR inline QRectF translated(const QPointF &p) const noexcept;

    Q_REQUIRED_RESULT Q_DECL_CONSTEXPR inline QRectF transposed() const noexcept;

    Q_DECL_RELAXED_CONSTEXPR inline void moveTo(qreal x, qreal y) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void moveTo(const QPointF &p) noexcept;

    Q_DECL_RELAXED_CONSTEXPR inline void setRect(qreal x, qreal y, qreal w, qreal h) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void getRect(qreal *x, qreal *y, qreal *w, qreal *h) const;

    Q_DECL_RELAXED_CONSTEXPR inline void setCoords(qreal x1, qreal y1, qreal x2, qreal y2) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void getCoords(qreal *x1, qreal *y1, qreal *x2, qreal *y2) const;

    Q_DECL_RELAXED_CONSTEXPR inline void adjust(qreal x1, qreal y1, qreal x2, qreal y2) noexcept;
    Q_REQUIRED_RESULT Q_DECL_CONSTEXPR inline QRectF adjusted(qreal x1, qreal y1, qreal x2, qreal y2) const noexcept;

    Q_DECL_CONSTEXPR inline qreal width() const noexcept;
    Q_DECL_CONSTEXPR inline qreal height() const noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setWidth(qreal w) noexcept;
    Q_DECL_RELAXED_CONSTEXPR inline void setHeight(qreal h) noexcept;

    QRectF operator|(const QRectF &r) const noexcept;
    QRectF operator&(const QRectF &r) const noexcept;
    inline QRectF& operator|=(const QRectF &r) noexcept;
    inline QRectF& operator&=(const QRectF &r) noexcept;

    bool contains(const QRectF &r) const noexcept;
    bool contains(const QPointF &p) const noexcept;
    inline bool contains(qreal x, qreal y) const noexcept;
    Q_REQUIRED_RESULT inline QRectF united(const QRectF &other) const noexcept;
    Q_REQUIRED_RESULT inline QRectF intersected(const QRectF &other) const noexcept;
    bool intersects(const QRectF &r) const noexcept;


    friend Q_DECL_CONSTEXPR inline bool operator==(const QRectF &, const QRectF &) noexcept;
    friend Q_DECL_CONSTEXPR inline bool operator!=(const QRectF &, const QRectF &) noexcept;

private:
    qreal xp;
    qreal yp;
    qreal w;
    qreal h;
};

Q_DECL_CONSTEXPR inline bool operator==(const QRectF &, const QRectF &) noexcept;
Q_DECL_CONSTEXPR inline bool operator!=(const QRectF &, const QRectF &) noexcept;


Q_DECL_CONSTEXPR inline QRectF::QRectF(qreal aleft, qreal atop, qreal awidth, qreal aheight) noexcept
    : xp(aleft), yp(atop), w(awidth), h(aheight)
{
}

Q_DECL_CONSTEXPR inline QRectF::QRectF(const QPointF &atopLeft, const QPointF &abottomRight) noexcept
    : xp(atopLeft.x()), yp(atopLeft.y()), w(abottomRight.x() - atopLeft.x()), h(abottomRight.y() - atopLeft.y())
{
}

Q_DECL_CONSTEXPR inline bool QRectF::isNull() const noexcept
{ return w == 0. && h == 0.; }

Q_DECL_CONSTEXPR inline bool QRectF::isEmpty() const noexcept
{ return w <= 0. || h <= 0.; }

Q_DECL_CONSTEXPR inline bool QRectF::isValid() const noexcept
{ return w > 0. && h > 0.; }

Q_DECL_CONSTEXPR inline qreal QRectF::x() const noexcept
{ return xp; }

Q_DECL_CONSTEXPR inline qreal QRectF::y() const noexcept
{ return yp; }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::setLeft(qreal pos) noexcept
{ qreal diff = pos - xp; xp += diff; w -= diff; }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::setRight(qreal pos) noexcept
{ w = pos - xp; }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::setTop(qreal pos) noexcept
{ qreal diff = pos - yp; yp += diff; h -= diff; }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::setBottom(qreal pos) noexcept
{ h = pos - yp; }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::setTopLeft(const QPointF &p) noexcept
{ setLeft(p.x()); setTop(p.y()); }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::setTopRight(const QPointF &p) noexcept
{ setRight(p.x()); setTop(p.y()); }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::setBottomLeft(const QPointF &p) noexcept
{ setLeft(p.x()); setBottom(p.y()); }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::setBottomRight(const QPointF &p) noexcept
{ setRight(p.x()); setBottom(p.y()); }

Q_DECL_CONSTEXPR inline QPointF QRectF::center() const noexcept
{ return QPointF(xp + w/2, yp + h/2); }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::moveLeft(qreal pos) noexcept
{ xp = pos; }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::moveTop(qreal pos) noexcept
{ yp = pos; }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::moveRight(qreal pos) noexcept
{ xp = pos - w; }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::moveBottom(qreal pos) noexcept
{ yp = pos - h; }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::moveTopLeft(const QPointF &p) noexcept
{ moveLeft(p.x()); moveTop(p.y()); }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::moveTopRight(const QPointF &p) noexcept
{ moveRight(p.x()); moveTop(p.y()); }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::moveBottomLeft(const QPointF &p) noexcept
{ moveLeft(p.x()); moveBottom(p.y()); }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::moveBottomRight(const QPointF &p) noexcept
{ moveRight(p.x()); moveBottom(p.y()); }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::moveCenter(const QPointF &p) noexcept
{ xp = p.x() - w/2; yp = p.y() - h/2; }

Q_DECL_CONSTEXPR inline qreal QRectF::width() const noexcept
{ return w; }

Q_DECL_CONSTEXPR inline qreal QRectF::height() const noexcept
{ return h; }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::translate(qreal dx, qreal dy) noexcept
{
    xp += dx;
    yp += dy;
}

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::translate(const QPointF &p) noexcept
{
    xp += p.x();
    yp += p.y();
}

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::moveTo(qreal ax, qreal ay) noexcept
{
    xp = ax;
    yp = ay;
}

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::moveTo(const QPointF &p) noexcept
{
    xp = p.x();
    yp = p.y();
}

Q_DECL_CONSTEXPR inline QRectF QRectF::translated(qreal dx, qreal dy) const noexcept
{ return QRectF(xp + dx, yp + dy, w, h); }

Q_DECL_CONSTEXPR inline QRectF QRectF::translated(const QPointF &p) const noexcept
{ return QRectF(xp + p.x(), yp + p.y(), w, h); }


Q_DECL_RELAXED_CONSTEXPR inline void QRectF::getRect(qreal *ax, qreal *ay, qreal *aaw, qreal *aah) const
{
    *ax = this->xp;
    *ay = this->yp;
    *aaw = this->w;
    *aah = this->h;
}

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::setRect(qreal ax, qreal ay, qreal aaw, qreal aah) noexcept
{
    this->xp = ax;
    this->yp = ay;
    this->w = aaw;
    this->h = aah;
}

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::getCoords(qreal *xp1, qreal *yp1, qreal *xp2, qreal *yp2) const
{
    *xp1 = xp;
    *yp1 = yp;
    *xp2 = xp + w;
    *yp2 = yp + h;
}

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::setCoords(qreal xp1, qreal yp1, qreal xp2, qreal yp2) noexcept
{
    xp = xp1;
    yp = yp1;
    w = xp2 - xp1;
    h = yp2 - yp1;
}

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::adjust(qreal xp1, qreal yp1, qreal xp2, qreal yp2) noexcept
{ xp += xp1; yp += yp1; w += xp2 - xp1; h += yp2 - yp1; }

Q_DECL_CONSTEXPR inline QRectF QRectF::adjusted(qreal xp1, qreal yp1, qreal xp2, qreal yp2) const noexcept
{ return QRectF(xp + xp1, yp + yp1, w + xp2 - xp1, h + yp2 - yp1); }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::setWidth(qreal aw) noexcept
{ this->w = aw; }

Q_DECL_RELAXED_CONSTEXPR inline void QRectF::setHeight(qreal ah) noexcept
{ this->h = ah; }

inline bool QRectF::contains(qreal ax, qreal ay) const noexcept
{
    return contains(QPointF(ax, ay));
}

inline QRectF& QRectF::operator|=(const QRectF &r) noexcept
{
    *this = *this | r;
    return *this;
}

inline QRectF& QRectF::operator&=(const QRectF &r) noexcept
{
    *this = *this & r;
    return *this;
}

inline QRectF QRectF::intersected(const QRectF &r) const noexcept
{
    return *this & r;
}

inline QRectF QRectF::united(const QRectF &r) const noexcept
{
    return *this | r;
}


