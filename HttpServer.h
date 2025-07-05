#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QTcpServer>
#include <QObject>

class DBusManager;

class HttpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit HttpServer(DBusManager *dbusManager, QObject *parent = nullptr);
    
protected:
    void incomingConnection(qintptr socketDescriptor) override;
    
private:
    DBusManager *m_dbusManager;
};

#endif // HTTPSERVER_H