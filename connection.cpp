#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("garderie");
db.setUserName("islem2");//inserer nom de l'utilisateur
db.setPassword("123456789");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
