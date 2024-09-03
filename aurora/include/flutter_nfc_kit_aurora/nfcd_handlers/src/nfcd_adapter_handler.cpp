#include "nfcd_adapter_handler.h"
#include "nfcd_adapter_handler_src.h"
#include "nfcd_tag_handler_src.h"

NfcdTagsModelPrivate::NfcdTagsModelPrivate(NfcdAdapterDBusIface *iface) : QObject(nullptr), m_adapter(iface){
    m_roleNames[NfcdTagsModelPrivate::PathRole] = QByteArrayLiteral("path");
    m_roleNames[NfcdTagsModelPrivate::ProtocolRole] = QByteArrayLiteral("protocol");
    m_roleNames[NfcdTagsModelPrivate::TechnologyRole] = QByteArrayLiteral("technology");
    m_roleNames[NfcdTagsModelPrivate::TypeRole] = QByteArrayLiteral("type");

    updateTags(iface->GetTags().value());

    connect(iface, &NfcdAdapterDBusIface::TagsChanged, this, &NfcdTagsModelPrivate::updateTags);
}

void NfcdTagsModelPrivate::updateTags(const QList<QDBusObjectPath> &tags){
    QStringList tagsPaths;

    for (const auto &tag : tags){
        tagsPaths.append(tag.path());
    }

    if (m_parent){
        m_parent->beginResetModel();
    }

    for (const auto &tagPath : tagsPaths){
        if (m_tags.contains(tagPath)){
            continue;
        }

        QSharedPointer<NfcdTagDBusIface> tagPtr(new NfcdTagDBusIface(tagPath));
        m_tags.insert(tagPath, tagPtr);
    }

    QMapIterator<QString, QSharedPointer<NfcdTagDBusIface>> it(m_tags);
    while (it.hasNext()){
        it.next();
        if (tagsPaths.contains(it.key())){
            continue;
        }

        m_tags.take(it.key()).reset();
    }

    if (m_parent){
        m_parent->endResetModel();
    }
}

void NfcdTagsModelPrivate::setParent(NfcdTagsModel *parent){
    QObject::setParent(parent);
    m_parent = parent;
}

QHash<int, QByteArray> NfcdTagsModelPrivate::roleNames() const {
    return m_roleNames;
}

QVariant NfcdTagsModelPrivate::data(const QModelIndex &index, int role) const {
    if (index.row() >= m_tags.count()){
        return QVariant();
    }

    auto key = m_tags.keys().at(index.row());
    auto value = m_tags.value(key);
    if (role == NfcdTagsModelPrivate::PathRole){
        return key;
    } else if (role == NfcdTagsModelPrivate::ProtocolRole){
        return static_cast<NfcdTagProtocol>(value->GetProtocol().value());
    } else if (role == NfcdTagsModelPrivate::TechnologyRole){
        return static_cast<NfcdTagTechnology>(value->GetTechnology().value());
    } else if (role == NfcdTagsModelPrivate::TypeRole){
        return value->GetType().value();
    }

    return QVariant();
}

int NfcdTagsModelPrivate::rowCount(const QModelIndex &parent) const {
    if(parent.isValid()){
        return 0;
    }

    return m_tags.count();
}


//----------------------------------------------------------------------------------------

NfcdAdapterHandlerPrivate::NfcdAdapterHandlerPrivate(QObject *parent) : QObject(parent){ 
    
    //empty
}

QString NfcdAdapterHandlerPrivate::adapterPath() const {
    return m_adapterPath;
}

void NfcdAdapterHandlerPrivate::setAdapterPath(const QString &adapterPath){
    if(m_adapterPath == adapterPath){
        return;
    }

    m_adapterPath = adapterPath;
    m_iface.reset(new NfcdAdapterDBusIface(adapterPath, this));
    m_model.reset(new NfcdTagsModel(new NfcdTagsModelPrivate(m_iface.data()), this));

    connect(m_iface.data(), &NfcdAdapterDBusIface::EnabledChanged, this,
            &NfcdAdapterHandlerPrivate::enabledChanged);
    connect(m_iface.data(), &NfcdAdapterDBusIface::PoweredChanged, this,
            &NfcdAdapterHandlerPrivate::poweredChanged);
    connect(m_iface.data(), &NfcdAdapterDBusIface::TargetPresentChanged, this,
            &NfcdAdapterHandlerPrivate::targetPresentChanged);
    connect(m_iface.data(), &NfcdAdapterDBusIface::ModeChanged, this,
            [this](uint mode) {
                emit modeChanged(static_cast<QString>(mode));
            });
    
    emit adapterPathChanged(adapterPath);
    emit interfaceVersionChanged(interfaceVesrion());
    emit enabledChanged(enabled());
    emit poweredChanged(powered());
    emit targetPresentChanged(targetPresent());
    emit supportedModesChanged(supportedModes());
    emit modeChanged(mode());
    emit tagsModelChanged(tagsModel());
}

QString NfcdAdapterHandlerPrivate::interfaceVesrion(){
    return QStringLiteral("%1").arg(m_iface.isNull() ? 0 : m_iface->GetInterfaceVersion().value());
}

bool NfcdAdapterHandlerPrivate::enabled(){
    return m_iface.isNull() ? false : m_iface->GetEnabled().value();
}

bool NfcdAdapterHandlerPrivate::powered(){
    return m_iface.isNull() ? false : m_iface->GetPowered().value();
}

bool NfcdAdapterHandlerPrivate::targetPresent(){
    return m_iface.isNull() ? false : m_iface->GetTargetPresent().value();
}

QString NfcdAdapterHandlerPrivate::supportedModes(){
    quint32 supportedModesVal = m_iface.isNull() ? static_cast<quint32>(NfcdMode::ReaderWriter)
                                                : m_iface->GetSupportedModes().value();

    
    QString supportedModesRes;
    if((supportedModesVal & NfcdMode::P2PInitiator) == NfcdMode::P2PInitiator){
        supportedModesRes += QStringLiteral("P2PInitiator&");
    }
    if((supportedModesVal & NfcdMode::ReaderWriter) == NfcdMode::ReaderWriter){
        supportedModesRes += QStringLiteral("ReaderWriter&");
    }
    if((supportedModesVal & NfcdMode::P2PTarget) == NfcdMode::P2PTarget){
        supportedModesRes += QStringLiteral("P2PTarget&");
    }
    if((supportedModesVal & NfcdMode::CardEmulation) == NfcdMode::CardEmulation){
        supportedModesRes += QStringLiteral("CardEmulation");
    }

    return supportedModesRes;
    
}

QString NfcdAdapterHandlerPrivate::mode(){
    quint32 modeVal = m_iface.isNull() ? static_cast<quint32>(NfcdMode::ReaderWriter)
                                                : m_iface->GetMode().value();

    
    QString adapterMode;
    if((modeVal & NfcdMode::P2PInitiator) == NfcdMode::P2PInitiator){
        adapterMode = QStringLiteral("P2PInitiator");
    }
    if((modeVal & NfcdMode::ReaderWriter) == NfcdMode::ReaderWriter){
        adapterMode = QStringLiteral("ReaderWriter");
    }
    if((modeVal & NfcdMode::P2PTarget) == NfcdMode::P2PTarget){
        adapterMode = QStringLiteral("P2PTarget");
    }
    if((modeVal & NfcdMode::CardEmulation) == NfcdMode::CardEmulation){
        adapterMode = QStringLiteral("CardEmulation");
    }

    return adapterMode;
}

QString NfcdAdapterHandlerPrivate::tagsList()
{
    QList<QDBusObjectPath> reply = m_iface->GetTags().value();
    QString tagsList;

    for (const auto &tag : reply)
    {
        tagsList += tag.path();
        tagsList += QStringLiteral("&");
    }
    return tagsList;
}


//-----------------------------------------------------

NfcdTagsModel *NfcdAdapterHandlerPrivate::tagsModel(){
    return m_model.data();
}

NfcdTagsModel::NfcdTagsModel(NfcdTagsModelPrivate *data, QObject *parent) : QAbstractListModel(parent), m_data(data){
    m_data->setParent(this);
}

QHash<int, QByteArray> NfcdTagsModel::roleNames() const {
    return m_data->roleNames();
}

QVariant NfcdTagsModel::data(const QModelIndex &index, int role) const {
    return m_data->data(index, role);
}

int NfcdTagsModel::rowCount(const QModelIndex &parent) const{
    return m_data->rowCount(parent);
}

NfcdTagsModel *NfcdAdapterHandler::tagsModel(){
    return m_data->tagsModel();
}


//---------------------------------------------------------------------------------------------------------------------

NfcdAdapterHandler::NfcdAdapterHandler(QObject *parent) : QObject(parent), m_data(new NfcdAdapterHandlerPrivate(this)){
    connect(m_data.data(), &NfcdAdapterHandlerPrivate::adapterPathChanged, this,
            &NfcdAdapterHandler::adapterPathChanged);
            connect(m_data.data(), &NfcdAdapterHandlerPrivate::interfaceVersionChanged, this,
            &NfcdAdapterHandler::interfaceVersionChanged);
            connect(m_data.data(), &NfcdAdapterHandlerPrivate::enabledChanged, this,
            &NfcdAdapterHandler::enabledChanged);
            connect(m_data.data(), &NfcdAdapterHandlerPrivate::poweredChanged, this,
            &NfcdAdapterHandler::poweredChanged);
            connect(m_data.data(), &NfcdAdapterHandlerPrivate::targetPresentChanged, this,
            &NfcdAdapterHandler::targetPresentChanged);
            connect(m_data.data(), &NfcdAdapterHandlerPrivate::supportedModesChanged, this,
            &NfcdAdapterHandler::supportedModesChanged);
            connect(m_data.data(), &NfcdAdapterHandlerPrivate::modeChanged, this,
            &NfcdAdapterHandler::modeChanged);
            connect(m_data.data(), &NfcdAdapterHandlerPrivate::tagsModelChanged, this,
            &NfcdAdapterHandler::tagsModelChanged);
}

QString NfcdAdapterHandler::adapterPath() const {
    return m_data->adapterPath();
}

void NfcdAdapterHandler::setAdapterPath(const QString &adapterPath){
    m_data->setAdapterPath(adapterPath);
}

QString NfcdAdapterHandler::interfaceVersion(){
    return m_data->interfaceVesrion();
}

bool NfcdAdapterHandler::enabled(){
    return m_data->enabled();
}

bool NfcdAdapterHandler::powered(){
    return m_data->powered();
}

bool NfcdAdapterHandler::targetPresent(){
    return m_data->targetPresent();
}

QString NfcdAdapterHandler::supportedModes(){
    return m_data->supportedModes();
}

QString NfcdAdapterHandler::mode(){
    return m_data->mode();
}

QString NfcdAdapterHandler::tagsList()
{
    return m_data->tagsList();
}

#include "moc_nfcd_adapter_handler.cpp"
