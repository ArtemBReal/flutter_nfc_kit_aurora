import 'dart:convert';

import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:ndef/ndef.dart' as ndef;
import 'package:ndef/record.dart';
import 'package:ndef/utilities.dart';

import 'flutter_nfc_kit_aurora_platform_interface.dart';

const channelEvent = "flutter_nfc_kit_aurora_events";

/// An implementation of [FlutterNfcKitAuroraPlatform] that uses method channels.
class MethodChannelFlutterNfcKitAurora extends FlutterNfcKitAuroraPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('flutter_nfc_kit_aurora');

  List<String> splitToList(String? splitingString, String splitSymbol) {
    final splittedList = splitingString!.split(splitSymbol);
    splittedList.removeWhere((element) => element.isEmpty);
    return splittedList;
  }

  Map<int, String> splitToMap(splitingString, String pairSplitSymbol) {
    Map<int, String> splittedMap = {};

    List<String> keyValuePairs = splitingString.split(pairSplitSymbol);
    int i = 0;
    for (String pair in keyValuePairs) {
      List<String> parts = pair.split(':');
      splittedMap[i] = parts[1];
      i++;
    }
    return splittedMap;
  }

  //Канал событий
  final eventChannel = const EventChannel(channelEvent);
  @override
  Stream<String?> checkChanges(){
    return eventChannel.receiveBroadcastStream().map((event) => event as String);
  }

  TypeNameFormat fromStringToTNF(String tnfString) {
    switch (tnfString) {
      case 'empty':
        return TypeNameFormat.empty;
      case 'nfcWellKnown':
        return TypeNameFormat.nfcWellKnown;
      case 'media':
        return TypeNameFormat.media;
      case 'absoluteURI':
        return TypeNameFormat.absoluteURI;
      case 'nfcExternal':
        return TypeNameFormat.nfcExternal;
      case 'unknwon':
        return TypeNameFormat.unknown;
      case 'unchanged':
        return TypeNameFormat.unchanged;
      //case 'reserved': return TypeNameFormat.reserved;
      //'reserved' в современных реализациях не встречается (?)
      default:
        return TypeNameFormat.unknown;
    }
  }


  //-------------------------- DAEMON -----------------------------------
  @override
  Future<String?> getDaemonInterfaceVersion() async {
    final version =
        await methodChannel.invokeMethod<String>('getDaemonInterfaceVersion');
    return version;
  }

  @override
  Future<String?> getDaemonVersion() async {
    final version =
        await methodChannel.invokeMethod<String>('getDaemonVersion');
    return version;
  }

  @override
  Future<String?> getDaemonAdaptersModel() async {
    final adaptersModel =
        await methodChannel.invokeMethod<String>('getDaemonAdaptersModel');
    return adaptersModel;
  }

  @override
  Future<List<String>?> getDaemonAdaptersList() async {
    final adaptersListString =
        await methodChannel.invokeMethod<String>('getDaemonAdaptersList');
    List<String>? adaptersList = splitToList(adaptersListString!, '&');
    return adaptersList;
  }

  @override
  Future<String?> getDaemonMode() async {
    final daemonMode =
        await methodChannel.invokeMethod<String>('getDaemonMode');
    return daemonMode;
  }


  //------------------------- ADAPTER ----------------------------------
  @override
  Future<String?> getAdapterInterfaceVersion() async {
    final adapterInterfaceVersion =
        await methodChannel.invokeMethod<String>('getAdapterInterfaceVersion');
    return adapterInterfaceVersion;
  }

  Future<bool?> getAdapterEnabled() async {
    final adapterEnabled =
        await methodChannel.invokeMethod<bool>('getAdapterEnabled');
    return adapterEnabled;
  }

  @override
  Future<bool?> getAdapterPowered() async {
    final adapterPowered =
        await methodChannel.invokeMethod<bool>('getAdapterPowered');
    return adapterPowered;
  }

  @override
  Future<bool?> getAdapterTargetPresent() async {
    final adapterTargetPresent =
        await methodChannel.invokeMethod<bool>('getAdapterTargetPresent');
    return adapterTargetPresent;
  }

  @override
  Future<List<String>?> getAdapterSupportedModes() async {
    final supportedModes =
        await methodChannel.invokeMethod<String>('getAdapterSupportedModes');
    List<String>? supportedModesList = splitToList(supportedModes!, '&');
    return supportedModesList;
  }

  @override
  Future<String?> getAdapterMode() async {
    final adapterMode =
        await methodChannel.invokeMethod<String>('getAdapterMode');
    return adapterMode;
  }

  @override
  Future<List<String>?> getAdapterTagsList() async {
    final adapterTags =
        await methodChannel.invokeMethod<String>('getAdapterTagsList');
    List<String>? adapterTagsList = splitToList(adapterTags!, '&');
    return adapterTagsList;
  }

  @override
  Future<Map<int, String>?> getAdapterTagsModel() async {
    final adapterTagsModel = await methodChannel
        .invokeMethod<Map<int, String>>('getAdapterTagsModel');
    return adapterTagsModel;
  }


  //------------------------------ TAG ---------------------------------
  @override
  Future<String?> getTagInterfaceVersion() async {
    final tagInterfaceVersion =
        await methodChannel.invokeMethod<String>('getTagInterfaceVersion');
    return tagInterfaceVersion;
  }

  @override
  Future<bool?> getTagPresent() async {
    final tagPresent = await methodChannel.invokeMethod<bool>('getTagPresent');
    return tagPresent;
  }

  @override
  Future<String?> getTagProtocol() async {
    final tagProtocol =
        await methodChannel.invokeMethod<String>('getTagProtocol');
    return tagProtocol;
  }

  @override
  Future<String?> getTagTechnology() async {
    final tagTechnology =
        await methodChannel.invokeMethod<String>('getTagTechnology');
    return tagTechnology;
  }

  @override
  Future<String?> getTagType() async {
    final tagType = await methodChannel.invokeMethod<String>('getTagType');
    return tagType;
  }

  @override
  Future<List<String>?> getTagInterfaces() async {
    final tagInterfacesStr =
        await methodChannel.invokeMethod<String>('getTagInterfaces');
    List<String>? tagInterfaces = splitToList(tagInterfacesStr, '&');
    return tagInterfaces;
  }

  @override
  Future<List<String>?> getTagNdefRecords() async {
    final tagNdefRecordsStr =
        await methodChannel.invokeMethod<String>('getTagNdefRecords');
    List<String>? tagNdefRecords = splitToList(tagNdefRecordsStr, '&');
    return tagNdefRecords;
  }

  @override
  Future tagAcquire() async {
    return await methodChannel.invokeMethod('tagAcquire');
  }

  @override
  Future tagRelease() async {
    return await methodChannel.invokeMethod('tagRelease');
  }

  @override
  Future tagDeactivate() async {
    return await methodChannel.invokeMethod('tagDeactivate');
  }

  //---------------------------------------- ISO DEP --------------------------------------
  @override
  Future<String?> getIsoDepInterfaceVersion() async {
    final isoDepInterfaceVersion =
        await methodChannel.invokeMethod<String>('getIsoDepInterfaceVersion');
    return isoDepInterfaceVersion;
  }

  @override
  Future<List<String>?> getIsoDepTransmit() async {
    final isoDepTransmitResponse =
        await methodChannel.invokeMethod<String>('getIsoDepTransmit');
    List<String>? isoDepTransmitResponseList =
        splitToList(isoDepTransmitResponse, '&');
    return isoDepTransmitResponseList;
  }

  //----------------------------------------- NDEF ----------------------

  @override
  Future<String?> getNdefInterfaceVersion() async {
    final version =
        await methodChannel.invokeMethod<String?>('getNdefInterfaceVersion');
    return version;
  }

  @override
  Future<List<String>?> getNdefFlags() async {
    final flags = await methodChannel.invokeMethod<String?>('getNdefFlags');
    List<String>? flagsList = splitToList(flags, '&');
    return flagsList;
  }

  @override
  Future<TypeNameFormat?> getNdefTypeNameFormat() async {
    final typeNFString =
        await methodChannel.invokeMethod<String?>('getNdefTypeNameFormat');
    TypeNameFormat typeNF = fromStringToTNF(typeNFString!);
    return typeNF;
  }

  @override
  Future<String?> getNdefType() async {
    final type = await methodChannel.invokeMethod<String?>('getNdefType');
    return type;
  }

  @override
  Future<String?> getNdefId() async {
    final idList = await methodChannel.invokeMethod<List<int>?>('getNdefId');
    String id = idList!.map((code) => String.fromCharCode(code)).join('');
    return id;
  }

  @override
  Future<String?> getNdefPayload() async {
    final payloadList =
        await methodChannel.invokeMethod<List<int>?>('getNdefPayload');
    String payload =
        payloadList!.map((code) => String.fromCharCode(code)).join('');
    return payload;
  }


  //Собственная реализация функции 'декапсуляции' данных из NDEF-записи
  @override
  Future<List<ndef.NDEFRecord>?> getNdefRawData() async {

    final rawDataBytes =
        await methodChannel.invokeMethod<List<int>?>('getNdefRawData');

    int tnfAndIdLength = rawDataBytes![0];
    String tnf = ((tnfAndIdLength >> 3) & 0x07).toString();
    int idLength = tnfAndIdLength & 0x07;

    // Извлечение Payload Length
    int payloadLength = (rawDataBytes[1] << 24) +
        (rawDataBytes[2] << 16) +
        (rawDataBytes[3] << 8) +
        rawDataBytes[4];

    // Извлечение ID (если он присутствует)
    String id = '';
    if (idLength > 0) {
      id = String.fromCharCodes(rawDataBytes.sublist(5, 5 + idLength));
    }
    // Извлечение Payload
    String payload = String.fromCharCodes(rawDataBytes.sublist(5 + idLength));

    TypeNameFormat typeNF = fromStringToTNF(tnf!);

    Uint8List typeDecoded = Uint8List.fromList(utf8.encode(''));
    Uint8List idDecoded = Uint8List.fromList(utf8.encode(id));
    Uint8List payloadDecoded = Uint8List.fromList(utf8.encode(payload));

    ndef.NDEFRecord ndefRecord = ndef.NDEFRecord(
        id: idDecoded, type: typeDecoded, tnf: typeNF, payload: payloadDecoded);
    List<ndef.NDEFRecord> recordData = [ndefRecord];
    return recordData;
  }

  //Функция 'инкапсуляции' данных в NDEF-запись
  @override
  Future<List<ndef.NDEFRecord>?> getNdefRecord() async {
    
    final typeNFString = await methodChannel.invokeMethod<String?>('getNdefTypeNameFormat');
    final type = await methodChannel.invokeMethod<String?>('getNdefType');
    final idEncoded = await methodChannel.invokeMethod<List<int>?>('getNdefId');
    final payloadEncoded = await methodChannel.invokeMethod<List<int>?>('getNdefPayload');

    String id = idEncoded!.map((code) => String.fromCharCode(code)).join('');
    String payload = payloadEncoded!.map((code) => String.fromCharCode(code)).join('');
    TypeNameFormat typeNF = fromStringToTNF(typeNFString!);

    Uint8List typeDecoded = Uint8List.fromList(utf8.encode(type!));
    Uint8List idDecoded = Uint8List.fromList(utf8.encode(id));
    Uint8List payloadDecoded = Uint8List.fromList(utf8.encode(payload));

    ndef.NDEFRecord rawRecord = ndef.NDEFRecord(tnf: typeNF, type: typeDecoded,id: idDecoded, payload: payloadDecoded);
    List<ndef.NDEFRecord> rawList = [rawRecord];
    return rawList;
    
  }

  @override
  Future<List<String>?> getNdefInterfaces() async {
    final interfaces =
        await methodChannel.invokeMethod<String?>('getNdefInterfaces');
    List<String>? interfacesList = splitToList(interfaces, '&');
    return interfacesList;
  }


  //-------------------------------------- TAG CLASSIC -------------------------------
  @override
  Future<String?> getTagClassicInterfaceVersion() async {
    final interfaceVersion = await methodChannel
        .invokeMethod<String?>('getTagClassicInterfaceVersion');
    return interfaceVersion;
  }

  @override
  Future<String?> getTagClassicSerial() async {
    final serial =
        await methodChannel.invokeMethod<String?>('getTagClassicSerial');
    return serial;
  }


 //-------------------------------- TAG TYPE 2 --------------------------------
 @override
  Future<String?> getTagType2InterfaceVersion() async {
    final interfaceVersion = await methodChannel.invokeMethod<String?>('getTagType2InterfaceVersion');
    return interfaceVersion;
  }

  @override
  Future<String?> getTagType2BlockSize() async {
    final blockSize = await methodChannel.invokeMethod<String?>('getTagType2BlockSize');
    return blockSize;
  }

  @override
  Future<String?> getTagType2DataSize() async {
  final dataSize = await methodChannel.invokeMethod<String?>('getTagType2DataSize');
  return dataSize;
  }

  @override
  Future<String?> getTagType2AllData() async {
  final allDataEncoded = await methodChannel.invokeMethod<List<int>?>('getTagType2AllData');
  String allData = allDataEncoded!.map((code) => String.fromCharCode(code)).join('');
  return allData;
  }

  @override
  Future<String?> getTagType2Serial() async {
  final serial = await methodChannel.invokeMethod<String?>('getTagType2Serial');
  return serial;
  }
}