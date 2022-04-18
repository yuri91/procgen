#pragma once

#include "defs.h"

#include <string>

class Q_GUI_EXPORT QImage
{
public:
    enum Format {
        Format_RGB32,
        Format_ARGB32,
        Format_ARGB32_Premultiplied,
    };
    QImage(uchar *data, int width, int height, int bytesPerLine, Format format);
    explicit QImage(const std::string &fileName, const char *format = nullptr);
    QImage(int width, int height, Format format);

    QImage mirrored(bool horizontally = false, bool vertically = true) const;
    QImage convertToFormat(Format f) const;

    int width() const;
    int height() const;
};
