#ifndef NFCD_TAGCLASSIC_HANDLER_H
#define NFCD_TAGCLASSIC_HANDLER_H

#include "qt_headers.h"
#include "nfcd_typifier.h"

class NfcdTagClassicHandlerPrivate;

class NfcdTagClassicHandler : public QObject{
    Q_OBJECT

    Q_PROPERTY(QString tagPath READ tagPath WRITE setTagPath NOTIFY tagPathChanged)
    Q_PROPERTY(QString interfaceVersion READ interfaceVersion NOTIFY interfaceVersionChanged)
    Q_PROPERTY(QByteArray serial READ serial NOTIFY serialChanged)


public:
    explicit NfcdTagClassicHandler(QObject *parent = nullptr);

    QString tagPath() const;
    void setTagPath(const QString &tagPath);

    QString interfaceVersion();
    QByteArray serial();

signals:
    void tagPathChanged(const QString &tagPath);
    void interfaceVersionChanged(QString interfaceVersion);
    void serialChanged(QByteArray serial);

private:
    QSharedPointer<NfcdTagClassicHandlerPrivate> m_data{ nullptr };
};

#endif //NFCD_TAGCLASSIC_HANDLER_H
