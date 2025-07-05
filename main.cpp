#include <QCoreApplication>
#include "DBusManager.h"
#include "HttpServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    // Create D-Bus manager
    DBusManager dbusManager;
    
    // Create HTTP server
    HttpServer server(&dbusManager);
    
    return a.exec();
}