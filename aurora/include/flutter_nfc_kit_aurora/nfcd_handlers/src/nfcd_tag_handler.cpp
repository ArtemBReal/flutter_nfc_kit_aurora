#include "nfcd_tag_handler.h"
#include "nfcd_tag_handler_src.h"

NfcdTagHandlerPrivate::NfcdTagHandlerPrivate(QObject *parent) : QObject(parent) {
    //empty
}

QString NfcdTagHandlerPrivate::tagPath() const{
    return m_tagPath;
}

void NfcdTagHandlerPrivate::setTagPath(const QString &tagPath){
    if (m_tagPath == tagPath)
    {
        return;
    }

    m_tagPath = tagPath;
    m_iface.reset(new NfcdTagDBusIface(tagPath, this));

    connect(m_iface.data(), &NfcdTagDBusIface::Removed, this, &NfcdTagHandlerPrivate::removed);

    emit tagPathChanged(tagPath);
    emit interfaceVersionChanged(interfaceVersion());
    emit presentChanged(present());
    emit protocolChanged(protocol());
    emit technologyChanged(technology());
    emit typeChanged(type());
    emit interfacesChanged(interfaces());
    emit ndefRecordsChanged(ndefRecords());
    emit pollParametersChanged(pollParameters());
}

QString NfcdTagHandlerPrivate::interfaceVersion(){
    return QStringLiteral("%1").arg(m_iface.isNull() ? 0 : m_iface->GetInterfaceVersion().value());
}

bool NfcdTagHandlerPrivate::present(){
    return m_iface.isNull() ? false : m_iface->GetPresent().value();
}

QString NfcdTagHandlerPrivate::protocol(){
    uint tagProtocolVal;
    if (m_iface.isNull()){
        tagProtocolVal = NfcdTagProtocol::UnknownProtocol;
    } else {
        tagProtocolVal = m_iface->GetProtocol().value();
    }

    switch (tagProtocolVal){
    case NfcdTagProtocol::UnknownProtocol:
        return QStringLiteral("Unknown Protocol");
    case NfcdTagProtocol::Type1:
        return QStringLiteral("Type 1");
    case NfcdTagProtocol::Type2:
        return QStringLiteral("Type 2");
    case NfcdTagProtocol::Type3:
        return QStringLiteral("Type 3");
    case NfcdTagProtocol::Type4A:
        return QStringLiteral("Type 4A");
    case NfcdTagProtocol::Type4B:
        return QStringLiteral("Type 4B");
    case NfcdTagProtocol::DEP:
        return QStringLiteral("DEP");
    case NfcdTagProtocol::Classic:
        return QStringLiteral("Classic");
    default:
        return QStringLiteral("Unknown");
    }
}

QString NfcdTagHandlerPrivate::technology(){
    uint tagTechnology;
    if (m_iface.isNull()){
        tagTechnology = NfcdTagTechnology::UnknownTechnology;
    } else {
        tagTechnology = m_iface->GetTechnology().value();
    }

    switch (tagTechnology)
    {
    case NfcdTagTechnology::UnknownTechnology:
        return QStringLiteral("Unknown Technology");
    case NfcdTagTechnology::NfcA:
        return QStringLiteral("NFC A");
    case NfcdTagTechnology::NfcB:
        return QStringLiteral("NFC B");
    case NfcdTagTechnology::NfcF:
        return QStringLiteral("NFC F");
    default:
        return QStringLiteral("Unknown");
    }
}

QString NfcdTagHandlerPrivate::type(){
    uint tagType;
    if (m_iface.isNull()){
        tagType = NfcdTagType::UnknownType;
    } else {
        tagType = m_iface->GetType().value();
    }

    switch (tagType){
    case NfcdTagType::UnknownType:
        return QStringLiteral("Unknown Type");
    case NfcdTagType::TypeFelica:
        return QStringLiteral("Felica");
    case NfcdTagType::TypeMifareClassic:
        return QStringLiteral("Mifare Classic");
    case NfcdTagType::TypeMifareUlralight:
        return QStringLiteral("Mifare Ultralight");
    default:
        return QStringLiteral("Unknown");
    }
}

QString NfcdTagHandlerPrivate::interfaces()
{
    QStringList interfaces;
    if (m_iface.isNull()){
        return QStringLiteral("No interfaces");
    } else {
        interfaces = m_iface->GetInterfaces().value();
    }

    return QStringLiteral("%1").arg(interfaces.join("&"));

}

QString NfcdTagHandlerPrivate::ndefRecords(){
    if (m_iface.isNull()){
        return QStringLiteral("No NDEF Records");
    } else {
        QList<QDBusObjectPath> reply = m_iface->GetNdefRecords().value();

        QString ndefRecords;

        for (const auto &record : reply){
            ndefRecords += record.path();
            ndefRecords += QStringLiteral("&");
        }
        return ndefRecords;
    }
}

QVariantMap NfcdTagHandlerPrivate::pollParameters(){
    return m_iface.isNull() ? QVariantMap() : m_iface->GetPollParameters().value();
}

void NfcdTagHandlerPrivate::acquire(bool wait){
    if (!m_iface.isNull()){
        m_iface->Acquire(wait);
    }
}

void NfcdTagHandlerPrivate::deactivate(){
    if (!m_iface.isNull()){
        m_iface->Deactivate();
    }
}

void NfcdTagHandlerPrivate::release(){
    if (!m_iface.isNull()){
        m_iface->Release();
    }
}

QString NfcdTagHandlerPrivate::transceive(const QString &data){
    if (m_iface.isNull()){
        return QString();
    }

    QByteArray bytes = QByteArray::fromHex(QString(data).remove(QRegExp(QStringLiteral("\\s"))).remove(QRegExp(QStringLiteral("0[xX]{1}"))).toLatin1());

    return m_iface->Transceive(bytes).value();
}


//---------------------------------------------------------------------------------------------------------

NfcdTagHandler::NfcdTagHandler(QObject *parent) : QObject(parent), m_data(new NfcdTagHandlerPrivate(this)){
    connect(m_data.data(), &NfcdTagHandlerPrivate::tagPathChanged, this,
            &NfcdTagHandler::tagPathChanged);
    connect(m_data.data(), &NfcdTagHandlerPrivate::interfaceVersionChanged, this,
            &NfcdTagHandler::interfaceVersionChanged);
    connect(m_data.data(), &NfcdTagHandlerPrivate::presentChanged, this,
            &NfcdTagHandler::presentChanged);
    connect(m_data.data(), &NfcdTagHandlerPrivate::protocolChanged, this,
            &NfcdTagHandler::protocolChanged);
    connect(m_data.data(), &NfcdTagHandlerPrivate::technologyChanged, this,
            &NfcdTagHandler::technologyChanged);
    connect(m_data.data(), &NfcdTagHandlerPrivate::typeChanged, this,
            &NfcdTagHandler::typeChanged);
    connect(m_data.data(), &NfcdTagHandlerPrivate::pollParametersChanged, this,
            &NfcdTagHandler::pollParametersChanged);
    connect(m_data.data(), &NfcdTagHandlerPrivate::pollParametersChanged, this,
            &NfcdTagHandler::pollParametersChanged);
    connect(m_data.data(), &NfcdTagHandlerPrivate::removed, this,
            &NfcdTagHandler::removed);
}

QString NfcdTagHandler::tagPath() const{
    return m_data->tagPath();
}

void NfcdTagHandler::setTagPath(const QString &tagPath){
    m_data->setTagPath(tagPath);
}

QString NfcdTagHandler::interfaceVersion(){
    return m_data->interfaceVersion();
}

bool NfcdTagHandler::present(){
    return m_data->present();
}

QString NfcdTagHandler::protocol(){
    return m_data->protocol();
}

QString NfcdTagHandler::technology(){
    return m_data->technology();
}

QString NfcdTagHandler::type(){
    return m_data->type();
}

QString NfcdTagHandler::interfaces(){
    return m_data->interfaces();
}

QString NfcdTagHandler::ndefRecords(){
    return m_data->ndefRecords();
}

QVariantMap NfcdTagHandler::pollParameters(){
    return m_data->pollParameters();
}

void NfcdTagHandler::acquire(bool wait){
    m_data->acquire(wait);
}

void NfcdTagHandler::deactivate(){
    m_data->deactivate();
}

void NfcdTagHandler::release(){
    m_data->release();
}

QString NfcdTagHandler::transceive(const QString &data){
    return m_data->transceive(data);
}

#include "moc_nfcd_tag_handler.cpp"
