// SPDX-FileCopyrightText: 2023 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#include "nfcd_isodep_handler.h"
#include "nfcd_isodep_handler_src.h"

NfcdIsoDepHandlerPrivate::NfcdIsoDepHandlerPrivate(QObject *parent) : QObject(parent) { }

QString NfcdIsoDepHandlerPrivate::tagPath() const {
    return m_tagPath;
}

void NfcdIsoDepHandlerPrivate::setTagPath(const QString &tagPath){
    if (m_tagPath == tagPath)
        return;

    m_tagPath = tagPath;
    m_iface.reset(new NfcdIsoDepDBusIface(tagPath, this));

    emit tagPathChanged(tagPath);
    emit interfaceVersionChanged(interfaceVersion());
}

QString NfcdIsoDepHandlerPrivate::interfaceVersion(){
    return QStringLiteral("%1").arg(m_iface.isNull() ? 0 : m_iface->GetInterfaceVersion().value());
}

QString NfcdIsoDepHandlerPrivate::activationParamaters()
{
    // QT НЕ РАЗРЕШАЕТ ИСПОЛЬЗОВАТЬ ПРИВЕДЁННЫЙ НИЖЕ ТИП
    //QVector<QPair<QString, QVariant>> reply = m_iface->GetActivationParameters().value();   
}

QString NfcdIsoDepHandlerPrivate::transmit(uchar cla, uchar ins, 
                                                    uchar p1, uchar p2,
                                                    QString &data, uint le){

    if (m_iface.isNull()){
        return {};
    }

    QByteArray bytes = QByteArray::fromHex(QString(data).remove(QRegExp(QStringLiteral("\\s")))
                                                        .remove(QRegExp(QStringLiteral("0[xX]{1}")))
                                                        .toLatin1());

    QDBusPendingReply<QByteArray, uchar, uchar> result =
            m_iface->Transmit(cla, ins, p1, p2, bytes, le);

    QString response = QString::fromUtf8(result.argumentAt(0).value<QByteArray>());

    // Отладочная печать для проверки ответа
    qDebug() << "ISO DEP Response " << result << response;

    QString sw1 = QString::number(result.argumentAt(1).value<uchar>());
    QString sw2 = QString::number(result.argumentAt(2).value<uchar>());

    // Формирование посылки
    QString transmit = QStringLiteral("response:") + QStringLiteral("%1").arg(response) 
        + QStringLiteral("&sw1:") + QStringLiteral("%1").arg(sw1) + QStringLiteral("&sw2:") + QStringLiteral("%1").arg(sw2);

    return transmit;
}

void NfcdIsoDepHandlerPrivate::reset(){
    if (!m_iface.isNull()){
        m_iface->Reset();
    }
}


//------------------------------------------------------------------------------------------------------------------

NfcdIsoDepHandler::NfcdIsoDepHandler(QObject *parent) : QObject(parent), m_data(new NfcdIsoDepHandlerPrivate(this)){
    connect(m_data.data(), 
            &NfcdIsoDepHandlerPrivate::tagPathChanged, this,
            &NfcdIsoDepHandler::tagPathChanged);

    connect(m_data.data(), 
            &NfcdIsoDepHandlerPrivate::interfaceVersionChanged, this,
            &NfcdIsoDepHandler::interfaceVersionChanged);
}

QString NfcdIsoDepHandler::tagPath() const {
    return m_data->tagPath();
}

void NfcdIsoDepHandler::setTagPath(const QString &tagPath){
    m_data->setTagPath(tagPath);
}

QString NfcdIsoDepHandler::interfaceVersion(){
    return m_data->interfaceVersion();
}

QString NfcdIsoDepHandler::activationParameters(){
    return m_data->activationParamaters();
}

QString NfcdIsoDepHandler::transmit(uchar cla, uchar ins,
                                             uchar p1, uchar p2,
                                            QString &data, uint le){

    return m_data->transmit(cla, ins, p1, p2, data, le);
}

void NfcdIsoDepHandler::reset(){
    m_data->reset();
}

#include "moc_nfcd_isodep_handler.cpp"