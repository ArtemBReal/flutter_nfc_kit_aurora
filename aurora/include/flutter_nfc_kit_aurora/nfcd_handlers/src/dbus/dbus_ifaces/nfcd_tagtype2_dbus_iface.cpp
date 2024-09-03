#include "nfcd_constants.h"
#include "nfcd_tagtype2_dbus_iface.h"

NfcdTagType2DBusIface::NfcdTagType2DBusIface(const QString &path, QObject *parent) : QDBusAbstractInterface(
                                            NfcdConstants::nfcdService, path,
                                            NfcdConstants::nfcdTagType2Iface,
                                            QDBusConnection::systemBus(), parent){

    //empty
}

QDBusPendingReply<int> NfcdTagType2DBusIface::GetInterfaceVersion(){
    return asyncCallWithArgumentList(QStringLiteral("GetInterfaceVersion"), QList<QVariant>());
}

QDBusPendingReply<uint> NfcdTagType2DBusIface::GetBlockSize(){
    return asyncCallWithArgumentList(QStringLiteral("GetBlockSize"), QList<QVariant>());
}

QDBusPendingReply<uint> NfcdTagType2DBusIface::GetDataSize(){
    return asyncCallWithArgumentList(QStringLiteral("GetDataSize"), QList<QVariant>());
}

QDBusPendingReply<uint> NfcdTagType2DBusIface::Write(uint sector, uint block, const QByteArray &data){
    QList<QVariant> arguments = {
        QVariant::fromValue(sector),
        QVariant::fromValue(block),
        QVariant::fromValue(data),
    };

    return asyncCallWithArgumentList(QStringLiteral("Write"), arguments);
}

QDBusPendingReply<uint> NfcdTagType2DBusIface::WriteData(uint offset, const QByteArray &data){
    QList<QVariant> arguments = {
        QVariant::fromValue(offset),
        QVariant::fromValue(data),
    };
    return asyncCallWithArgumentList(QStringLiteral("WriteData"), arguments);
}

QDBusPendingReply<QByteArray> NfcdTagType2DBusIface::Read(uint sector, uint block){
    QList<QVariant> arguments = {
        QVariant::fromValue(sector),
        QVariant::fromValue(block),
    };
    return asyncCallWithArgumentList(QStringLiteral("Read"), arguments);
}

QDBusPendingReply<QByteArray> NfcdTagType2DBusIface::ReadData(uint offset, uint maxbytes){
    QList<QVariant> arguments = {
        QVariant::fromValue(offset),
        QVariant::fromValue(maxbytes),
    };
    return asyncCallWithArgumentList(QStringLiteral("ReadData"), arguments);
}

QDBusPendingReply<QByteArray> NfcdTagType2DBusIface::ReadAllData(){
    return asyncCallWithArgumentList(QStringLiteral("ReadAllData"), QList<QVariant>());
}

QDBusPendingReply<QByteArray> NfcdTagType2DBusIface::GetSerial(){
    return asyncCallWithArgumentList(QStringLiteral("GetSerial"), QList<QVariant>());
}

#include "moc_nfcd_tagtype2_dbus_iface.cpp"