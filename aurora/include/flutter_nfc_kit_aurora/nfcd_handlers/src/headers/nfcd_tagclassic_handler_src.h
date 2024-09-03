#ifndef NFCD_TAGCLASSIC_HANDLER_SRC_H
#define NFCD_TAGCLASSIC_HANDLER_SRC_H

#include "qt_headers.h"
#include "nfcd_typifier.h"
#include "nfcd_tagclassic_dbus_iface.h"

class NfcdTagClassicHandlerPrivate : public QObject{
    Q_OBJECT

public:
    explicit NfcdTagClassicHandlerPrivate(QObject *parent = nullptr);

    QString tagPath() const;
    void setTagPath(const QString &tagPath);

    QString interfaceVersion();
    QByteArray serial();

signals:
    void tagPathChanged(const QString &tagPath);
    void interfaceVersionChanged(QString interfaceVersion);
    void serialChanged(QByteArray serial);

private:
    QSharedPointer<NfcdTagClassicDBusIface> m_iface{ nullptr };
    QString m_tagPath{};
};

#endif //NFCD_TAGCLASSIC_HANDLER_SRC_H
