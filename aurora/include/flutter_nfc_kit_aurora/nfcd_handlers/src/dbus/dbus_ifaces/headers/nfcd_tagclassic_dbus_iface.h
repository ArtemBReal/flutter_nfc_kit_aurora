#ifndef NFCD_TAGCLASSIC_DBUS_IFACE_H
#define NFCD_TAGCLASSIC_DBUS_IFACE_H

#include "qt_headers.h"

class NfcdTagClassicDBusIface : public QDBusAbstractInterface{
    Q_OBJECT

public:
    NfcdTagClassicDBusIface(const QString &path, QObject *parent = nullptr);

public slots:
    QDBusPendingReply<int> GetInterfaceVersion();
    QDBusPendingReply<QByteArray> GetSerial();
};

#endif //NFCD_TAGCLASSIC_DBUS_IFACE_H