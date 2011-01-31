#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>
class User : public QObject
{
    Q_OBJECT
    public:
        explicit User(QObject *parent = 0);

        void setFirstname(QString firstname);
        void setLastname(QString lastname);
        void setUrl(QString url);
        void setImageUrl(QString imageUrl);

        QString firstName();
        QString lastName();
        QString url();
        QString imageUrl();

    private:
        QString _firstName;
        QString _lastName;
        QString _url;
        QString _imageUrl;

};

#endif // USER_H
