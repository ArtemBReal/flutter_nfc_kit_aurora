#include "nfcd_tag_dbus_iface.h"
#include "../nfcd_constants.h"

NfcdTagDBusIface::NfcdTagDBusIface(const QString &path, QObject *parent) : QDBusAbstractInterface(NfcdConstants::nfcdService,
    path, NfcdConstants::nfcdTagIface, 
    QDBusConnection::systemBus(), parent) {
    //empty
}

QDBusPendingReply<int> NfcdTagDBusIface::GetInterfaceVersion(){
    return asyncCallWithArgumentList(QStringLiteral("GetInterfaceVersion"), QList<QVariant>());
}

QDBusPendingReply<bool> NfcdTagDBusIface::GetPresent(){
    return asyncCallWithArgumentList(QStringLiteral("GetPresent"), QList<QVariant>());
}

QDBusPendingReply<uint> NfcdTagDBusIface::GetProtocol() {
    return asyncCallWithArgumentList(QStringLiteral("GetProtocol"), QList<QVariant>());
}

QDBusPendingReply<uint> NfcdTagDBusIface::GetTechnology(){
    return asyncCallWithArgumentList(QStringLiteral("GetTechnology"), QList<QVariant>());
}

QDBusPendingReply<uint> NfcdTagDBusIface::GetType(){
    return asyncCallWithArgumentList(QStringLiteral("GetType"), QList<QVariant>());
}

QDBusPendingReply<QStringList> NfcdTagDBusIface::GetInterfaces(){
    return asyncCallWithArgumentList(QStringLiteral("GetInterfaces"), QList<QVariant>());
}

QDBusPendingReply<QVariantMap> NfcdTagDBusIface::GetPollParameters(){
    return asyncCallWithArgumentList(QStringLiteral("GetPollParameters"), QList<QVariant>());
}

QDBusPendingReply<QList<QDBusObjectPath>> NfcdTagDBusIface::GetNdefRecords(){
    return asyncCallWithArgumentList(QStringLiteral("GetNdefRecords"), QList<QVariant>());
}

QDBusPendingReply<> NfcdTagDBusIface::Acquire(bool wait){
    QList<QVariant> arguments {
        QVariant::fromValue(wait),
    };
    return asyncCallWithArgumentList(QStringLiteral("Acquire"), arguments);
}

QDBusPendingReply<> NfcdTagDBusIface::Deactivate() {
    return asyncCallWithArgumentList(QStringLiteral("Deactivate"), QList<QVariant>());
}

QDBusPendingReply<> NfcdTagDBusIface::Release() {
    return asyncCallWithArgumentList(QStringLiteral("Release"), QList<QVariant>());
}

QDBusPendingReply<QByteArray> NfcdTagDBusIface::Transceive(const QByteArray &data){
    QList<QVariant> arguments{
        QVariant::fromValue(data),
    };
    return asyncCallWithArgumentList(QStringLiteral("Transceive"), arguments);
}

#include "moc_nfcd_tag_dbus_iface.cpp"