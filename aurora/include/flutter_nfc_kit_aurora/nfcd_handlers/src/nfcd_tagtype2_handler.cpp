#include "nfcd_tagtype2_handler.h"
#include "nfcd_tagtype2_handler_src.h"

NfcdTagType2HandlerPrivate::NfcdTagType2HandlerPrivate(QObject *parent) : QObject(parent){
    //empty
}

QString NfcdTagType2HandlerPrivate::tagPath() const {
    return m_tagPath;
}

void NfcdTagType2HandlerPrivate::setTagPath(const QString &tagPath){
    if (m_tagPath == tagPath){
        return;
    }  

    m_tagPath = tagPath;
    m_iface.reset(new NfcdTagType2DBusIface(tagPath, this));

    emit tagPathChanged(tagPath);
    emit interfaceVersionChanged(interfaceVersion());
    emit blockSizeChanged(blockSize());
    emit dataSizeChanged(dataSize());
    emit serialChanged(serial());
}

QString NfcdTagType2HandlerPrivate::interfaceVersion(){
    return QStringLiteral("%1").arg(m_iface.isNull() ? 0 : m_iface->GetInterfaceVersion().value());
}

quint32 NfcdTagType2HandlerPrivate::blockSize(){
    return m_iface.isNull() ? 0 : m_iface->GetBlockSize().value();
}

quint32 NfcdTagType2HandlerPrivate::dataSize(){
    return m_iface.isNull() ? 0 : m_iface->GetDataSize().value();
}

quint32 NfcdTagType2HandlerPrivate::write(quint32 sector, quint32 block, const QString &data){
    if (m_iface.isNull()){
        return 0;
    }
        
    QByteArray bytes = QByteArray::fromHex(QString(data).remove(QRegExp(QStringLiteral("\\s")))
                                                        .remove(QRegExp(QStringLiteral("0[xX]{1}")))
                                                        .toLatin1());

    return m_iface->Write(sector, block, bytes).value();
}

quint32 NfcdTagType2HandlerPrivate::writeData(quint32 offset, const QString &data){
    if (m_iface.isNull()){
        return 0;
    }
        
    QByteArray bytes = QByteArray::fromHex(QString(data).remove(QRegExp(QStringLiteral("\\s")))
                                                        .remove(QRegExp(QStringLiteral("0[xX]{1}")))
                                                        .toLatin1());

    return m_iface->WriteData(offset, bytes).value();
}

QString NfcdTagType2HandlerPrivate::read(quint32 sector, quint32 block){
    return m_iface.isNull() ? QString() : m_iface->Read(sector, block).value();
}

QString NfcdTagType2HandlerPrivate::readData(quint32 offset, quint32 maxbytes){
    return m_iface.isNull() ? QString() : m_iface->ReadData(offset, maxbytes).value();
}

QByteArray NfcdTagType2HandlerPrivate::readAllData(){
    return m_iface.isNull() ? QByteArray() : m_iface->ReadAllData().value();
}

QByteArray NfcdTagType2HandlerPrivate::serial(){
    return m_iface.isNull() ? QByteArray() : m_iface->GetSerial().value();
}


//-------------------------------------------------------------------------------------------------------

NfcdTagType2Handler::NfcdTagType2Handler(QObject *parent) : QObject(parent), 
                                                            m_data(new NfcdTagType2HandlerPrivate(this)){
    connect(m_data.data(), 
            &NfcdTagType2HandlerPrivate::tagPathChanged, this,
            &NfcdTagType2Handler::tagPathChanged);

    connect(m_data.data(), 
            &NfcdTagType2HandlerPrivate::interfaceVersionChanged, this,
            &NfcdTagType2Handler::interfaceVersionChanged);

    connect(m_data.data(),
            &NfcdTagType2HandlerPrivate::blockSizeChanged, this,
            &NfcdTagType2Handler::blockSizeChanged);

    connect(m_data.data(), 
            &NfcdTagType2HandlerPrivate::dataSizeChanged, this,
            &NfcdTagType2Handler::dataSizeChanged);

    connect(m_data.data(), 
            &NfcdTagType2HandlerPrivate::serialChanged, this,
            &NfcdTagType2Handler::serialChanged);
}

QString NfcdTagType2Handler::tagPath() const {
    return m_data->tagPath();
}

void NfcdTagType2Handler::setTagPath(const QString &tagPath){
    m_data->setTagPath(tagPath);
}

QString NfcdTagType2Handler::interfaceVersion(){
    return m_data->interfaceVersion();
}

quint32 NfcdTagType2Handler::blockSize(){
    return m_data->blockSize();
}

quint32 NfcdTagType2Handler::dataSize(){
    return m_data->dataSize();
}

quint32 NfcdTagType2Handler::write(quint32 sector, quint32 block, const QString &data){
    return m_data->write(sector, block, data);
}

quint32 NfcdTagType2Handler::writeData(quint32 offset, const QString &data){
    return m_data->writeData(offset, data);
}

QString NfcdTagType2Handler::read(quint32 sector, quint32 block){
    return m_data->read(sector, block);
}

QString NfcdTagType2Handler::readData(quint32 offset, quint32 maxbytes){
    return m_data->readData(offset, maxbytes);
}

QByteArray NfcdTagType2Handler::readAllData(){
    return m_data->readAllData();
}

QByteArray NfcdTagType2Handler::serial(){
    return m_data->serial();
}

#include "moc_nfcd_tagtype2_handler.cpp"
