#ifndef JSONTRANSMITTER_H
#define JSONTRANSMITTER_H

#include <QObject>
#include <QJsonArray>


class JSONTransmitter : public QObject
{
    Q_OBJECT
public:
    explicit JSONTransmitter(QObject *parent = 0);
    QJsonArray JSONData;

signals:
    void sendJSON(QString payload);

public slots:
    void getJSON();

};

#endif // JSONTRANSMITTER_H
