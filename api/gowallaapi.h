#ifndef GOWALLAAPI_H
#define GOWALLAAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QList>
#include <QUrl>
#include <QScriptEngine>
class Activity;
class User;
class Spot;
class GowallaApi : public QObject
{
    Q_OBJECT
    public:
        explicit GowallaApi(QObject *parent = 0);

        enum Scope{
            Read,
            ReadWrite
        };

        int getFriendActivity();
        int fetchOAuthToken(QString code,QString clientId,QString clientSecret,QUrl redirectUrl,int scope=Read);
        int getNearbyPlaces(double lat,double lng,int radiusInMeters=100);

    signals:
        void activitiesRecieved(QList<Activity*>*);
        void spotsRecieved(QList<Spot*>*);
    public slots:
        void replyRecieved(QNetworkReply*);
    private:
        QList<Activity*>* createActivityList(QScriptValue val);
        QList<Spot*>* createSpotList(QScriptValue val);

        Activity* createActivityObject(QScriptValue val);
        User* createUserObject(QScriptValue val);
        Spot* createSpotObject(QScriptValue val);

        QNetworkReply* callMethod(QNetworkRequest req);
    private:
        QNetworkAccessManager* netmgr;
        QScriptEngine* scriptEngine;
        QMap<QNetworkReply*,int> replyTypeMap;

        QString userName;
        QString oAuthToken;
        QString refreshToken;

        enum CallType{
            FetchOAuthToken,
            FriendActivity,
            NearbySpots
        };

};

#endif // GOWALLAAPI_H
