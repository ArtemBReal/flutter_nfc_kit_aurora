#ifndef NFCD_NDEF_DBUS_IFACE_H
#define NFCD_NDEF_DBUS_IFACE_H

#include "qt_headers.h"

class NfcdNdefDBusIface : public QDBusAbstractInterface{
    Q_OBJECT

public:
    NfcdNdefDBusIface(const QString &path, QObject *parent = nullptr);

public slots:
    QDBusPendingReply<int> GetInterfaceVersion();
    QDBusPendingReply<uint> GetFlags();
    QDBusPendingReply<uint> GetTypeNameFormat();
    QDBusPendingReply<QByteArray>GetType();
    QDBusPendingReply<QByteArray> GetId();
    QDBusPendingReply<QByteArray> GetPayload();
    QDBusPendingReply<QByteArray> GetRawData();
    QDBusPendingReply<QStringList> GetInterfaces();

};

#endif //NFCD_NDEF_DBUS_IFACE_H