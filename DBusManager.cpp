#include "DBusManager.h"
#include <QDebug>
#include <QCoreApplication>

// D-Bus Configuration
const QString BUS_NAME = "com.cmlite";
const QString OBJECT_PATH = "/com/cmlite/Ethernet";
const QString INTERFACE_NAME = "cm.Ethernetmanager";

DBusManager::DBusManager(QObject *parent)
    : QObject(parent),
      m_customBus(QDBusConnection::connectToBus(
          "unix:path=/tmp/custom-bus.socket",  // Custom bus address
          "CustomBusConnection")              // Unique connection name
      )
{
    qDebug() << "Connecting to custom D-Bus at unix:path=/tmp/custom-bus.socket";
    
    // Verify custom bus connection
    if (!m_customBus.isConnected()) {
        qWarning() << "Failed to connect to custom D-Bus:" << m_customBus.lastError().message();
    }
    
    // Create interface using custom bus
    m_ethernetInterface = new QDBusInterface(
        BUS_NAME,
        OBJECT_PATH,
        INTERFACE_NAME,
        m_customBus,  // Use our custom bus connection
        this
    );
    
    if (!m_ethernetInterface->isValid()) {
        qWarning() << "D-Bus interface error:" << m_ethernetInterface->lastError().message();
    }
}

QString DBusManager::GetIPv4forEthernet()
{
    if (!m_ethernetInterface->isValid()) {
        return "DBus Interface Error";
    }
    
    QDBusReply<QString> reply = m_ethernetInterface->call("getIPv4forEthernet");
    
    return reply.isValid() ? reply.value() : "DBus Error: " + reply.error().message();
}

QString DBusManager::GetIPv4GatewayforEthernet(){
    
    if (!m_ethernetInterface->isValid()) {
        return "DBus Interface Error";
    }
    
    QDBusReply<QString> reply = m_ethernetInterface->call("getIPv4GatewayforEthernet");
    
    return reply.isValid() ? reply.value() : "DBus Error: " + reply.error().message();
}

QString DBusManager::GetIPv4SubnetforEthernet()
{
    if (!m_ethernetInterface->isValid()) {
        return "DBus Interface Error";
    }
    
    QDBusReply<QString> reply = m_ethernetInterface->call("getIPv4SubnetforEthernet");
    
    return reply.isValid() ? reply.value() : "DBus Error: " + reply.error().message();
}

QString DBusManager::GetIPv4DNSforEthernet()
{
    if (!m_ethernetInterface->isValid()) {
        return "DBus Interface Error";
    }
    
    QDBusReply<QString> reply = m_ethernetInterface->call("getIPv4DNSforEthernet");
    
    return reply.isValid() ? reply.value() : "DBus Error: " + reply.error().message();
}


QString DBusManager::GetIPv6forEthernet()
{
    if (!m_ethernetInterface->isValid()) {
        return "DBus Interface Error";
    }
    
    QDBusReply<QString> reply = m_ethernetInterface->call("getIPv6forEthernet");
    
    return reply.isValid() ? reply.value() : "DBus Error: " + reply.error().message();
}

QString DBusManager::GetIPv6GatewayforEthernet()
{
    if (!m_ethernetInterface->isValid()) {
        return "DBus Interface Error";
    }
    
    QDBusReply<QString> reply = m_ethernetInterface->call("getIPv6GatewayforEthernet");
    
    return reply.isValid() ? reply.value() : "DBus Error: " + reply.error().message();
}
QString DBusManager::GetIPv6PrefixLengthforEthernet()
{
    if (!m_ethernetInterface->isValid()) {
        return "DBus Interface Error";
    }
    
    QDBusReply<int> reply = m_ethernetInterface->call("getIPv6PrefixLengthforEthernet");
    
    return reply.isValid() ? QString::number(reply.value()) : "DBus Error: " + reply.error().message();
}

QString DBusManager::GetIPv6DNSforEthernet()
{
    if (!m_ethernetInterface->isValid()) {
        return "DBus Interface Error";
    }
    
    QDBusReply<QString> reply = m_ethernetInterface->call("getIPv6DNSforEthernet");
    
    return reply.isValid() ? reply.value() : "DBus Error: " + reply.error().message(); 
}