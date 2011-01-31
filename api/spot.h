#ifndef SPOT_H
#define SPOT_H

#include <QObject>

class Spot : public QObject
{
    Q_OBJECT
    public:
        explicit Spot(QObject *parent = 0);
        void setName(QString name);
        void setUrl(QString url);
        void setLat(double lat);
        void setLong(double lng);
        void setDistance(double distance);
        void setDescription(QString desc);

        QString name();
        QString url();
        double lat();
        double lng();
        QString description();
        int distance();
    private:
        QString _name;
        QString _url;
        QString _description;
        double _lat;
        double _lng;
        int _distance;
};

#endif // SPOT_H
