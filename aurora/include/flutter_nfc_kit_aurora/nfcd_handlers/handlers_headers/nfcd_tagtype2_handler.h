#ifndef NFCD_TAGTYPE2_HANDLER_H
#define NFCD_TAGTYPE2_HANDLER_H

#include "qt_headers.h"
#include "nfcd_typifier.h"

class NfcdTagType2HandlerPrivate;

class NfcdTagType2Handler : public QObject{
    Q_OBJECT

    Q_PROPERTY(QString tagPath READ tagPath WRITE setTagPath NOTIFY tagPathChanged)
    Q_PROPERTY(QString interfaceVersion READ interfaceVersion NOTIFY interfaceVersionChanged)
    Q_PROPERTY(quint32 blockSize READ blockSize NOTIFY blockSizeChanged)
    Q_PROPERTY(quint32 dataSize READ dataSize NOTIFY dataSizeChanged)
    Q_PROPERTY(QByteArray serial READ serial NOTIFY serialChanged)

public:
    explicit NfcdTagType2Handler(QObject *parent = nullptr);

    QString tagPath() const;
    void setTagPath(const QString &tagPath);

    QString interfaceVersion();
    quint32 blockSize();
    quint32 dataSize();
    QByteArray serial();

    Q_INVOKABLE quint32 write(quint32 sector, quint32 block, const QString &data);
    Q_INVOKABLE quint32 writeData(quint32 offset, const QString &data);
    Q_INVOKABLE QString read(quint32 sector, quint32 block);
    Q_INVOKABLE QString readData(quint32 offset, quint32 maxbytes);
    Q_INVOKABLE QByteArray readAllData();

signals:
    void tagPathChanged(const QString &tagPath);
    void interfaceVersionChanged(const QString &interfaceVersion);
    void blockSizeChanged(quint32 blockSize);
    void dataSizeChanged(quint32 dataSize);
    void serialChanged(const QByteArray &serial);

private:
    QSharedPointer<NfcdTagType2HandlerPrivate> m_data{ nullptr };
};

#endif //NFCD_TAGTYPE2_HANDLER_H
