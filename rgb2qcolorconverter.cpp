#include "rgb2qcolorconverter.h"
#include "rtpparser.h"

#include <QDebug>

RGB2QColorConverter::RGB2QColorConverter(QObject *parent) :
    QObject(parent)
{
}

void RGB2QColorConverter::newFrame(u_int8_t* frame, int width, int height)
{
    u_int8_t* row;
    for(int x=0; x < width; x++) {
        row = frame + (x*width * RGB_SIZE);
        for (int y = 0; y < height; ++y) {
            qDebug() << "" << row[y * RGB_SIZE + 0] << ","
                    << row[y * RGB_SIZE + 1] << ","
                    << row[y * RGB_SIZE + 2] << ",";
        }
    }
}
