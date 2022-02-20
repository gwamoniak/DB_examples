#include "dbhandler.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QVariantMap>
#include <QDebug>

DBHandler::DBHandler(QObject *parent, bool addToDB)
    : QObject{parent}
{
    m_networkManager = new QNetworkAccessManager(this);

    // add into DB
    QVariantMap newPet;
    if(addToDB)
    {
        newPet["Type"]  = "Dog";
        newPet["Name"]  = "Szarik";
        newPet["Food"]  = "Wurst";


        QJsonDocument jsonDoc = QJsonDocument::fromVariant(newPet);

        QNetworkRequest newPetRequest(QUrl("https://qt-dbintegration-default-rtdb.europe-west1.firebasedatabase.app/Pets.json"));
        newPetRequest.setHeader(QNetworkRequest::ContentTypeHeader,QString("application/json"));
        m_networkManager->post(newPetRequest,jsonDoc.toJson());
    }

    m_networkReply = m_networkManager->get(QNetworkRequest(QUrl("https://qt-dbintegration-default-rtdb.europe-west1.firebasedatabase.app/Pets.json")));
    connect(m_networkReply, &QNetworkReply::readyRead,this,&DBHandler::networkReplyReadyRead);
}

DBHandler::~DBHandler()
{
    if(m_networkManager)
        m_networkManager->deleteLater();
}

void DBHandler::networkReplyReadyRead()
{
    qDebug() << m_networkReply->readAll();
}
