#include "nfcd_daemon_dbus_iface.h"
#include "../nfcd_constants.h"

NfcdDaemonDBusIface::NfcdDaemonDBusIface(QObject *parent) : 
    QDBusAbstractInterface(NfcdConstants::nfcdService, 
    NfcdConstants::nfcdPath, 
    NfcdConstants::nfcdDaemonIface, 
    QDBusConnection::systemBus(), parent){ 
    //empty
}


QDBusPendingReply<int> NfcdDaemonDBusIface::GetInterfaceVersion(){
    return asyncCallWithArgumentList(QStringLiteral("GetInterfaceVersion"), QList<QVariant>());
}

QDBusPendingReply<int> NfcdDaemonDBusIface::GetDaemonVersion(){
     return asyncCallWithArgumentList(QStringLiteral("GetDaemonVersion"), QList<QVariant>());
}

QDBusPendingReply<QList<QDBusObjectPath>> NfcdDaemonDBusIface::GetAdapters(){
     return asyncCallWithArgumentList(QStringLiteral("GetAdapters"), QList<QVariant>());
}

QDBusPendingReply<quint8> NfcdDaemonDBusIface::GetMode(){
    return asyncCallWithArgumentList(QStringLiteral("GetMode"), QList<QVariant>());
}

#include "moc_nfcd_daemon_dbus_iface.cpp"