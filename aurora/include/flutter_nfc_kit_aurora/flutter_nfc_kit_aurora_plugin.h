#ifndef FLUTTER_PLUGIN_FLUTTER_NFC_KIT_AURORA_PLUGIN_H
#define FLUTTER_PLUGIN_FLUTTER_NFC_KIT_AURORA_PLUGIN_H

#include <QObject>

#include <flutter/plugin-interface.h>
#include <flutter_nfc_kit_aurora/globals.h>
#include <flutter_nfc_kit_aurora/qt_headers.h>
#include <flutter_nfc_kit_aurora/help_functions.h>

#include <flutter_nfc_kit_aurora/nfcd_handlers/handlers_headers/nfcd_daemon_handler.h>
#include <flutter_nfc_kit_aurora/nfcd_handlers/handlers_headers/nfcd_adapter_handler.h>
#include <flutter_nfc_kit_aurora/nfcd_handlers/handlers_headers/nfcd_isodep_handler.h>
#include <flutter_nfc_kit_aurora/nfcd_handlers/handlers_headers/nfcd_ndef_handler.h>
#include <flutter_nfc_kit_aurora/nfcd_handlers/handlers_headers/nfcd_tagtype2_handler.h>
#include <flutter_nfc_kit_aurora/nfcd_handlers/handlers_headers/nfcd_tagclassic_handler.h>
#include <flutter_nfc_kit_aurora/nfcd_handlers/handlers_headers/nfcd_tag_handler.h>
#include <flutter_nfc_kit_aurora/nfcd_handlers/handlers_headers/nfcd_typifier.h>

class PLUGIN_EXPORT FlutterNfcKitAuroraPlugin final : public QObject, public PluginInterface
{
    Q_OBJECT

public:
    explicit FlutterNfcKitAuroraPlugin(QObject *parent = nullptr);
    void RegisterWithRegistrar(PluginRegistrar &registrar) override;

public slots:
    void checkTargetPresent();
    void checkAdapterEnabled();
    void checkAdapterPowered();

private:
    void onMethodCall(const MethodCall &call);
    void unimplemented(const MethodCall &call);
    size_t hash(const std::string& str);
    void onListen();
    void onCancel();

    bool getTargetPresent();

    bool m_sendEvents;
    bool m_update;

    static NfcdDaemonHandler& daemonHandlerInstance();
    static NfcdAdapterHandler& adapterHandlerInstance();
    static NfcdTagHandler& tagHandlerInstance();
    static NfcdIsoDepHandler& isoDepHandlerInstance();
    static NfcdNdefHandler& ndefHandlerInstance();
    static NfcdTagClassicHandler& tagClassicHandlerInstance();
    static NfcdTagType2Handler& tagType2HandlerInstance();

    static HelpFunctions& helpFuncInstance();

    void onGetDaemonInterfaceVersion(const MethodCall &call);
    void onGetDaemonVersion (const MethodCall &call);
    void onGetDaemonAdaptersModel(const MethodCall &call);
    void onGetDaemonAdaptersList(const MethodCall &call);
    void onGetDaemonMode(const MethodCall &call);

    void onGetAdapterInterfaceVersion(const MethodCall &call);
    void onGetAdapterEnabled(const MethodCall &call);
    void onGetAdapterPowered(const MethodCall &call);
    void onGetAdapterTargetPresent(const MethodCall &call);
    void onGetAdapterSupportedModes(const MethodCall &call);
    void onGetAdapterMode(const MethodCall &call);
    void onGetAdapterTagsList(const MethodCall &call);
    void onGetAdapterTagsModel(const MethodCall &call);

    void onGetTagInterfaceVersion(const MethodCall &call);
    void onGetTagPresent(const MethodCall &call);
    void onGetTagProtocol(const MethodCall &call);
    void onGetTagTechnology(const MethodCall &call);
    void onGetTagType(const MethodCall &call);
    void onGetTagInterfaces(const MethodCall &call);
    void onGetTagNdefRecords(const MethodCall &call);
    void onGetTagPollParameters(const MethodCall &call);
    void onTagAcquire(const MethodCall &call);
    void onTagDeactivate(const MethodCall &call);
    void onTagRelease(const MethodCall &call);
    void onTagTransceive(const MethodCall &call);

    void onGetIsoDepActivationParameters(const MethodCall &call);
    QMap<QString, QVariant> onGetIsoDepActivationParametersMock();
    void onGetIsoDepInterfaceVersion(const MethodCall &call);
    void onGetIsoDepReset(const MethodCall &call);
    void onGetIsoDepTransmit(const MethodCall &call);

    void onGetNdefInterfaceVersion(const MethodCall &call);
    void onGetNdefFlags(const MethodCall &call);
    void onGetNdefTypeNameFormat(const MethodCall &call);
    void onGetNdefType(const MethodCall &call);
    void onGetNdefId(const MethodCall &call);
    void onGetNdefPayload(const MethodCall &call);
    void onGetNdefRawData(const MethodCall &call);
    void onGetNdefInterfaces(const MethodCall &call);

    void onGetTagClassicInterfaceVersion(const MethodCall &call);
    void onGetTagClassicSerial(const MethodCall &call);

    void onGetTagType2InterfaceVersion(const MethodCall &call);
    void onGetTagType2BlockSize(const MethodCall &call);
    void onGetTagType2DataSise(const MethodCall &call);
    void onGetTagType2Write(const MethodCall &call);
    void onGetTagType2WriteData(const MethodCall &call);
    void onGetTagType2Read(const MethodCall &call);
    void onGetTagType2ReadData(const MethodCall &call);
    void onGetTagType2AllData(const MethodCall &call);
    void onGetTagType2Serial(const MethodCall &call);

    //NfcdAdapterHandler& m_manager;
    QMetaObject::Connection m_tagPresentChangedConnection;
    QMetaObject::Connection m_adapterEnabledChangedConnection;
    QMetaObject::Connection m_adapterPoweredChangedConnection;

};

#endif /* FLUTTER_PLUGIN_FLUTTER_NFC_KIT_AURORA_PLUGIN_H */
