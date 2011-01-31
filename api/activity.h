#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QObject>

class Spot;
class User;
class Activity : public QObject
{
    Q_OBJECT
    public:
        explicit Activity(QObject *parent = 0);
        void setUser(User* user);
        void setSpot(Spot* spot);
        void setCreatedOn(QString createdOn);
        void setMessage(QString message);
        void setType(QString type);

        User* user();
        Spot* spot();
        QString createdOn();
        QString type();
        QString message();
    private:
        User* _user;
        Spot* _spot;
        QString _createdOn;
        QString _message;
        QString _type;

};

#endif // ACTIVITY_H
