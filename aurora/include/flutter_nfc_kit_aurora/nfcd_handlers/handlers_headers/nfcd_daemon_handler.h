#ifndef NFCD_DAEMON_HANDLER_H
#define NFCD_DAEMON_HANDLER_H

#include "qt_headers.h"
#include "nfcd_typifier.h"

class NfcdAdaptersModelPrivate;

class NfcdAdaptersModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit NfcdAdaptersModel(QObject *parent = nullptr) = delete;
    NfcdAdaptersModel(NfcdAdaptersModelPrivate *data, QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent) const override;

private:
    friend class NfcdAdaptersModelPrivate;
    QSharedPointer<NfcdAdaptersModelPrivate> m_data{ nullptr };
};

class NfcdDaemonHandlerPrivate;

class NfcdDaemonHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString interfaceVersion READ interfaceVersion CONSTANT)
    Q_PROPERTY(QString daemonVersion READ daemonVersion CONSTANT)
    Q_PROPERTY(QString adaptersList READ adaptersList CONSTANT)
    Q_PROPERTY(NfcdAdaptersModel *adaptersModel READ adaptersModel CONSTANT)

public:
    explicit NfcdDaemonHandler(QObject *parent = nullptr);

    QString interfaceVersion();
    QString daemonVersion();
    QString adaptersList();
    NfcdAdaptersModel *adaptersModel();
    QString daemonMode();

private:
    QSharedPointer<NfcdDaemonHandlerPrivate> m_data{ nullptr };
};



#endif // NFCD_DAEMON_HANDLER_H