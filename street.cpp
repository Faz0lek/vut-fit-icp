#include "street.h"

Street::Street(QString street_name, int x1, int y1, int x2, int y2)
{
    this->street_name = street_name;
    this->coordinates = QPair<QPoint, QPoint>(QPoint(x1, y1), QPoint(x2, y2));
}

Street::Street(){}
