#ifndef AUTHDBHANDLER_H
#define AUTHDBHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>

class AuthDBHandler : public QObject
{
    Q_OBJECT
public:
    explicit AuthDBHandler(QObject *parent = nullptr);
    ~AuthDBHandler();
    void setAPIKey(const QString &apiKey);
    void signUserUp(const QString & emailAdress, const QString &password);
    void signUserIn(const QString & emailAdress, const QString &password);

signals:
    void userSignedIn();
public slots:
    void networkReplyReadyRead();
    void authenticatedDataBaseCall();

private:
    void performPOST(const QString &url, const QJsonDocument& payload);
    void parseResponse(const QByteArray& respons);
    QString m_apiKey;
    QNetworkAccessManager *m_networkManager;
    QNetworkReply *m_networkReply;
    QString m_idToken;


};

#endif // AUTHDBHANDLER_H
