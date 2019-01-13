#include "jsontransmitter.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QJsonDocument>

JSONTransmitter::JSONTransmitter(QObject *parent) : QObject(parent){

}

void JSONTransmitter::getJSON(){
    QJsonDocument doc;
    doc.setArray(JSONData);
    QString dataToString(doc.toJson());
    //qDebug() << "getJSON sent: " << dataToString;

    emit sendJSON(dataToString);
}
