#include "nfcd_constants.h"
#include "nfcd_ndef_dbus_iface.h"

NfcdNdefDBusIface::NfcdNdefDBusIface(const QString &path, QObject *parent) : QDBusAbstractInterface(
                                     NfcdConstants::nfcdService,path,
                                     NfcdConstants::nfcdNdefIface,
                                     QDBusConnection::systemBus(), parent){
    //empty
}


QDBusPendingReply<int> NfcdNdefDBusIface::GetInterfaceVersion(){
    return asyncCallWithArgumentList(QStringLiteral("GetInterfaceVersion"), QList<QVariant>());
}


QDBusPendingReply<uint> NfcdNdefDBusIface::GetFlags(){
    return asyncCallWithArgumentList(QStringLiteral("GetFlags"), QList<QVariant>());
}

QDBusPendingReply<uint> NfcdNdefDBusIface::GetTypeNameFormat(){
    return asyncCallWithArgumentList(QStringLiteral("GetTypeNameFormat"), QList<QVariant>());
}

QDBusPendingReply<QByteArray> NfcdNdefDBusIface::GetType(){
    return asyncCallWithArgumentList(QStringLiteral("GetType"), QList<QVariant>());
}


QDBusPendingReply<QByteArray> NfcdNdefDBusIface::GetId(){
    return asyncCallWithArgumentList(QStringLiteral("GetId"), QList<QVariant>());
}

QDBusPendingReply<QByteArray> NfcdNdefDBusIface::GetPayload(){
    return asyncCallWithArgumentList(QStringLiteral("GetPayload"), QList<QVariant>());
}

QDBusPendingReply<QByteArray> NfcdNdefDBusIface::GetRawData(){
    return asyncCallWithArgumentList(QStringLiteral("GetRawData"), QList<QVariant>());
}

QDBusPendingReply<QStringList> NfcdNdefDBusIface::GetInterfaces()
{
    return asyncCallWithArgumentList(QStringLiteral("GetInterfaces"), QList<QVariant>());
}

#include "moc_nfcd_ndef_dbus_iface.cpp"