#ifndef NFCD_TAG_HANDLER_H
#define NFCD_TAG_HANDLER_H

#include "qt_headers.h"
#include "nfcd_typifier.h"

class NfcdTagHandlerPrivate;

class NfcdTagHandler : public QObject {
    Q_OBJECT

public:
    explicit NfcdTagHandler(QObject *parent = nullptr);

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

    Q_INVOKABLE void acquire(bool wait);
    Q_INVOKABLE void deactivate();
    Q_INVOKABLE void release();
    Q_INVOKABLE QString transceive(const QString &data);

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
    QSharedPointer<NfcdTagHandlerPrivate> m_data { nullptr };
};

#endif //NFCD_TAG_HANDLER_H