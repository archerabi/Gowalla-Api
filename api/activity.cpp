#include "activity.h"
#include "user.h"
#include "spot.h"
Activity::Activity(QObject *parent) :
    QObject(parent)
{
}
void Activity::setUser(User* user)
{
    _user = user;
    _user->setParent(this);
}

void Activity::setSpot(Spot* spot)
{
    _spot = spot;
    _spot->setParent(this);
}

void Activity::setCreatedOn(QString createdOn)
{
    _createdOn = createdOn;
}

void Activity::setMessage(QString message)
{
    _message = message;
}

void Activity::setType(QString type)
{
    _type = type;
}

User* Activity::user()
{
    return _user;
}

Spot* Activity::spot()
{
    return _spot;
}

QString Activity::createdOn()
{
    return _createdOn;
}

QString Activity::type()
{
    return _type;
}

QString Activity::message()
{
    return _message;
}
