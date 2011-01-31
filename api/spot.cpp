#include "spot.h"

Spot::Spot(QObject *parent) :
    QObject(parent)
{
}
void Spot::setName(QString name)
{
    _name = name;
}

void Spot::setUrl(QString url)
{
    _url = url;
}

void Spot::setLat(double lat)
{
    _lat = lat;
}

void Spot::setLong(double lng)
{
    _lng = lng;
}

void Spot::setDescription(QString desc)
{
    _description = desc;
}
void Spot::setDistance(double distance)
{
    _distance = distance;
}

QString Spot:: name()
{
    return _name;
}

QString Spot::url()
{
    return _url;
}


double Spot::lat()
{
    return _lat;
}

double Spot::lng()
{
    return _lng;
}

int Spot::distance()
{
    return _distance;
}
QString Spot::description()
{
     return _description;
}
