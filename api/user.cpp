#include "user.h"

User::User(QObject *parent) :
    QObject(parent)
{
}

void User::setFirstname(QString firstname)
{
     _firstName = firstname;
}

void User::setLastname(QString lastname)
{
    _lastName = lastname;
}

void User::setUrl(QString url)
{
    _url = url;
}

void User::setImageUrl(QString imageUrl)
{
    _imageUrl = imageUrl;
}

QString User::firstName()
{
    return _firstName;
}

QString User::lastName()
{
    return _lastName;
}

QString User::url()
{
    return _url;
}

QString User::imageUrl()
{
    return _imageUrl;
}
