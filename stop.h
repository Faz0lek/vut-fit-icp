#ifndef STOP_H
#define STOP_H

#include <QString>

class Stop
{
public:
    Stop(QString streetname, int distance);
    Stop();
private:
    QString street_name;
    int distance;
};

#endif // STOP_H
