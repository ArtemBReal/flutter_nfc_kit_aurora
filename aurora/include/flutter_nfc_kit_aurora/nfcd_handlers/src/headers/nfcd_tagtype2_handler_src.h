#ifndef NFCD_TAGTYPE2_HANDLER_SRC_H
#define NFCD_TAGTYPE2_HANDLER_SRC_H

#include "qt_headers.h"
#include "nfcd_typifier.h"
#include "nfcd_tagtype2_dbus_iface.h"

class NfcdTagType2HandlerPrivate : public QObject{
    Q_OBJECT

public:
    explicit NfcdTagType2HandlerPrivate(QObject *parent = nullptr);

    QString tagPath() const;
    void setTagPath(const QString &tagPath);

    QString interfaceVersion();
    quint32 blockSize();
    quint32 dataSize();
    quint32 write(quint32 sector, quint32 block, const QString &data);
    quint32 writeData(quint32 offset, const QString &data);
    QString read(quint32 sector, quint32 block);
    QString readData(quint32 offset, quint32 maxbytes);
    QByteArray readAllData();
    QByteArray serial();

signals:
    void tagPathChanged(const QString &tagPath);
    void interfaceVersionChanged(const QString &interfaceVersion);
    void blockSizeChanged(quint32 blockSize);
    void dataSizeChanged(quint32 dataSize);
    void serialChanged(const QByteArray &serial);

private:
    QSharedPointer<NfcdTagType2DBusIface> m_iface{ nullptr };
    QString m_tagPath{};
};

#endif //NFCD_TAGTYPE2_HANDLER_SRC_H
