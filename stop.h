#ifndef STOP_H
#define STOP_H

#include "street.h"

#include <QString>

class Stop
{
public:
    Stop(const Street * const street, const int distance);
    Stop();
private:
    const Street * const street;
    const int distance;
};

#endif // STOP_H
