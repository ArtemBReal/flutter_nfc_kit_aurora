#ifndef NFCD_NDEF_HANDLER_H
#define NFCD_NDEF_HANDLER_H

#include "qt_headers.h"
#include "nfcd_typifier.h"

class NfcdNdefHandlerPrivate;

class NfcdNdefHandler : public QObject{
    Q_OBJECT

    Q_PROPERTY(QString recordPath READ recordPath WRITE setRecordPath NOTIFY recordPathChanged)
    Q_PROPERTY(QString interfaceVersion READ interfaceVersion NOTIFY interfaceVersionChanged)
    Q_PROPERTY(QString flags READ flags NOTIFY flagsChanged)
    Q_PROPERTY(QString typeNameFormat READ typeNameFormat NOTIFY typeNameFormatChanged)
    Q_PROPERTY(QByteArray type READ type NOTIFY typeChanged)
    Q_PROPERTY(QByteArray id READ id NOTIFY idChanged)
    Q_PROPERTY(QByteArray payload READ payload NOTIFY payloadChanged)
    Q_PROPERTY(QByteArray rawData READ rawData NOTIFY rawDataChanged)
    Q_PROPERTY(QString interfaces READ interfaces NOTIFY interfacesChanged)

public:
    explicit NfcdNdefHandler(QObject *parent = nullptr);

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
    QSharedPointer<NfcdNdefHandlerPrivate> m_data{ nullptr };
};

#endif //NFCD_NDEF_HANDLER_H
