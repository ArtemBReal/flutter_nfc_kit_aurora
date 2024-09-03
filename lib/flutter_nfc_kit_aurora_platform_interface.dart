import 'dart:typed_data';

import 'package:plugin_platform_interface/plugin_platform_interface.dart';
import 'package:ndef/ndef.dart' as ndef;

import 'flutter_nfc_kit_aurora_method_channel.dart';

abstract class FlutterNfcKitAuroraPlatform extends PlatformInterface {
  /// Constructs a FlutterNfcKitAuroraPlatform.
  FlutterNfcKitAuroraPlatform() : super(token: _token);

  static final Object _token = Object();

  static FlutterNfcKitAuroraPlatform _instance = MethodChannelFlutterNfcKitAurora();

  /// The default instance of [FlutterNfcKitAuroraPlatform] to use.
  ///
  /// Defaults to [MethodChannelFlutterNfcKitAurora].
  
  static FlutterNfcKitAuroraPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [FlutterNfcKitAuroraPlatform] when
  /// they register themselves.
  static set instance(FlutterNfcKitAuroraPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Stream<String?> checkChanges(){
    throw UnimplementedError('checkChanges() has not been implemented.');
  }

  Future<String?> getDaemonInterfaceVersion() {
    throw UnimplementedError('getDaemonInterfaceVersion() has not been implemented.');
  }

  Future<String?> getDaemonVersion() {
    throw UnimplementedError('getDaemonVersion() has not been implemented.');
  }  

  Future<String?> getDaemonAdaptersModel(){
    throw UnimplementedError('getDaemonAdaptersModel() has not been implemented.');
  }

  Future<List<String>?> getDaemonAdaptersList() {
    throw UnimplementedError('getDaemonAdaptersList() has not been implemented.');
  }

  Future<String?> getDaemonMode() {
    throw UnimplementedError('getDaemonMode() has not been implemented.');
  }

  //-------------------------------ADAPTER--------------------------

  Future<String?> getAdapterInterfaceVersion() {
    throw UnimplementedError('getAdapterInterfaceVersion() has not been implemented.');

  }

  Future<bool?> getAdapterEnabled() {
    throw UnimplementedError('getAdapterEnabled() has not been implemented.');
  }

  Future<bool?> getAdapterPowered() {
    throw UnimplementedError('getAdapterPowered() has not been implemented.');
  }

  Future<bool?> getAdapterTargetPresent() {
    throw UnimplementedError('adapterEnabled() has not been implemented.');
  }


  Future<List<String>?> getAdapterSupportedModes() {
    throw UnimplementedError('getAdapterSupportedModes() has not been implemented.'); 
  }


  Future<String?> getAdapterMode(){
    throw UnimplementedError('getAdapterMode() has not been implemented.');  
  }

  Future<List<String>?> getAdapterTagsList(){
    throw UnimplementedError('getAdapterTagsList() has not been implemented.'); 
  }

  Future<Map<int, String>?> getAdapterTagsModel(){
    throw UnimplementedError('getAdapterTagsModel() has not been implemented.');  
  }

  //-------------------------------- TAG -------------------------------

  Future<String?> getTagInterfaceVersion(){
        throw UnimplementedError('getTagInterfaceVersion() has not been implemented.');  
  }

  Future<bool?> getTagPresent(){
    throw UnimplementedError('getTagPresent() has not been implemented.');  
  }

  Future<String?> getTagProtocol(){
    throw UnimplementedError('getTagProtocol() has not been implemented.');  
  }

  Future<String?> getTagTechnology(){
    throw UnimplementedError('getTagTechnology() has not been implemented.');  
  }

  Future<String?> getTagType(){
    throw UnimplementedError('getTagType() has not been implemented.');  
  }

  Future<List<String>?> getTagInterfaces(){
    throw UnimplementedError('getTagInterfaces() has not been implemented.');  
  }

  Future<List<String>?> getTagNdefRecords(){
    throw UnimplementedError('getTagNdefRecords() has not been implemented.');  
  }

  Future tagAcquire(){
    throw UnimplementedError('tagAcquire() has not been implemented.'); 
  }
  
  Future tagRelease(){
    throw UnimplementedError('tagRelease() has not been implemented.'); 
  }

  Future tagDeactivate(){
    throw UnimplementedError('tagDeactivate() has not been implemented.'); 
  }

  //------------------------------- ISO DEP ----------------------------------
  Future<String?> getIsoDepInterfaceVersion(){
    throw UnimplementedError('getIsoDepInterfaceVersion() has not been implemented.'); 
  }

  Future<List<String>?> getIsoDepTransmit(){
    throw UnimplementedError('getIsodDepTransmit() has not been implemented.'); 
  }

  Future<String?> getIsoDepReset(){
    throw UnimplementedError('getIsoDepReset() has not been implemented.'); 
  }


  //-------------------------------- NDEF -------------------------------

  Future<String?> getNdefInterfaceVersion(){
    throw UnimplementedError('getNdefInterfaceVersion() has not been implemented.');
  }

  Future <List<String>?> getNdefFlags() {
    throw UnimplementedError('getNdefFlags() has not been implemented.');
  }

  Future<ndef.TypeNameFormat?> getNdefTypeNameFormat(){
    throw UnimplementedError('getNdefTypeNameFormat() has not been implemented.');
  }

  Future<String?> getNdefType(){
    throw UnimplementedError('getNdefType() has not been implemented.');
  }

  Future<String?> getNdefId(){
    throw UnimplementedError('getNdefId() has not been implemented.');
  }

  Future<String?> getNdefPayload(){
    throw UnimplementedError('getNdefPayload() has not been implemented.');
  }

  Future<List<ndef.NDEFRecord>?> getNdefRawData(){
    throw UnimplementedError('getNdefRawData() has not been implemented.');
  }

  Future<List<ndef.NDEFRecord>?>  getNdefRecord(){
    throw UnimplementedError('getNdefRecord() has not been implemented.');
  }

  Future<List<String>?> getNdefInterfaces(){
    throw UnimplementedError('getNdefInterfaces() has not been implemented.');
  }

  //----------------------------------- TAG CLASSIC ----------------------------
  Future<String?> getTagClassicInterfaceVersion(){
    throw UnimplementedError('getTagClassicInterfaceVersion() has not been implemented.');
  }

  Future<String?> getTagClassicSerial(){
    throw UnimplementedError('getTagClassicSerial() has not been implemented.');
  }


  //-------------------------------------- TAG TYPE 2 ----------------------------
  Future<String?> getTagType2InterfaceVersion(){
    throw UnimplementedError('getTagType2InterfaceVersion() has not been implemented.');
  }

  Future<String?> getTagType2BlockSize(){
    throw UnimplementedError('getTagType2BlockSize() has not been implemented.');
  }

  Future<String?> getTagType2DataSize(){
    throw UnimplementedError('getTagType2DataSize() has not been implemented.');
  }

  Future<String?> getTagType2AllData(){
    throw UnimplementedError('getTagType2AllData() has not been implemented.');
  }

  Future<String?> getTagType2Serial(){
    throw UnimplementedError('getTagType2Serial() has not been implemented.');
  }
  
}
