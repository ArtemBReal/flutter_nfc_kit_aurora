#ifndef NFCD_ISODEP_DBUS_IFACE_H
#define NFCD_ISODEP_DBUS_IFACE_H

#include "qt_headers.h"

class NfcdIsoDepDBusIface : public QDBusAbstractInterface {
    Q_OBJECT

public:
    NfcdIsoDepDBusIface(const QString &path, QObject *parent = nullptr);

public slots:
    QDBusPendingReply<int> GetInterfaceVersion();
    //QDBusPendingReply<QVector<QPair<QString,QVariant>>> GetActivationParameters();
    QDBusPendingReply<QByteArray, uchar, uchar> Transmit(uchar cla, uchar ins, uchar p1, uchar p2,
                                                         const QByteArray &data, uint le);
    QDBusPendingReply<> Reset();
};

#endif //NFCD_ISODEP_DBUS_IFACE_H