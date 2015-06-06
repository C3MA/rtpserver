#include "rgb2qcolorconverter.h"
#include "rtpparser.h"

#include <QDebug>
#include <QColor>
#include <QList>

RGB2QColorConverter::RGB2QColorConverter(QObject *parent, QQuickItem *root) :
    QObject(parent)
{
    this->mRoot = root;
}

void RGB2QColorConverter::newFrame(u_int8_t* frame, int width, int height)
{
    if (mRoot == NULL)
        return;

    QVariantList list;

    u_int8_t* row;
    for(int x=0; x < width; x++) {
        row = frame + (x*width * RGB_SIZE);
        for (int y = 0; y < height; ++y) {
            list << QColor(row[y * RGB_SIZE + 0] /* red */,
                    row[y * RGB_SIZE + 1] /* green */,
                    row[y * RGB_SIZE + 2] /* blue */);
        }
    }

    QVariant returnedValue;
    QMetaObject::invokeMethod(mRoot, "updateFrameContent",
            Q_RETURN_ARG(QVariant, returnedValue),
            Q_ARG(QVariant, QVariant::fromValue(list)),
            Q_ARG(QVariant, width),
            Q_ARG(QVariant, height));

}
