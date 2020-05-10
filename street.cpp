#include "street.h"

Street::Street(QString streetname, int x1, int y1, int x2, int y2)
    : street_name(streetname),
      coordinates(QPair<QPoint, QPoint>(QPoint(x1, y1), QPoint(x2, y2)))
{}

Street::Street(){}
