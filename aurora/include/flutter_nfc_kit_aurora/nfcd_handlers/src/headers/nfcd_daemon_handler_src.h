#ifndef NFCD_DAEMON_HANDLER_SRC_H
#define NFCD_DAEMON_HANDLER_SRC_H

#include "qt_headers.h"
#include "nfcd_typifier.h"
#include "nfcd_daemon_dbus_iface.h"
#include "nfcd_adapter_dbus_iface.h"

class NfcdAdaptersModel;

class NfcdAdaptersModelPrivate : public QObject
{
    Q_OBJECT

public:
    enum Role {
        PathRole = Qt::UserRole + 1,
        EnabledRole,
        PoweredRole,
    };

public:
    NfcdAdaptersModelPrivate(NfcdDaemonDBusIface *iface);

    void setParent(NfcdAdaptersModel *parent);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;

private slots:
    void updateAdapters(const QList<QDBusObjectPath> &adapters);

private:
    NfcdAdaptersModel *m_parent{ nullptr };
    NfcdDaemonDBusIface *m_daemon{ nullptr };
    QMap<QString, QSharedPointer<NfcdAdapterDBusIface>> m_adapters{};
    QHash<int, QByteArray> m_roleNames{};
};

class NfcdDaemonHandlerPrivate : public QObject
{
    Q_OBJECT

public:
    explicit NfcdDaemonHandlerPrivate(QObject *parent = nullptr);

    QString interfaceVersion();
    QString daemonVersion();
    QString adaptersList();
    NfcdAdaptersModel *adaptersModel();
    QString daemonMode();

private:
    QSharedPointer<NfcdDaemonDBusIface> m_iface{ nullptr };
    QSharedPointer<NfcdAdaptersModel> m_model{ nullptr };
};


#endif // NFCD_DAEMON_HANDLER_SRC_H