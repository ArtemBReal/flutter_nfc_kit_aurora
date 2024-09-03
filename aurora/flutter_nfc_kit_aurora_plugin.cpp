#include <flutter_nfc_kit_aurora/flutter_nfc_kit_aurora_plugin.h>
#include <flutter/method-channel.h>
#include <sys/utsname.h>

#include <vector>
#include <qvector.h>

#include <QDebug>
#include <string>
#include <functional>


namespace Event
{
    //канал событий
    constexpr auto Channel = "flutter_nfc_kit_aurora_events";
}

FlutterNfcKitAuroraPlugin::FlutterNfcKitAuroraPlugin(QObject *parent) : QObject(parent)
{
    m_sendEvents = false;   //отправляем ли сигнал о событии
    m_update = false;       //необходимо ли обновление данных
}

void FlutterNfcKitAuroraPlugin::RegisterWithRegistrar(PluginRegistrar &registrar)
{

    registrar.RegisterMethodChannel("flutter_nfc_kit_aurora",
                                    MethodCodecType::Standard,
                                    [this](const MethodCall &call)
                                    { this->onMethodCall(call); });
    registrar.RegisterEventChannel(
        Event::Channel,
        MethodCodecType::Standard,
        [this](const Encodable &)
        {
            this->onListen();
            return EventResponse();
        },
        [this](const Encodable &)
        {
            this->onCancel();
            return EventResponse();
        });
}

void FlutterNfcKitAuroraPlugin::onMethodCall(const MethodCall &call)
{
    const auto &method = call.GetMethod();

    if (method.find("Daemon") != std::string::npos)
    {
        if (method == "getDaemonInterfaceVersion")
        {
            onGetDaemonInterfaceVersion(call);
        }
        else if (method == "getDaemonVersion")
        {
            onGetDaemonVersion(call);
        }
        else if (method == "getDaemonAdaptersModel")
        {
            onGetDaemonAdaptersModel(call);
        }
        else if (method == "getDaemonAdaptersList")
        {
            onGetDaemonAdaptersList(call);
        }
        else if (method == "getDaemonMode")
        {
            onGetDaemonMode(call);
        }
    }
    else if (method.find("Adapter") != std::string::npos)
    {
        if (method == "getAdapterInterfaceVersion")
        {
            onGetAdapterInterfaceVersion(call);
        }
        else if (method == "getAdapterEnabled")
        {
            onGetAdapterEnabled(call);
        }
        else if (method == "getAdapterPowered")
        {
            onGetAdapterPowered(call);
        }
        else if (method == "getAdapterTargetPresent")
        {
            onGetAdapterTargetPresent(call);
        }
        else if (method == "getAdapterSupportedModes")
        {
            onGetAdapterSupportedModes(call);
        }
        else if (method == "getAdapterMode")
        {
            onGetAdapterMode(call);
        }
        else if (method == "getAdapterTagsModel")
        {
            onGetAdapterTagsModel(call);
        }
        else if (method == "getAdapterTagsList")
            onGetAdapterTagsList(call);
    }
    else if (method.find("Tag") != std::string::npos)
    {
        if (method.find("Classic") != std::string::npos)
        {
            if (method == "getTagClassicInterfaceVersion")
            {
                onGetTagClassicInterfaceVersion(call);
            }
            else if (method == "getTagClassicSerial")
            {
                onGetTagClassicSerial(call);
            }
        }
        else if (method.find("Type2") != std::string::npos)
        {
            if (method == "getTagType2InterfaceVersion")
            {
                onGetTagType2InterfaceVersion(call);
            }
            else if (method == "getTagType2BlockSize")
            {
                onGetTagType2BlockSize(call);
            }
            else if (method == "getTagType2DataSize")
            {
                onGetTagType2DataSise(call);
            }
            else if (method == "getTagType2AllData")
            {
                onGetTagType2AllData(call);
            }
            else if (method == "getTagType2Serial")
            {
                onGetTagType2Serial(call);
            }
        }
        else
        {
            if (method == "getTagInterfaceVersion")
            {
                onGetTagInterfaceVersion(call);
            }
            else if (method == "getTagPresent")
            {
                onGetTagPresent(call);
            }
            else if (method == "getTagProtocol")
            {
                onGetTagProtocol(call);
            }
            else if (method == "getTagTechnology")
            {
                onGetTagTechnology(call);
            }
            else if (method == "getTagType")
            {
                onGetTagType(call);
            }
            else if (method == "tagAcquire")
            {
                onTagAcquire(call);
            }
            else if (method == "tagRelease")
            {
                onTagRelease(call);
            }
            else if (method == "tagDeactivate")
            {
                onTagDeactivate(call);
            }
            else if (method == "getTagInterfaces")
            {
                onGetTagInterfaces(call);
            }
            else if (method == "getTagNdefRecords")
            {
                onGetTagNdefRecords(call);
            }
        }
    }
    else if (method.find("Iso") != std::string::npos)
    {
        if (method == "getIsoDepInterfaceVersion")
        {
            onGetIsoDepInterfaceVersion(call);
        }
        else if (method == "getIsoDepTransmit")
        {
            onGetIsoDepTransmit(call);
        }
        else if (method == "getIsoDepReset")
        {
            onGetIsoDepReset(call);
        }
    }
    else if (method.find("Ndef") != std::string::npos)
    {
        if (method == "getNdefInterfaceVersion")
        {
            onGetNdefInterfaceVersion(call);
        }
        else if (method == "getNdefFlags")
        {
            onGetNdefFlags(call);
        }
        else if (method == "getNdefTypeNameFormat")
        {
            onGetNdefTypeNameFormat(call);
        }
        else if (method == "getNdefType")
        {
            onGetNdefType(call);
        }
        else if (method == "getNdefId")
        {
            onGetNdefId(call);
        }
        else if (method == "getNdefPayload")
        {
            onGetNdefPayload(call);
        }
        else if (method == "getNdefRawData")
        {
            onGetNdefRawData(call);
        }
        else if (method == "getNdefInterfaces")
        {
            onGetNdefInterfaces(call);
        }
    }

    else
    {
        unimplemented(call);
    }
}

size_t FlutterNfcKitAuroraPluginhash(const std::string& str)
{
    std::hash<std::string> hasher;
    return hasher(str);
}

void FlutterNfcKitAuroraPlugin::unimplemented(const MethodCall &call)
{
    call.SendSuccessResponse(nullptr);
}

void FlutterNfcKitAuroraPlugin::onListen()
{
    m_tagPresentChangedConnection =
        QObject::connect(&FlutterNfcKitAuroraPlugin::adapterHandlerInstance(),
                         &NfcdAdapterHandler::targetPresentChanged,
                         this,
                         &FlutterNfcKitAuroraPlugin::checkTargetPresent);

    m_adapterEnabledChangedConnection =
        QObject::connect(&FlutterNfcKitAuroraPlugin::adapterHandlerInstance(),
                         &NfcdAdapterHandler::enabledChanged,
                         this,
                         &FlutterNfcKitAuroraPlugin::checkAdapterEnabled);

    m_adapterPoweredChangedConnection =
        QObject::connect(&FlutterNfcKitAuroraPlugin::adapterHandlerInstance(),
                         &NfcdAdapterHandler::poweredChanged,
                         this,
                         &FlutterNfcKitAuroraPlugin::checkAdapterPowered);

    m_sendEvents = true;
    qDebug() << m_sendEvents;

    checkTargetPresent();
}

void FlutterNfcKitAuroraPlugin::onCancel()
{
    m_sendEvents = false;
    QObject::disconnect(m_tagPresentChangedConnection);
    QObject::disconnect(m_adapterEnabledChangedConnection);
    QObject::disconnect(m_adapterPoweredChangedConnection);
}

void FlutterNfcKitAuroraPlugin::checkTargetPresent()
{
    qDebug() << "Have Event";
    if (m_sendEvents)
    {
        qDebug() << "Sending event";
        auto whichEvent = QStringLiteral("targetPresented");
        EventChannel(Event::Channel, MethodCodecType::Standard).SendEvent(whichEvent.toStdString());
    }
}

void FlutterNfcKitAuroraPlugin::checkAdapterEnabled()
{
    if (m_sendEvents)
    {
        auto whichEvent = QStringLiteral("adapterEnabled");
        EventChannel(Event::Channel, MethodCodecType::Standard).SendEvent(whichEvent.toStdString());
    }
}

void FlutterNfcKitAuroraPlugin::checkAdapterPowered()
{
    if (m_sendEvents)
    {
        auto whichEvent = QStringLiteral("adapterPowered");
        EventChannel(Event::Channel, MethodCodecType::Standard).SendEvent(whichEvent.toStdString());
    }
}


// Статические экземпляры классов каждого из обработчиков

NfcdDaemonHandler &FlutterNfcKitAuroraPlugin::daemonHandlerInstance()
{
    static NfcdDaemonHandler daemonHandler;
    return daemonHandler;
}

NfcdAdapterHandler &FlutterNfcKitAuroraPlugin::adapterHandlerInstance()
{

    static NfcdAdapterHandler adapterHanlder;
    return adapterHanlder;
}

NfcdTagHandler &FlutterNfcKitAuroraPlugin::tagHandlerInstance()
{
    static NfcdTagHandler tagHandler;
    return tagHandler;
}

NfcdIsoDepHandler &FlutterNfcKitAuroraPlugin::isoDepHandlerInstance()
{
    static NfcdIsoDepHandler isoDepHandler;
    return isoDepHandler;
}

NfcdNdefHandler &FlutterNfcKitAuroraPlugin::ndefHandlerInstance()
{
    static NfcdNdefHandler ndefHandler;
    return ndefHandler;
}

NfcdTagClassicHandler &FlutterNfcKitAuroraPlugin::tagClassicHandlerInstance()
{
    static NfcdTagClassicHandler tagClassicHandler;
    return tagClassicHandler;
}

NfcdTagType2Handler &FlutterNfcKitAuroraPlugin::tagType2HandlerInstance()
{
    static NfcdTagType2Handler tagType2Handler;
    return tagType2Handler;
}

HelpFunctions &FlutterNfcKitAuroraPlugin::helpFuncInstance()
{
    static HelpFunctions helpFuncInstance;
    return helpFuncInstance;
}


//-------------------- Daemon Handler Method Channel --------------------

void FlutterNfcKitAuroraPlugin::onGetDaemonInterfaceVersion(const MethodCall &call)
{
    QString daemonInterfaceVersion;
    daemonInterfaceVersion = FlutterNfcKitAuroraPlugin::daemonHandlerInstance().interfaceVersion();

    call.SendSuccessResponse(daemonInterfaceVersion.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetDaemonVersion(const MethodCall &call)
{
    QString daemonVersion;
    daemonVersion = FlutterNfcKitAuroraPlugin::daemonHandlerInstance().daemonVersion();

    call.SendSuccessResponse(daemonVersion.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetDaemonAdaptersModel(const MethodCall &call)
{
    // Рудиментарный метод на основе официального API NFCD,
    // для разработчиков прикладных приложений бесполезен,
    // можно удалить
    call.SendSuccessResponse(1);
}

void FlutterNfcKitAuroraPlugin::onGetDaemonAdaptersList(const MethodCall &call)
{
    QString adaptersList = FlutterNfcKitAuroraPlugin::daemonHandlerInstance().adaptersList();

    QStringList adapterListSplitted = adaptersList.split("&");
    QVector<QString> adapterListVector;
    foreach (QString part, adapterListSplitted)
    {
        adapterListVector.append(part);
    }

     //предполагается, что в мобильном устройстве ВСЕГДА только один NFC-адаптер
    QString adapterPath = adapterListVector.at(0);

    FlutterNfcKitAuroraPlugin::adapterHandlerInstance().setAdapterPath(adapterPath);

    call.SendSuccessResponse(adaptersList.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetDaemonMode(const MethodCall &call)
{
    QString daemonMode;
    daemonMode = FlutterNfcKitAuroraPlugin::daemonHandlerInstance().daemonMode();

    call.SendSuccessResponse(daemonMode.toStdString());
}

//-------------------- Adapter Handler Method Channel --------------------

void FlutterNfcKitAuroraPlugin::onGetAdapterInterfaceVersion(const MethodCall &call)
{
    QString adapterInterfaceVersion;
    adapterInterfaceVersion = FlutterNfcKitAuroraPlugin::adapterHandlerInstance().interfaceVersion();

    call.SendSuccessResponse(adapterInterfaceVersion.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetAdapterEnabled(const MethodCall &call)
{
    bool adapterEnabled;
    adapterEnabled = FlutterNfcKitAuroraPlugin::adapterHandlerInstance().enabled();

    call.SendSuccessResponse(adapterEnabled);
}

void FlutterNfcKitAuroraPlugin::onGetAdapterPowered(const MethodCall &call)
{
    bool adapterPowered;
    adapterPowered = FlutterNfcKitAuroraPlugin::adapterHandlerInstance().powered();

    call.SendSuccessResponse(adapterPowered);
}

void FlutterNfcKitAuroraPlugin::onGetAdapterTargetPresent(const MethodCall &call)
{
    bool adapterTargetPresent;
    adapterTargetPresent = FlutterNfcKitAuroraPlugin::adapterHandlerInstance().targetPresent();

    call.SendSuccessResponse(adapterTargetPresent);
}

void FlutterNfcKitAuroraPlugin::onGetAdapterSupportedModes(const MethodCall &call)
{
    QString supportedModes;
    supportedModes = FlutterNfcKitAuroraPlugin::adapterHandlerInstance().supportedModes();
    call.SendSuccessResponse(supportedModes.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetAdapterMode(const MethodCall &call)
{
    QString adapterMode = FlutterNfcKitAuroraPlugin::adapterHandlerInstance().mode();

    call.SendSuccessResponse(adapterMode.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetAdapterTagsList(const MethodCall &call)
{
    QString tagsList = FlutterNfcKitAuroraPlugin::adapterHandlerInstance().tagsList();

    QStringList tagsListSplitted = tagsList.split("&");
    QVector<QString> tagsListVector;
    foreach (QString part, tagsListSplitted)
    {
        tagsListVector.append(part);
    }
    
    // Предполагается, что в данный момент времени 
    // возможно взаимодействие только с одним NFC-тегом
    QString tagPath = tagsListVector.at(0);

    // Путь до NFC-тега должен быть известен всем обработчикам,
    // так как он может использовать несколько технологий
    FlutterNfcKitAuroraPlugin::tagHandlerInstance().setTagPath(tagPath);
    FlutterNfcKitAuroraPlugin::isoDepHandlerInstance().setTagPath(tagPath);
    FlutterNfcKitAuroraPlugin::tagClassicHandlerInstance().setTagPath(tagPath);
    FlutterNfcKitAuroraPlugin::tagType2HandlerInstance().setTagPath(tagPath);

    call.SendSuccessResponse(tagsList.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetAdapterTagsModel(const MethodCall &call)
{
    // Рудиментарный метод на основе официального API NFCD,
    // для разработчиков прикладных приложений бесполезен,
    // можно удалить
    call.SendSuccessResponse(Encodable(1));
}

//----------------------------- TAG ------------------------------------

void FlutterNfcKitAuroraPlugin::onGetTagInterfaceVersion(const MethodCall &call)
{
    QString tagInterfaceVersion = FlutterNfcKitAuroraPlugin::tagHandlerInstance().interfaceVersion();
    call.SendSuccessResponse(tagInterfaceVersion.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetTagPresent(const MethodCall &call)
{
    bool tagPresent = FlutterNfcKitAuroraPlugin::tagHandlerInstance().present();
    call.SendSuccessResponse(tagPresent);
}

void FlutterNfcKitAuroraPlugin::onGetTagProtocol(const MethodCall &call)
{
    QString tagProtocol = FlutterNfcKitAuroraPlugin::tagHandlerInstance().protocol();
    call.SendSuccessResponse(tagProtocol.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetTagTechnology(const MethodCall &call)
{
    QString tagTechnology = FlutterNfcKitAuroraPlugin::tagHandlerInstance().technology();
    call.SendSuccessResponse(tagTechnology.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetTagType(const MethodCall &call)
{
    QString tagType = FlutterNfcKitAuroraPlugin::tagHandlerInstance().type();
    call.SendSuccessResponse(tagType.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetTagInterfaces(const MethodCall &call)
{
    QString tagInterfaces = FlutterNfcKitAuroraPlugin::tagHandlerInstance().interfaces();
    call.SendSuccessResponse(tagInterfaces.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetTagNdefRecords(const MethodCall &call)
{
    QString ndefRecords = FlutterNfcKitAuroraPlugin::tagHandlerInstance().ndefRecords();

    QStringList ndefRecordsList = ndefRecords.split("&");
    QVector<QString> ndefRecordsVector;
    foreach (QString part, ndefRecordsList)
    {
        ndefRecordsList.append(part);
    }

    // Предполагается, что не может быть больше одной NDEF-записи
    QString recordPath = ndefRecordsList.at(0);

    FlutterNfcKitAuroraPlugin::ndefHandlerInstance().setRecordPath(recordPath);
    call.SendSuccessResponse(ndefRecords.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetTagPollParameters(const MethodCall &call)
{
    // НЕ РАБОТАЕТ РЕАЛИЗАЦИЯ В ПЛАТФОРМОЗАВИСИМОЙ ЧАСТИ,
    // СМ. ДОКУМЕНТАЦИЮ НА API
    call.SendSuccessResponse(1);
}

void FlutterNfcKitAuroraPlugin::onTagAcquire(const MethodCall &call)
{
    bool wait = false;
    FlutterNfcKitAuroraPlugin::tagHandlerInstance().acquire(wait);
    call.SendSuccessResponse(1);
}

void FlutterNfcKitAuroraPlugin::onTagDeactivate(const MethodCall &call)
{
    FlutterNfcKitAuroraPlugin::tagHandlerInstance().deactivate();
    call.SendSuccessResponse(1);
}

void FlutterNfcKitAuroraPlugin::onTagRelease(const MethodCall &call)
{
    FlutterNfcKitAuroraPlugin::tagHandlerInstance().release();
    call.SendSuccessResponse(1);
}

void FlutterNfcKitAuroraPlugin::onTagTransceive(const MethodCall &call)
{
    // БЕЗ РЕАЛИЗАЦИИ onGetTagPollParameters ПЕРЕДАЧА НЕ РАБОТАЕТ,
    
    // QByteArray dataTransceive = FlutterNfcKitAuroraPlugin::tagHandlerInstance().transceive();

    call.SendSuccessResponse(1);
}

//-------------------------------------- ISO DEP ------------------------------------------

void FlutterNfcKitAuroraPlugin::onGetIsoDepActivationParameters(const MethodCall &call)
{
    // Из платформозависимой части параметры должны возвращаться
    // в виде вектора vector<pait<string, variant>> 
    // Qt запрещает использовать такой каст, поэтому реализация метода
    // в соответствии с API затруднительна
    
    call.SendSuccessResponse(1);
}

QMap<QString, QVariant> FlutterNfcKitAuroraPlugin::onGetIsoDepActivationParametersMock()
{
    uchar cla = 0x00;
    uchar ins = 0xA4;
    uchar p1 = 0x04;
    uchar p2 = 0x00;
    QString data = "0x325041592E5359532E444446393100";
    uint le = 0x0E;

    QMap<QString, QVariant> parameteresMap;

    // Сохраняем значения разных типов
    parameteresMap["cla"] = static_cast<uchar>(cla);
    parameteresMap["ins"] = static_cast<uchar>(ins); 
    parameteresMap["p1"] = static_cast<uchar>(p1);
    parameteresMap["p2"] = static_cast<uchar>(p2); 
    parameteresMap["data"] = QString(data); 
    parameteresMap["le"] = static_cast<uint>(le);

    return parameteresMap;
}

void FlutterNfcKitAuroraPlugin::onGetIsoDepInterfaceVersion(const MethodCall &call)
{
    QString isoDepInterfaceVersion = FlutterNfcKitAuroraPlugin::isoDepHandlerInstance().interfaceVersion();
    call.SendSuccessResponse(isoDepInterfaceVersion.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetIsoDepReset(const MethodCall &call)
{
    FlutterNfcKitAuroraPlugin::isoDepHandlerInstance().reset();
    call.SendSuccessResponse(1);
}

void FlutterNfcKitAuroraPlugin::onGetIsoDepTransmit(const MethodCall &call)
{

    // Т.к. реализация метода onGetIsoDepActivationParameters отсутствует,
    // ниже приведён пример работы с заранее определёнными параметрами
    // СПОЙЛЕР: предположительно, работает не так, как нужно

    QMap<QString, QVariant> parameteresMap = FlutterNfcKitAuroraPlugin::onGetIsoDepActivationParametersMock();

    uchar cla = parameteresMap["cla"].toUInt();
    uchar ins = parameteresMap["ins"].toUInt();
    uchar p1 = parameteresMap["p1"].toUInt();
    uchar p2 = parameteresMap["p2"].toUInt();
    QString data = parameteresMap["data"].toString();
    uint le = parameteresMap["le"].toUInt();

    QString transmitResponse = FlutterNfcKitAuroraPlugin::isoDepHandlerInstance().transmit(cla, ins, p1, p2, data, le);

    call.SendSuccessResponse(transmitResponse.toStdString());
}

//------------------------------------------ NDEF ------------------------------------------

void FlutterNfcKitAuroraPlugin::onGetNdefInterfaceVersion(const MethodCall &call)
{
    QString ndefInterfaceVersion = FlutterNfcKitAuroraPlugin::ndefHandlerInstance().interfaceVersion();
    call.SendSuccessResponse(ndefInterfaceVersion.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetNdefFlags(const MethodCall &call)
{
    QString ndefFlags = FlutterNfcKitAuroraPlugin::ndefHandlerInstance().flags();
    call.SendSuccessResponse(ndefFlags.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetNdefTypeNameFormat(const MethodCall &call)
{
    QString ndefTypeNF = FlutterNfcKitAuroraPlugin::ndefHandlerInstance().typeNameFormat();
    call.SendSuccessResponse(ndefTypeNF.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetNdefType(const MethodCall &call)
{
    QByteArray ndefType = FlutterNfcKitAuroraPlugin::ndefHandlerInstance().type();
    QString ndefTypeStr = FlutterNfcKitAuroraPlugin::helpFuncInstance().fromRDtoStr(ndefType);
    qDebug() << "Ndef ndefTypeStr: " << ndefType << ":" << ndefTypeStr;
    call.SendSuccessResponse(ndefTypeStr.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetNdefId(const MethodCall &call)
{
    QByteArray id = FlutterNfcKitAuroraPlugin::ndefHandlerInstance().id();
    std::vector<uint8_t> idVector(id.begin(), id.end());
    QString ndefIdStr = FlutterNfcKitAuroraPlugin::helpFuncInstance().fromRDtoStr(id);
    qDebug() << "Ndef Id: " << id << ":" << ndefIdStr;
    call.SendSuccessResponse(idVector);
}

void FlutterNfcKitAuroraPlugin::onGetNdefPayload(const MethodCall &call)
{
    QByteArray ndefPayload = FlutterNfcKitAuroraPlugin::ndefHandlerInstance().payload();
    QString ndefPayloadStr = FlutterNfcKitAuroraPlugin::helpFuncInstance().fromRDtoStr(ndefPayload);

    std::vector<uint8_t> ndefPayloadVector(ndefPayload.begin(), ndefPayload.end());
    QString dataString;
    for (uint8_t byte : ndefPayloadVector)
    {
        dataString.append(QString("%1 ").arg(byte, 2, 16, QLatin1Char('0')));
    }

    // Отладочная печать
    qDebug() << "Ndef Payload: " << ndefPayload << ":" << ndefPayloadStr << ":" << dataString;

    call.SendSuccessResponse(ndefPayloadVector);
}

void FlutterNfcKitAuroraPlugin::onGetNdefRawData(const MethodCall &call)
{
    QByteArray ndefRawData = FlutterNfcKitAuroraPlugin::ndefHandlerInstance().rawData();
    
    //Отладочная печать
    qDebug() << "RawData Array: " << ndefRawData;

    std::vector<uint8_t> ndefRawDataVector(ndefRawData.begin(), ndefRawData.end());
    QString dataString;
    for (uint8_t byte : ndefRawDataVector)
    {
        dataString.append(QString("%1 ").arg(byte, 2, 16, QLatin1Char('0')));
    }

    // Отладочная печать
    qDebug() << "RawData vector: " << dataString;

    call.SendSuccessResponse(Encodable::Uint8List(ndefRawDataVector));
}

void FlutterNfcKitAuroraPlugin::onGetNdefInterfaces(const MethodCall &call)
{
    QString ndefInterfaces = FlutterNfcKitAuroraPlugin::ndefHandlerInstance().interfaces();
    call.SendSuccessResponse(ndefInterfaces.toStdString());
}

//--------------------------------------- TAG CLASSIC -------------------------------------
void FlutterNfcKitAuroraPlugin::onGetTagClassicInterfaceVersion(const MethodCall &call)
{
    QString tagClassicInterfaceVersion = FlutterNfcKitAuroraPlugin::tagClassicHandlerInstance().interfaceVersion();
    call.SendSuccessResponse(tagClassicInterfaceVersion.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetTagClassicSerial(const MethodCall &call)
{
    QByteArray tagClassicSerial = FlutterNfcKitAuroraPlugin::tagClassicHandlerInstance().serial();
    
    // Отладочная печать полезной нагрузки - серийного номера
    qDebug() << "Serial: " << tagClassicSerial;

    QString tagClassicSerialStr = FlutterNfcKitAuroraPlugin::helpFuncInstance().fromQBAtoQStr(tagClassicSerial);
    call.SendSuccessResponse(tagClassicSerialStr.toStdString());
}

//---------------------------------------- TAG TYPE 2 -------------------------------------

void FlutterNfcKitAuroraPlugin::onGetTagType2InterfaceVersion(const MethodCall &call)
{
    QString interfaceVersion = FlutterNfcKitAuroraPlugin::tagType2HandlerInstance().interfaceVersion();
    call.SendSuccessResponse(interfaceVersion.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetTagType2BlockSize(const MethodCall &call)
{
    // Наследие API, размера блока данных

    quint32 tempBlockSize = FlutterNfcKitAuroraPlugin::tagType2HandlerInstance().blockSize();
    QString blockSize = QString("%1").arg(tempBlockSize);
    call.SendSuccessResponse(blockSize.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetTagType2DataSise(const MethodCall &call)
{
    // Наследие API, размер хранимых данных

    quint32 tempDataSize = FlutterNfcKitAuroraPlugin::tagType2HandlerInstance().dataSize();
    QString dataSize = QString("%1").arg(tempDataSize);
    call.SendSuccessResponse(dataSize.toStdString());
}

void FlutterNfcKitAuroraPlugin::onGetTagType2AllData(const MethodCall &call)
{
    QByteArray allData = FlutterNfcKitAuroraPlugin::tagType2HandlerInstance().readAllData();
    std::vector<uint8_t> allDataVector(allData.begin(), allData.end());

    call.SendSuccessResponse(allDataVector);
}

void FlutterNfcKitAuroraPlugin::onGetTagType2Serial(const MethodCall &call)
{
    QByteArray serial = FlutterNfcKitAuroraPlugin::tagType2HandlerInstance().serial();
    QString tagType2SerialStr = FlutterNfcKitAuroraPlugin::helpFuncInstance().fromQBAtoQStr(serial);

    call.SendSuccessResponse(tagType2SerialStr.toStdString());
}

#include "moc_flutter_nfc_kit_aurora_plugin.cpp"
#include "flutter_nfc_kit_aurora_plugin.h"
