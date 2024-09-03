#ifndef NFCD_ISO_HANDLER_SRC_H
#define NFCD_ISO_HANDLER_SRC_H

#include "qt_headers.h"
#include "nfcd_typifier.h"
#include "nfcd_isodep_dbus_iface.h"

class NfcdIsoDepHandlerPrivate : public QObject{
    Q_OBJECT

public:
    explicit NfcdIsoDepHandlerPrivate(QObject *parent = nullptr);

    QString tagPath() const;
    void setTagPath(const QString &tagPath);

    QString interfaceVersion();
    QString activationParamaters();
    QString transmit(uchar cla, uchar ins, uchar p1, 
                              uchar p2, QString &data, uint le);
    void reset();

signals:
    void tagPathChanged(const QString &tagPath);
    void interfaceVersionChanged(const QString &interfaceVersion);
    void activationParametersChanged(QString activationPramaters);

private:
    QSharedPointer<NfcdIsoDepDBusIface> m_iface{ nullptr };
    QString m_tagPath{};
};

#endif //NFCDISODEPHANDLER_P_H
