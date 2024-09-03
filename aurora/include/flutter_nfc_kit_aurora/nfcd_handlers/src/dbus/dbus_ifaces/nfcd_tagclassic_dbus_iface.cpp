#include "nfcd_tagclassic_dbus_iface.h"
#include "../nfcd_constants.h"

NfcdTagClassicDBusIface::NfcdTagClassicDBusIface(const QString &path, QObject *parent) : QDBusAbstractInterface(NfcdConstants::nfcdService,
    path, NfcdConstants::nfcdTagClassicIface, 
    QDBusConnection::systemBus(), parent) {

    //empty
}

QDBusPendingReply<int> NfcdTagClassicDBusIface::GetInterfaceVersion(){
    return asyncCallWithArgumentList(QStringLiteral("GetInterfaceVersion"), QList<QVariant>());
}

QDBusPendingReply<QByteArray> NfcdTagClassicDBusIface::GetSerial() {
    return asyncCallWithArgumentList(QStringLiteral("GetSerial"), QList<QVariant>());
}

#include "moc_nfcd_tagclassic_dbus_iface.cpp"
