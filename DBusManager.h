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
    
    QString GetIPv4forEthernet();
    QString GetIPv4GatewayforEthernet();
    QString GetIPv4SubnetforEthernet();
    QString GetIPv4DNSforEthernet();
    QString GetIPv6forEthernet();
    QString GetIPv6GatewayforEthernet();
    QString GetIPv6PrefixLengthforEthernet();
    QString GetIPv6DNSforEthernet();
private:
    QDBusConnection m_customBus;  // Custom bus connection
    QDBusInterface* m_ethernetInterface;
};

#endif // DBUSMANAGER_H