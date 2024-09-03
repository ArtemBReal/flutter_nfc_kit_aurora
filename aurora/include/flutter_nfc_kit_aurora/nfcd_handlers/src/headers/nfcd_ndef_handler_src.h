#ifndef NFCD_NDEF_HANDLER_SRC_H
#define NFCD_NDEF_HANDLER_SRC_H

#include "qt_headers.h"
#include "nfcd_typifier.h"
#include "nfcd_ndef_dbus_iface.h"

class NfcdNdefHandlerPrivate : public QObject{
    Q_OBJECT

public:
    explicit NfcdNdefHandlerPrivate(QObject *parent = nullptr);

    QString recordPath() const;
    void setRecordPath(const QString &recordPath);

    QString interfaceVersion();
    QString flags();
    QString typeNameFormat();
    QByteArray type();
    QByteArray id();
    QByteArray payload();
    QByteArray rawData();
    QString interfaces();

signals:
    void recordPathChanged(const QString &recordPath);
    void interfaceVersionChanged(const QString &interfaceVersion);
    void flagsChanged(QString flags);
    void typeNameFormatChanged(QString typeNameFormat);
    void typeChanged(QByteArray type);
    void idChanged(QByteArray id);
    void payloadChanged(QByteArray payload);
    void rawDataChanged(QByteArray rawData);
    void interfacesChanged(QString interfaces);

private:
    QSharedPointer<NfcdNdefDBusIface> m_iface{ nullptr };
    QString m_recordPath{};
};

#endif //NFCD_NDEF_HANDLER_SRC_H
