#include "nfcd_tagclassic_handler.h"
#include "nfcd_tagclassic_handler_src.h"

NfcdTagClassicHandlerPrivate::NfcdTagClassicHandlerPrivate(QObject *parent) : QObject(parent){
    //empty
}

QString NfcdTagClassicHandlerPrivate::tagPath() const {
    return m_tagPath;
}

void NfcdTagClassicHandlerPrivate::setTagPath(const QString &tagPath){
    if (m_tagPath == tagPath){
        return;
    }  

    m_tagPath = tagPath;
    m_iface.reset(new NfcdTagClassicDBusIface(tagPath, this));

    emit tagPathChanged(tagPath);
    emit interfaceVersionChanged(interfaceVersion());
    emit serialChanged(serial());
}

QString NfcdTagClassicHandlerPrivate::interfaceVersion(){
    return QStringLiteral("%1").arg(m_iface.isNull() ? 0 : m_iface->GetInterfaceVersion().value());
}

QByteArray NfcdTagClassicHandlerPrivate::serial(){
    QByteArray emptyArray;
    return m_iface.isNull() ? emptyArray : m_iface->GetSerial().value();

}


//---------------------------------------------------------------------------------------------------------

NfcdTagClassicHandler::NfcdTagClassicHandler(QObject *parent) : QObject(parent), 
                                                            m_data(new NfcdTagClassicHandlerPrivate(this)){
    connect(m_data.data(), 
            &NfcdTagClassicHandlerPrivate::tagPathChanged, this,
            &NfcdTagClassicHandler::tagPathChanged);

    connect(m_data.data(), 
            &NfcdTagClassicHandlerPrivate::interfaceVersionChanged, this,
            &NfcdTagClassicHandler::interfaceVersionChanged);

    connect(m_data.data(),
            &NfcdTagClassicHandlerPrivate::serialChanged, this,
            &NfcdTagClassicHandler::serialChanged);

}

QString NfcdTagClassicHandler::tagPath() const {
    return m_data->tagPath();
}

void NfcdTagClassicHandler::setTagPath(const QString &tagPath){
    m_data->setTagPath(tagPath);
}

QString NfcdTagClassicHandler::interfaceVersion(){
    return m_data->interfaceVersion();
}

QByteArray NfcdTagClassicHandler::serial(){
    return m_data->serial();
}

#include "moc_nfcd_tagclassic_handler.cpp"
