#ifndef NFCD_TAGTYPE2_DBUS_IFACE_H
#define NFCD_TAGTYPE2_DBUS_IFACE_H

#include "qt_headers.h"

class NfcdTagType2DBusIface : public QDBusAbstractInterface{
    Q_OBJECT

public:
    NfcdTagType2DBusIface(const QString &path, QObject *parent = nullptr);

public slots:
    QDBusPendingReply<int> GetInterfaceVersion();
    QDBusPendingReply<uint> GetBlockSize();
    QDBusPendingReply<uint> GetDataSize();
    QDBusPendingReply<uint> Write(uint sector, uint block, const QByteArray &data);
    QDBusPendingReply<uint> WriteData(uint offset, const QByteArray &data);
    QDBusPendingReply<QByteArray> Read(uint sector, uint block);
    QDBusPendingReply<QByteArray> ReadData(uint offset, uint maxbytes);
    QDBusPendingReply<QByteArray> ReadAllData();
    QDBusPendingReply<QByteArray> GetSerial();
};

#endif //NFCD_TAGTYPE2_DBUS_IFACE_H