#include "nfcd_constants.h"
#include "nfcd_isodep_dbus_iface.h"

NfcdIsoDepDBusIface::NfcdIsoDepDBusIface(const QString &path, QObject *parent) : QDBusAbstractInterface(
                    NfcdConstants::nfcdService, path,
                    NfcdConstants::nfcdIsoDepIface,
                    QDBusConnection::systemBus(), parent){

    //empty
}

/*
QDBusPendingReply<QVector<QPair<QString,QVariant>>> NfcdIsoDepDBusIface::GetActivationParameters(){
    return asyncCallWithArgumentList(QStringLiteral("GetActivationParameters"), QList<QVariant>());
}
*/

QDBusPendingReply<int> NfcdIsoDepDBusIface::GetInterfaceVersion(){
    return asyncCallWithArgumentList(QStringLiteral("GetInterfaceVersion"), QList<QVariant>());
}

QDBusPendingReply<QByteArray, uchar, uchar> NfcdIsoDepDBusIface::Transmit(uchar cla, uchar ins, 
                                                                          uchar p1, uchar p2, 
                                                                          const QByteArray &data, uint le){
    QList<QVariant> arguments = {
        QVariant::fromValue(cla), QVariant::fromValue(ins), QVariant::fromValue(p1),
        QVariant::fromValue(p2), QVariant::fromValue(data), QVariant::fromValue(le),
    };

    return asyncCallWithArgumentList(QStringLiteral("Transmit"), arguments);
}

QDBusPendingReply<> NfcdIsoDepDBusIface::Reset(){
    return asyncCallWithArgumentList(QStringLiteral("Reset"), QList<QVariant>());
}

#include "moc_nfcd_isodep_dbus_iface.cpp"