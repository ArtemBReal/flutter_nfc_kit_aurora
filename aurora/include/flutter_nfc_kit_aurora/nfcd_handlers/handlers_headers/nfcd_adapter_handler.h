#ifndef NFCD_ADAPTER_HANDLER_H
#define NFCD_ADAPTER_HANDLER_H

#include "qt_headers.h"
#include "nfcd_typifier.h"

class NfcdTagsModelPrivate;

class NfcdTagsModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit NfcdTagsModel(QObject *parent = nullptr) = delete;
    NfcdTagsModel(NfcdTagsModelPrivate *data, QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    QVariant data (const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent) const override;

private:
    friend class NfcdTagsModelPrivate;
    QSharedPointer<NfcdTagsModelPrivate> m_data { nullptr };    
};

class NfcdAdapterHandlerPrivate;

class NfcdAdapterHandler : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString adapterPath READ adapterPath WRITE setAdapterPath NOTIFY adapterPathChanged)
    Q_PROPERTY(QString interfaceVersion READ interfaceVersion NOTIFY interfaceVersionChanged)
    Q_PROPERTY(bool enabled READ enabled NOTIFY enabledChanged)
    Q_PROPERTY(bool powered READ powered NOTIFY poweredChanged)
    Q_PROPERTY(bool targetPresent READ targetPresent NOTIFY targetPresentChanged)
    Q_PROPERTY(QString supportedModes READ supportedModes NOTIFY supportedModesChanged)
    Q_PROPERTY(QString mode READ mode NOTIFY modeChanged)
    Q_PROPERTY(NfcdTagsModel *tagsModel READ tagsModel NOTIFY tagsModelChanged)

public:
    explicit NfcdAdapterHandler(QObject *parent = nullptr);

    QString adapterPath() const;
    void setAdapterPath(const QString &adapterPath);

    QString interfaceVersion();
    bool enabled();
    bool powered();
    bool targetPresent();
    QString supportedModes();
    QString mode();
    QString tagsList();
    NfcdTagsModel *tagsModel();

signals:
    void adapterPathChanged(const QString &adapterPath);
    void interfaceVersionChanged(const QString &interfaceVersion);
    void enabledChanged(bool enabled);
    void poweredChanged(bool powered);
    void targetPresentChanged(bool targetPresent);
    void supportedModesChanged(QString supportedModes);
    void modeChanged(QString mode);
    void tagsModelChanged(NfcdTagsModel *tagsModel);

private:
    QSharedPointer<NfcdAdapterHandlerPrivate> m_data { nullptr };
};

#endif //NFCD_ADAPTER_HANDLER_H