#include <QCoreApplication>
#include "dbhandler.h"
#include "authdbhandler.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //DBHandler dbhandler;
    AuthDBHandler authdbhandler;
    authdbhandler.setAPIKey("AIzaSyCUnYPYBxllXfg9jahR463eGJoucarBpXQ");
    //authdbhandler.signUserUp("testing@email.com","Password123!");
    authdbhandler.signUserIn("testing@email.com","Password123!");

    return a.exec();
}
