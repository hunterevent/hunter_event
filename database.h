#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QString>
#include <QVector>
#include "httprequest.h"

/** @brief use this class for connection to database
*/
/** @example
 *
 QObject::connect( db, SIGNAL(SigGetEvent(QVector<EventInfo> )),
                      this, SLOT(FuncForGetting(QVector<EventInfo> )) );
*/


struct EventInfo {
    QString id;
    QString rating;
    QString comments;
};

class DataBase : public QObject
{
    Q_OBJECT
protected:
    HttpRequest * requer;
public:
    explicit DataBase(QObject *parent = 0);
    void GetEventInfo();
    void SetEventInfo(QString id_event,
                      QString comment,
                      QString rating);

signals:
    void SigGetEvent(QVector<EventInfo> event);
public slots:
    void SlotGetEvent(QString res);
};

#endif // DATABASE_H
