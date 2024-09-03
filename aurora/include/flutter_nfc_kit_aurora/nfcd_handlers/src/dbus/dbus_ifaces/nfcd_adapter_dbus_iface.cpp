#include "nfcd_adapter_dbus_iface.h"
#include "../nfcd_constants.h"

NfcdAdapterDBusIface::NfcdAdapterDBusIface(const QString &path, QObject *parent): QDBusAbstractInterface(
    NfcdConstants::nfcdService, path, 
    NfcdConstants::nfcdAdapterIface, 
    QDBusConnection::systemBus(), parent) { 
    //empty
}

QDBusPendingReply<int> NfcdAdapterDBusIface::GetInterfaceVersion(){
    return asyncCallWithArgumentList(QStringLiteral("GetInterfaceVersion"), QList<QVariant>());
}

QDBusPendingReply<bool> NfcdAdapterDBusIface::GetEnabled(){
    return asyncCallWithArgumentList(QStringLiteral("GetEnabled"), QList<QVariant>());
}

QDBusPendingReply<uint> NfcdAdapterDBusIface::GetMode(){
    return asyncCallWithArgumentList(QStringLiteral("GetMode"), QList<QVariant>());
}

QDBusPendingReply<bool> NfcdAdapterDBusIface::GetPowered(){
    return asyncCallWithArgumentList(QStringLiteral("GetPowered"), QList<QVariant>());
}

QDBusPendingReply<uint> NfcdAdapterDBusIface::GetSupportedModes(){
    return asyncCallWithArgumentList(QStringLiteral("GetSupportedModes"), QList<QVariant>());
}

QDBusPendingReply<bool> NfcdAdapterDBusIface::GetTargetPresent(){
    return asyncCallWithArgumentList(QStringLiteral("GetTargetPresent"), QList<QVariant>());
}


QDBusPendingReply<QList<QDBusObjectPath>> NfcdAdapterDBusIface::GetTags(){
    return asyncCallWithArgumentList(QStringLiteral("GetTags"), QList<QVariant>());
}

#include "moc_nfcd_adapter_dbus_iface.cpp"