#pragma once

#include "../QRect"
#include "../QRectF"
#include "../QImage"
#include "../QColor"

class QBrush {
public:
	QBrush(const QColor& c) noexcept:
		c(c)
	{
	}
	const QColor& color() const
	{
		return c;
	}
private:
	QColor c;
};

class QPen {
public:
	QPen(const QColor& c) noexcept:
		c(c), w(1)
	{
	}
	QPen(const QBrush& b, qreal w) noexcept:
		c(b.color()), w(w)
	{
	}
	const QColor& color() const
	{
		return c;
	}
	qreal width() const
	{
		return w;
	}
private:
	QColor c;
	qreal w;
};

namespace Qt {
	enum PenStyle {
        NoPen,
	};
}


class QPainter {
public:
    enum RenderHint {
        Antialiasing = 0x01,
        SmoothPixmapTransform = 0x04,
	};
    enum CompositionMode {
        CompositionMode_Source,
	};
    explicit QPainter(QImage *);
    void setPen(const QPen &pen);
    void setPen(Qt::PenStyle style);
    void drawEllipse(const QRect &r);
    void drawEllipse(const QRectF &r);
    void drawLine(int x1, int y1, int x2, int y2);
    void drawImage(const QRectF &r, const QImage &image);
	void restore();
	void save();
    void setRenderHint(RenderHint hint, bool on = true);
	void setBrush(const QBrush &brush);
    void fillRect(const QRectF &, const QColor &color);
    void fillRect(const QRect &, const QColor &color);
    void setOpacity(qreal opacity);
    void translate(qreal dx, qreal dy);
    void rotate(qreal a);
    void setCompositionMode(CompositionMode mode);
private:
};
