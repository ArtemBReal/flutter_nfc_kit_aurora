#ifndef NFCD_TAG_HANDLER_SRC_H
#define NFCD_TAG_HANDLER_SRC_H

#include "qt_headers.h"
#include "nfcd_typifier.h"
#include "nfcd_tag_dbus_iface.h"

class NfcdTagHandlerPrivate : public QObject {
    Q_OBJECT

public:
    explicit NfcdTagHandlerPrivate(QObject *parent = nullptr);
    
    QString tagPath() const;
    void setTagPath(const QString &tagPath);

    QString interfaceVersion();
    bool present();
    QString protocol();
    QString technology();
    QString type();
    QString interfaces();
    QString ndefRecords();
    QVariantMap pollParameters();
    void acquire(bool wait);
    void deactivate();
    void release();
    QString transceive(const QString &data);

signals:
    void tagPathChanged(const QString &tagPath);
    void interfaceVersionChanged(const QString &interfaceVersion);
    void presentChanged(bool present);
    void protocolChanged(QString protocol);
    void technologyChanged(QString technology);
    void typeChanged(QString type);
    void interfacesChanged(QString interfaces);
    void ndefRecordsChanged(QString ndefRecords);
    void pollParametersChanged(const QVariantMap &pollParameters);
    void removed();

private:
    QSharedPointer<NfcdTagDBusIface> m_iface { nullptr };
    QString m_tagPath {};
};

#endif //NFCD_TAG_HANDLER_SRC_H