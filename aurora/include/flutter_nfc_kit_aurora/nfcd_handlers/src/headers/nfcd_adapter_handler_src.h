#ifndef NFCD_ADAPTER_HANDLER_SRC_H
#define NFCD_ADAPTER_HANDLER_SRC_H

#include "qt_headers.h"
#include "nfcd_typifier.h"
#include "nfcd_tag_dbus_iface.h"
#include "nfcd_adapter_dbus_iface.h"

class NfcdTagsModel;

class NfcdTagsModelPrivate : public QObject {
    Q_OBJECT

public:
    enum Role {
        PathRole = Qt::UserRole + 1,
        ProtocolRole,
        TechnologyRole,
        TypeRole,
    };

public:
    NfcdTagsModelPrivate(NfcdAdapterDBusIface *iface);

    void setParent(NfcdTagsModel *parent);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;

private slots:
    void updateTags(const QList<QDBusObjectPath> &tags);

private:
    NfcdTagsModel *m_parent { nullptr };
    NfcdAdapterDBusIface *m_adapter { nullptr };
    QMap<QString, QSharedPointer<NfcdTagDBusIface>> m_tags {};
    QHash<int, QByteArray> m_roleNames {};
};

class NfcdAdapterHandlerPrivate : public QObject {
    Q_OBJECT

public:
    explicit NfcdAdapterHandlerPrivate(QObject *parent = nullptr);

    QString adapterPath() const;
    void setAdapterPath(const QString &adapterPath);

    QString interfaceVesrion();
    bool enabled();
    bool powered();
    bool targetPresent();
    QString supportedModes();
    QString mode();
    QString tagsList();
    NfcdTagsModel *tagsModel();

signals:
    void adapterPathChanged(const QString &adapterPath);
    void interfaceVersionChanged(const QString &interfaceVesrion);
    void enabledChanged(bool enabled);
    void poweredChanged(bool powered);
    void targetPresentChanged(bool targetPresent);
    void supportedModesChanged(QString supportedModes);
    void modeChanged(QString mode);
    void tagsModelChanged(NfcdTagsModel *tagsModel);

private:
    QSharedPointer<NfcdAdapterDBusIface> m_iface { nullptr };
    QSharedPointer<NfcdTagsModel> m_model { nullptr };
    QString m_adapterPath {};
};

#endif //NFCD_ADAPTER_HANDLER_SRC_H