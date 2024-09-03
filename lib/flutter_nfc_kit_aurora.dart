
import 'dart:typed_data';

import 'flutter_nfc_kit_aurora_platform_interface.dart';
import 'package:ndef/ndef.dart' as ndef;

class FlutterNfcKitAurora {

  //Поток для отслеживания событий в платформозависимой части
  Stream<String?> checkChanges(){
    return FlutterNfcKitAuroraPlatform.instance.checkChanges();
  }

  Future<String?> getDaemonInterfaceVersion(){
    return FlutterNfcKitAuroraPlatform.instance.getDaemonInterfaceVersion();
  }

  Future<String?> getDaemonVersion(){
    return FlutterNfcKitAuroraPlatform.instance.getDaemonVersion();
  }

  Future<String?> getDaemonAdaptersModel(){
    return FlutterNfcKitAuroraPlatform.instance.getDaemonAdaptersModel();
  }

  Future<List<String>?>  getDaemonAdaptersList(){
    return FlutterNfcKitAuroraPlatform.instance.getDaemonAdaptersList();
  }

  Future<String?> getDaemonMode(){
    return FlutterNfcKitAuroraPlatform.instance.getDaemonMode();
  }

  //------------------------------------ADAPTER-------------------------
  Future<String?> getAdapterInterfaceVersion(){
    return FlutterNfcKitAuroraPlatform.instance.getAdapterInterfaceVersion();
  }

  Future<bool?> getAdapterEnabled(){
    return FlutterNfcKitAuroraPlatform.instance.getAdapterEnabled();
  }

  Future<bool?> getAdapterPowered(){
    return FlutterNfcKitAuroraPlatform.instance.getAdapterPowered();
  }
  
  Future<bool?> getAdapterTargetPresent(){
    return FlutterNfcKitAuroraPlatform.instance.getAdapterTargetPresent();
  }

  Future<List<String>?> getAdapterSupportedModes(){
    return FlutterNfcKitAuroraPlatform.instance.getAdapterSupportedModes();
  }


  Future<String?> getAdapterMode(){
    return FlutterNfcKitAuroraPlatform.instance.getAdapterMode();
  }

  Future<List<String>?> getAdapterTagsList(){
    return FlutterNfcKitAuroraPlatform.instance.getAdapterTagsList();
  }

  Future<Map<int, String>?> getAdapterTagsModel(){
    return FlutterNfcKitAuroraPlatform.instance.getAdapterTagsModel();
  }

  
  //----------------------------------- TAG ----------------------------
  Future<String?> getTagInterfaceVersion(){
    return FlutterNfcKitAuroraPlatform.instance.getTagInterfaceVersion();
  }

  Future<bool?> getTagPresent(){
    return FlutterNfcKitAuroraPlatform.instance.getTagPresent();
  }

  Future<String?> getTagProtocol(){
    return FlutterNfcKitAuroraPlatform.instance.getTagProtocol();
  }

  Future<String?> getTagTechnology(){
    return FlutterNfcKitAuroraPlatform.instance.getTagTechnology();
  }

  Future<String?> getTagType(){
    return FlutterNfcKitAuroraPlatform.instance.getTagType();
  }

  Future<List<String>?> getTagInterfaces(){
    return FlutterNfcKitAuroraPlatform.instance.getTagInterfaces();
  }

  Future<List<String>?> getTagNdefRecords(){
    return FlutterNfcKitAuroraPlatform.instance.getTagNdefRecords();
  }

  Future tagAcquire(){
    return FlutterNfcKitAuroraPlatform.instance.tagAcquire();
  }

  Future tagRelease(){
    return FlutterNfcKitAuroraPlatform.instance.tagRelease();
  }

  Future tagDeactivate(){
    return FlutterNfcKitAuroraPlatform.instance.tagDeactivate();
  }

  //----------------------------------- ISO DEP --------------------------
  Future<String?> getIsoDepInterfaceVersion(){
    return FlutterNfcKitAuroraPlatform.instance.getIsoDepInterfaceVersion();
  }

  Future<List<String>?> getIsoDepTransmit(){
    return FlutterNfcKitAuroraPlatform.instance.getIsoDepTransmit();
  }

  /*------------------------------------------  
    Другие методы интерфейса не реализованы
    по причине отсутствия реализации
    в платформозависимой части плагина
  -------------------------------------------*/ 



  //------------------------------------NDEF--------------------------

  Future<String?> getNdefInterfaceVersion(){
    return FlutterNfcKitAuroraPlatform.instance.getNdefInterfaceVersion();
  }

  Future<List<String>?> getNdefFlags(){
    return FlutterNfcKitAuroraPlatform.instance.getNdefFlags();
  }

  Future<ndef.TypeNameFormat?> getNdefTypeNameFormat(){
    return FlutterNfcKitAuroraPlatform.instance.getNdefTypeNameFormat();
  }

  Future<String?> getNdefType(){
    return FlutterNfcKitAuroraPlatform.instance.getNdefType();
  }

  Future<String?> getNdefId(){
    return FlutterNfcKitAuroraPlatform.instance.getNdefId();
  }

  Future<String?> getNdefPayload(){
    return FlutterNfcKitAuroraPlatform.instance.getNdefPayload();
  }

  Future<List<ndef.NDEFRecord>?> getNdefRawData(){
    return FlutterNfcKitAuroraPlatform.instance.getNdefRawData();
  }

  Future<List<ndef.NDEFRecord>?>  getNdefRecord() async {
    return FlutterNfcKitAuroraPlatform.instance.getNdefRecord();
  }

  Future<List<String>?> getNdefInterfaces(){
    return FlutterNfcKitAuroraPlatform.instance.getNdefInterfaces();
  }


  //------------------------------------------ TAG CLASSIC ---------------------------------
  Future<String?> getTagClassicInterfaceVersion(){
    return FlutterNfcKitAuroraPlatform.instance.getTagClassicInterfaceVersion();
  }

  Future<String?> getTagClassicSerial(){
    return FlutterNfcKitAuroraPlatform.instance.getTagClassicSerial();
  }

  
  //---------------------------------------- TAG TYPE 2 -----------------------------
    Future<String?> getTagType2InterfaceVersion(){
    return FlutterNfcKitAuroraPlatform.instance.getTagType2InterfaceVersion();
  }

  Future<String?> getTagType2BlockSize(){
    return FlutterNfcKitAuroraPlatform.instance.getTagType2BlockSize();
  }

  Future<String?> getTagType2DataSize(){
    return FlutterNfcKitAuroraPlatform.instance.getTagType2DataSize();
  }

  Future<String?> getTagType2AllData(){
    return FlutterNfcKitAuroraPlatform.instance.getTagType2AllData();
  }

  Future<String?> getTagType2Serial(){
    return FlutterNfcKitAuroraPlatform.instance.getTagType2Serial();
  }

  
}
