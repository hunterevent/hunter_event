#include "database.h"
#include <QStringList>

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    requer = new HttpRequest;
    QObject::connect( requer, SIGNAL(finishLoading(QString)),
                      this, SLOT(SlotGetEvent(QString)) );
}

void DataBase::GetEventInfo()
{
    qDebug() << "try get events \n";
    requer->processRequest("http://atary2sa.bget.ru/get_events.php");
}

void DataBase::SetEventInfo(QString id_event,
                            QString comment,
                            QString rating)
{
    qDebug() << "try set events \n";
    requer->processRequest("http://atary2sa.bget.ru/set_events.php" +
                           QString("?id=") + id_event +
                           "&comment=" + comment +
                           "&rating=" + rating);
}

void DataBase::SlotGetEvent(QString res)
{
    qDebug() << "get events " << res << "\n\n";

    EventInfo ev;
    QVector<EventInfo> vec_ev;

    QStringList list = res.split("|");
    for(int i = 0; i < list.size(); i++) {
        QStringList list_2 = list[i].split("/");
        ev.id = list_2[0];
        ev.comments = list_2[1];
        ev.rating = list_2[2];
        vec_ev.push_back(ev);
//        qDebug() << "list[i] " << list[i];
//        qDebug() <<  "list_2 "  << list_2[0] << " " << list_2[1] << " " << list_2[2];
    }

    for(int i = 0; i < vec_ev.size(); i++) {
        qDebug() << vec_ev[i].id << vec_ev[i].comments << vec_ev[i].rating;
    }

    SigGetEvent(vec_ev);
}
