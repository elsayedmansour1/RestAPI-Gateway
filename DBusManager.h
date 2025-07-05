#ifndef DBUSMANAGER_H
#define DBUSMANAGER_H

#include <QObject>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusReply>

class DBusManager : public QObject
{
    Q_OBJECT
public:
    explicit DBusManager(QObject *parent = nullptr);
    
    QString GetIPv4DNSforEthernet();
    QString GetIPv4forEthernet();
    QString GetIPv4GatewayforEthernet();
    
private:
    QDBusConnection m_customBus;  // Custom bus connection
    QDBusInterface* m_ethernetInterface;
};

#endif // DBUSMANAGER_H