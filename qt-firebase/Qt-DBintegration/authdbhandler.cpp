#include "authdbhandler.h"
#include <QDebug>
#include <QVariantMap>
#include <QNetworkRequest>
#include <QJsonObject>


AuthDBHandler::AuthDBHandler(QObject *parent)
    : QObject{parent},
      m_apiKey(QString())
{
    m_networkManager = new QNetworkAccessManager(this);
   connect(this,&AuthDBHandler::userSignedIn,this,&AuthDBHandler::authenticatedDataBaseCall);

}

AuthDBHandler::~AuthDBHandler()
{
    if(m_networkManager)
        m_networkManager->deleteLater();
}

void AuthDBHandler::setAPIKey(const QString &apiKey)
{
    m_apiKey = apiKey;
}

void AuthDBHandler::signUserUp(const QString &emailAdress, const QString &password)
{
    QString sighInEndPoint = "https://identitytoolkit.googleapis.com/v1/accounts:signUp?key=" + m_apiKey;

    QVariantMap variantPayLoad;
    variantPayLoad["email"] = emailAdress;
    variantPayLoad["password"] = password;
    variantPayLoad["returnSecureToken"] = true;

    QJsonDocument jsonPayLoad = QJsonDocument::fromVariant(variantPayLoad);
    performPOST(sighInEndPoint,jsonPayLoad);
}

void AuthDBHandler::signUserIn(const QString &emailAdress, const QString &password)
{

    QString sighUpEndPoint = "https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=" + m_apiKey;

    QVariantMap variantPayLoad;
    variantPayLoad["email"] = emailAdress;
    variantPayLoad["password"] = password;
    variantPayLoad["returnSecureToken"] = true;

    QJsonDocument jsonPayLoad = QJsonDocument::fromVariant(variantPayLoad);
    performPOST(sighUpEndPoint,jsonPayLoad);
}

void AuthDBHandler::networkReplyReadyRead()
{
     QByteArray response = m_networkReply->readAll();
      m_networkReply->deleteLater();
      parseResponse(response);
}

void AuthDBHandler::authenticatedDataBaseCall()
{
    QString endPoint = "https://qt-dbintegration-default-rtdb.europe-west1.firebasedatabase.app/Pets.json?auth=" + m_idToken;
    m_networkReply = m_networkManager->get(QNetworkRequest(QUrl(endPoint)));
    connect(m_networkReply, &QNetworkReply::readyRead,this,&AuthDBHandler::networkReplyReadyRead);

}

void AuthDBHandler::performPOST(const QString &url, const QJsonDocument &payload)
{
    QNetworkRequest newRequest((QUrl (url))); // fix it
    newRequest.setHeader(QNetworkRequest::ContentTypeHeader,QString("application/json"));
    m_networkReply = m_networkManager->post(newRequest,payload.toJson());
    connect(m_networkReply, &QNetworkReply::readyRead,this,&AuthDBHandler::networkReplyReadyRead);

}

void AuthDBHandler::parseResponse(const QByteArray &response)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(response);
    if(jsonDocument.object().contains("error"))
    {
        qDebug()<< "Error!!!: " << response ;
    }
    else if(jsonDocument.object().contains("kind"))
    {
        QString idToken = jsonDocument.object().value("idToken").toString();
        qDebug() << "User Sigh In!";
        m_idToken = idToken;
        emit userSignedIn();

    }
    else
    {
        qDebug() << "The response was: " << response;
    }
}
