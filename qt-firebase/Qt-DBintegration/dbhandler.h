#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class DBHandler : public QObject
{
    Q_OBJECT
public:
    explicit DBHandler(QObject *parent = nullptr,bool addToDB = false);
    ~DBHandler();
public slots:
    void networkReplyReadyRead();

signals:

private:
    QNetworkAccessManager *m_networkManager;
    QNetworkReply *m_networkReply;


};

#endif // DBHANDLER_H
