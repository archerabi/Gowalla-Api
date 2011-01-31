#include "gowallaapi.h"
#include "api/activity.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QScriptValueIterator>
#include "user.h"
#include "spot.h"

GowallaApi::GowallaApi(QObject *parent) :
    QObject(parent)
{
    netmgr = new QNetworkAccessManager(this);
    connect(netmgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyRecieved(QNetworkReply*)));
    scriptEngine = new QScriptEngine(this);
}

int GowallaApi::getFriendActivity()
{
    QNetworkRequest req;
    QUrl url("https://api.gowalla.com/users/archerabi/activity/friends");
    url.addQueryItem("oauth_token",oAuthToken);
    req.setUrl(url);

    QNetworkReply* reply = callMethod(req);
    replyTypeMap.insert(reply,FriendActivity);
    return (int)reply;
}

int GowallaApi::getNearbyPlaces(double lat, double lng, int radiusInMeters)
{
    QNetworkRequest req;
    QUrl url("http://api.gowalla.com/spots");
    url.addQueryItem("lat",QString().setNum(lat));
    url.addQueryItem("lng",QString().setNum(lng));
    url.addQueryItem("radius",QString().setNum(radiusInMeters));
    req.setUrl(url);

    QNetworkReply* reply = callMethod(req);
    replyTypeMap.insert(reply,NearbySpots);
    return (int)reply;
}
QNetworkReply* GowallaApi::callMethod(QNetworkRequest req)
{
    req.setRawHeader(QByteArray("Accept"),QByteArray("application/json"));
    qDebug() << req.url().toString();
    QNetworkReply* reply = netmgr->get(req);
    return reply;
}

void GowallaApi::replyRecieved(QNetworkReply* reply)
{
    if(reply->error() != QNetworkReply::NoError)
    {

    }
    else
    {
        QString replyStr = reply->readAll();
//        qDebug() << replyStr;
        QScriptValue rootVal = scriptEngine->evaluate("(" + replyStr + ")");
        if(rootVal.property("error").isValid())
        {

        }
        else
        {
            switch(replyTypeMap.value(reply))
            {
                case NearbySpots:
                    {
                    QList<Spot*>* spotlist = createSpotList(rootVal);
                    emit spotsRecieved(spotlist);
                    }
                    break;
                case FetchOAuthToken:
                    userName = rootVal.property("username").toString();
                    oAuthToken = rootVal.property("access_token").toString();
                    refreshToken = rootVal.property("refreshToken").toString();
                    break;

                case FriendActivity:
                    QList<Activity*>* list = createActivityList(rootVal);
                    if(list)
                    {
                        emit activitiesRecieved(list);
                    }
                    break;
            }
        }
    }
    replyTypeMap.remove(reply);
    reply->deleteLater();
}

int GowallaApi::fetchOAuthToken(QString code,QString clientId,QString clientSecret,QUrl redirectUrl,int scope)
{
    QNetworkRequest req;
    req.setUrl(QUrl("https://gowalla.com/api/oauth/token"));

    QString authString = QString("grant_type=authorization_code&client_id=%1&client_secret=%2&code=%3&redirect_uri=%4")
                         .arg(clientId)
                         .arg(clientSecret)
                         .arg(code)
                         .arg(redirectUrl.toString());
    if(scope == ReadWrite)
    {
        authString.append("&scope=read-write");
    }

    QByteArray* array = new QByteArray;
    array->append(authString);
    QNetworkReply* reply = netmgr->post(req,*array);
    replyTypeMap.insert(reply,FetchOAuthToken);
    return (int)reply;
}

QList<Activity*>* GowallaApi::createActivityList(QScriptValue val)
{
    if(!val.property("activity").isArray())
        return NULL;

    QList<Activity*>* activityList = new QList<Activity*>;
    QScriptValueIterator iter(val.property("activity"));
    while(iter.hasNext())
    {
        iter.next();
        *activityList << createActivityObject( iter.value() );
    }
    return activityList;
}

QList<Spot*>* GowallaApi::createSpotList(QScriptValue val)
{
    if(!val.property("spots").isArray())
        return NULL;
    QList<Spot*>* spotlist = new QList<Spot*>;
    QScriptValueIterator iter(val.property("spots"));
    while(iter.hasNext())
    {
        iter.next();
        *spotlist  << createSpotObject( iter.value() );
        qDebug() << spotlist->last()->name();
    }
    return spotlist;
}

Activity* GowallaApi::createActivityObject(QScriptValue val)
{
    Activity* activity = new Activity(this);
    activity->setCreatedOn(val.property("created_at").toString());
    activity->setMessage(val.property("message").toString());
    activity->setType(val.property("type").toString());

    activity->setUser( createUserObject( val.property("user") ) );
    activity->setSpot( createSpotObject( val.property("spot") ) );
    return activity;
}

User* GowallaApi::createUserObject(QScriptValue val)
{
    User* user= new User(this);
    user->setFirstname( val.property("first_name").toString() );
    user->setImageUrl( val.property("image_url").toString() );
    user->setLastname( val.property("last_name").toString() );
    user->setUrl( val.property("url").toString() );
    return user;
}
Spot* GowallaApi::createSpotObject(QScriptValue val)
{
    Spot* spot = new Spot(this);
    spot->setLat( val.property("lat").toString().toDouble() );
    spot->setLong( val.property("lng").toString().toDouble() );
    spot->setUrl( val.property("url").toString() );
    spot->setName( val.property("name").toString() );
    if( val.property("radius_meters").isValid() )
        spot->setDistance( val.property("radius_meters").toInteger() );
    if( val.property("distance").isValid() )
        spot->setDescription( val.property("distance").toString() );
    return spot;
}

