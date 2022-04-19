#pragma once

#include "defs.h"

#include "../src/loadinghelper.h"

#include <string>
#include <cheerp/client.h>

class Q_GUI_EXPORT QImage
{
public:
    enum Format {
        Format_RGB32,
        Format_ARGB32,
        Format_ARGB32_Premultiplied,
    };
    explicit QImage(const std::string &fileName) {
        canvas = static_cast<client::HTMLCanvasElement*>(client::document.createElement("canvas"));
	auto* img = loadingHelper.get(fileName);
        canvas->set_width(img->get_width());
        canvas->set_height(img->get_height());
        auto* ctx = static_cast<client::CanvasRenderingContext2D*>(canvas->getContext("2d"));
	ctx->drawImage(img, 0, 0);
    }
    QImage(int width, int height, Format format)
        : format(format)
    {
        canvas = static_cast<client::HTMLCanvasElement*>(client::document.createElement("canvas"));
        canvas->set_width(width);
        canvas->set_height(height);
    }

    QImage mirrored(bool horizontally = false, bool vertically = true) const {
        QImage other(width(), height(), format);
        auto* ctx = static_cast<client::CanvasRenderingContext2D*>(other.canvas->getContext("2d"));
        int scaleH = horizontally ? -1 : 1;
        int scaleV = vertically ? -1 : 1;
        int posX = horizontally ? width() * -1 : 0;
        int posY = vertically ? height() * -1 : 0;
        ctx->save();
        ctx->scale(scaleH, scaleV);
        ctx->drawImage(canvas, posX, posY, width(), height());
        ctx->restore();
        return other;
    }
    QImage convertToFormat(Format f) const {
        // TODO actually convert
        QImage other(width(), height(), f);
        auto* ctx = static_cast<client::CanvasRenderingContext2D*>(other.canvas->getContext("2d"));
        ctx->drawImage(canvas, 0, 0);
        return other;
    }

    int width() const {
        return canvas->get_width();
    }
    int height() const {
        return canvas->get_height();
    }
    client::HTMLCanvasElement* getCanvas() const {
        return canvas;
    }
private:
    client::HTMLCanvasElement* canvas;
    Format format;
};
