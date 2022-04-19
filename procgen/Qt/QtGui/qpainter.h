#pragma once

#include <cheerp/client.h>
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

namespace Qt {
	enum PenStyle {
        NoPen,
		SolidLine,
	};
}

class QPen {
public:
	QPen(const Qt::PenStyle s) noexcept:
		c(QColor(0,0,0)), w(1), s(s)
	{
	}
	QPen(const QColor& c) noexcept:
		c(c), w(1), s(Qt::PenStyle::SolidLine)
	{
	}
	QPen(const QBrush& b, qreal w) noexcept:
		c(b.color()), w(w), s(Qt::PenStyle::SolidLine)
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
	Qt::PenStyle style() const {
		return s;
	}
private:
	QColor c;
	qreal w;
	Qt::PenStyle s;
};


class QPainter {
public:
    enum RenderHint {
        Antialiasing = 0x01,
        SmoothPixmapTransform = 0x04,
	};
    enum CompositionMode {
        CompositionMode_Source,
	};
    explicit QPainter(client::HTMLCanvasElement *canvas)
		: canvas(canvas), ctx(static_cast<client::CanvasRenderingContext2D*>(canvas->getContext("2d")))
	{
		setPen(QPen(QColor(0,0,0)));
		setBrush(QBrush(QColor(0,0,0)));
	};
    explicit QPainter(QImage *img): QPainter(img->getCanvas()) {
	}
    void setPen(const QPen &pen) {
		ctx->set_strokeStyle(pen.color().toString().c_str());
	}
    void setPen(Qt::PenStyle style) {
		setPen(QPen(style));
	}
    void drawEllipse(const QRect &r) {
		drawEllipse(r);
	}
    void drawEllipse(const QRectF &r) {
		ctx->beginPath();
		QPointF c = r.center();
		ctx->ellipse(c.x(), c.y(), r.width()/2, r.height()/2, 0, 0, 2*client::Math.get_PI());
		ctx->stroke();
	}
    void drawLine(int x1, int y1, int x2, int y2) {
		ctx->beginPath();
		ctx->moveTo(x1, y1);
		ctx->lineTo(x2, y2);
		ctx->stroke();
	}
    void drawImage(const QRectF &r, const QImage &image) {
		ctx->drawImage(image.getCanvas(), 0, 0, image.width(), image.height(), r.x(), r.y(), r.width(), r.height());
	}
	void restore() {
		ctx->restore();
	}
	void save() {
		ctx->save();
	}
    void setRenderHint(RenderHint hint, bool on = true);
	void setBrush(const QBrush &brush) {
		ctx->set_fillStyle(brush.color().toString().c_str());
	}
    void fillRect(const QRectF &r, const QColor &color)
	{
		ctx->set_fillStyle(color.toString().c_str());
		ctx->fillRect(r.x(), r.y(), r.width(), r.height());
	}
    void fillRect(const QRect &r, const QColor &color)
	{
		fillRect(r, color);
	}
    void setOpacity(qreal opacity) {
		ctx->set_globalAlpha(opacity);
	}
    void translate(qreal dx, qreal dy) {
		ctx->translate(dx, dy);
	}
    void rotate(qreal a) {
		ctx->rotate(a);
	}
    void setCompositionMode(CompositionMode mode) {
		switch (mode) {
			case CompositionMode::CompositionMode_Source:
			{
				ctx->set_globalCompositeOperation("copy");
				break;
			}
		}
	}
private:
	client::HTMLCanvasElement* canvas;
	client::CanvasRenderingContext2D* ctx;
};
