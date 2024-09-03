#ifndef NFCD_ADAPTER_DBUS_IFACE_H
#define NFCD_ADAPTER_DBUS_IFACE_H

#include "qt_headers.h"

class NfcdAdapterDBusIface : public QDBusAbstractInterface
{
    Q_OBJECT

public:
    NfcdAdapterDBusIface(const QString &path, QObject *parent = nullptr);

public slots:
    QDBusPendingReply<bool> GetEnabled();
    QDBusPendingReply<int> GetInterfaceVersion();
    QDBusPendingReply<uint> GetMode();
    QDBusPendingReply<bool> GetPowered();
    QDBusPendingReply<uint> GetSupportedModes();
    QDBusPendingReply<QList<QDBusObjectPath>> GetTags();
    QDBusPendingReply<bool> GetTargetPresent();

signals:
    void EnabledChanged(bool enabled);
    void PoweredChanged(bool powered);
    void TargetPresentChanged(bool targetPresent);
    void ModeChanged(uint mode);
    void TagsChanged(const QList<QDBusObjectPath> &tags);
};

#endif // NFCD_ADAPTER_DBUS_IFACE_H
