#include <QtCore/QVersionNumber>

#include "nfcd_daemon_handler.h"
#include "nfcd_daemon_handler_src.h"
#include "nfcd_adapter_handler_src.h"

NfcdAdaptersModelPrivate::NfcdAdaptersModelPrivate(NfcdDaemonDBusIface *iface) : QObject(nullptr), m_daemon(iface)
{
    m_roleNames[NfcdAdaptersModelPrivate::PathRole] = QByteArrayLiteral("path");
    m_roleNames[NfcdAdaptersModelPrivate::EnabledRole] = QByteArrayLiteral("enabled");
    m_roleNames[NfcdAdaptersModelPrivate::PoweredRole] = QByteArrayLiteral("powered");

    updateAdapters(iface->GetAdapters().value());

    connect(iface, &NfcdDaemonDBusIface::AdaptersChanged,
            this,
            &NfcdAdaptersModelPrivate::updateAdapters);
}

void NfcdAdaptersModelPrivate::updateAdapters(const QList<QDBusObjectPath> &adapters){
    QStringList adaptersPaths;

    for (const auto &adapter : adapters){
        adaptersPaths.append(adapter.path());
    }

    if (m_parent){
        m_parent->beginResetModel();
    }

    for (const auto &adapterPath : adaptersPaths){
        if (m_adapters.contains(adapterPath)){
            continue;
        }

        QSharedPointer<NfcdAdapterDBusIface> adapterPtr(new NfcdAdapterDBusIface(adapterPath));
        m_adapters.insert(adapterPath, adapterPtr);

        connect(adapterPtr.data(), &NfcdAdapterDBusIface::EnabledChanged,
                [this](){
                    if (m_parent){
                        m_parent->beginResetModel();
                        m_parent->endResetModel();
                    }
                });
        connect(adapterPtr.data(), &NfcdAdapterDBusIface::PoweredChanged,
                [this](){
                    if (m_parent){
                        m_parent->beginResetModel();
                        m_parent->endResetModel();
                    }
                });
    } // for &adapterPath

    QMapIterator<QString, QSharedPointer<NfcdAdapterDBusIface>> it(m_adapters);
    while (it.hasNext()){
        it.next();
        if (adaptersPaths.contains(it.key())){
            continue;
        }

        m_adapters.take(it.key()).reset();
    }

    if (m_parent){
        m_parent->endResetModel();
    }
}

void NfcdAdaptersModelPrivate::setParent(NfcdAdaptersModel *parent){
    QObject::setParent(parent);
    m_parent = parent;
}

QHash<int, QByteArray> NfcdAdaptersModelPrivate::roleNames() const {
    return m_roleNames;
}

QVariant NfcdAdaptersModelPrivate::data(const QModelIndex &index, int role) const {
    if (index.row() >= m_adapters.count()){
        return QVariant();
    }

    auto key = m_adapters.keys().at(index.row());
    auto value = m_adapters.value(key);
    if (role == NfcdAdaptersModelPrivate::PathRole){
        return key;
    }
    else if (role == NfcdAdaptersModelPrivate::EnabledRole){
        return value->GetEnabled().value();
    }
    else if (role == NfcdAdaptersModelPrivate::PoweredRole){
        return value->GetPowered().value();
    }

    return QVariant();
}

int NfcdAdaptersModelPrivate::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()){
        return 0;
    }

    return m_adapters.count();
}

NfcdDaemonHandlerPrivate::NfcdDaemonHandlerPrivate(QObject *parent) : QObject(parent),
                                                                      m_iface(new NfcdDaemonDBusIface(this)),
                                                                      m_model(new NfcdAdaptersModel(new NfcdAdaptersModelPrivate(m_iface.data()), this))
{
    // empty
}

QString NfcdDaemonHandlerPrivate::interfaceVersion(){
    return QStringLiteral("%1").arg(m_iface->GetInterfaceVersion().value());
}

QString NfcdDaemonHandlerPrivate::daemonVersion(){
    qint32 daemonVersion = m_iface->GetDaemonVersion().value();
    QVersionNumber daemonVersionNumber(((daemonVersion) >> 24) & 0x7f,
                                       ((daemonVersion) >> 12) & 0xfff,
                                       (daemonVersion) & 0x0fff);

    return QStringLiteral("%1").arg(daemonVersionNumber.toString());
}

QString NfcdDaemonHandlerPrivate::adaptersList(){
    QList<QDBusObjectPath> reply = m_iface->GetAdapters().value();
    QString adaptersList;

    for (const auto &adapter : reply){
        adaptersList += adapter.path();
        adaptersList += QStringLiteral("&");
    }
    return adaptersList;
}

QString NfcdDaemonHandlerPrivate::daemonMode(){
    quint8 daemonModeNumber = m_iface->GetMode().value();
    QString daemonModeString = QString::number(daemonModeNumber);
    return QStringLiteral("%1").arg(daemonModeString);
}


//------------------------------------------------------------

NfcdAdaptersModel *NfcdDaemonHandlerPrivate::adaptersModel(){
    return m_model.data();
}

NfcdAdaptersModel::NfcdAdaptersModel(NfcdAdaptersModelPrivate *data, QObject *parent) : QAbstractListModel(parent), m_data(data){
    m_data->setParent(this);
}

QHash<int, QByteArray> NfcdAdaptersModel::roleNames() const{
    return m_data->roleNames();
}

QVariant NfcdAdaptersModel::data(const QModelIndex &index, int role) const{
    return m_data->data(index, role);
}

int NfcdAdaptersModel::rowCount(const QModelIndex &parent) const{
    return m_data->rowCount(parent);
}


//------------------------------------------------------------------------------------------------------------------

NfcdDaemonHandler::NfcdDaemonHandler(QObject *parent) : QObject(parent), m_data(new NfcdDaemonHandlerPrivate(this))
{
    // empty
}

QString NfcdDaemonHandler::interfaceVersion(){
    return m_data->interfaceVersion();
}

QString NfcdDaemonHandler::daemonVersion(){
    return m_data->daemonVersion();
}


QString NfcdDaemonHandler::adaptersList(){
    return m_data->adaptersList();
}


NfcdAdaptersModel *NfcdDaemonHandler::adaptersModel(){
    return m_data->adaptersModel();
}

QString NfcdDaemonHandler::daemonMode(){
    return m_data->daemonMode();
}

#include "moc_nfcd_daemon_handler.cpp"
