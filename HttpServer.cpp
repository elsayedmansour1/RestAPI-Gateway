#include "HttpServer.h"
#include "DBusManager.h"
#include <QTcpSocket>
#include <QRegularExpression>

HttpServer::HttpServer(DBusManager *dbusManager, QObject *parent)
    : QTcpServer(parent), m_dbusManager(dbusManager)
{
    if (!listen(QHostAddress::Any, 8080)) {
        qCritical() << "HTTP Server error:" << errorString();
    } else {
        qInfo() << "HTTP Server listening on port 8080";
    }
}

void HttpServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    if (!socket->setSocketDescriptor(socketDescriptor)) {
        delete socket;
        return;
    }
    
    connect(socket, &QTcpSocket::readyRead, [this, socket]() {
        QByteArray request = socket->readAll();
        
        // Add newline to ensure clean output
        QByteArray responseBody;
        QString statusCode = "200 OK";
        
        if (request.contains("GET /ipv4dns")) {
            responseBody = m_dbusManager->GetIPv4DNSforEthernet().toUtf8() + "\n";
        }
        else if (request.contains("GET /ipv4Address")) {
            responseBody = m_dbusManager->GetIPv4forEthernet().toUtf8() + "\n";
        }
        else if (request.contains("GET /ipv4Gateway")){
            responseBody = m_dbusManager->GetIPv4GatewayforEthernet().toUtf8() + "\n";
            }
        else {
            responseBody = "Endpoint not found\n";
            statusCode = "404 Not Found";
        }
        
        // Build proper HTTP response with Content-Length
        QByteArray response = "HTTP/1.1 " + statusCode.toUtf8() + "\r\n"
                              "Content-Type: text/plain\r\n"
                              "Content-Length: " + QByteArray::number(responseBody.size()) + "\r\n"
                              "Connection: close\r\n\r\n" + 
                              responseBody;
        
        socket->write(response);
        socket->disconnectFromHost();
    });

    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}