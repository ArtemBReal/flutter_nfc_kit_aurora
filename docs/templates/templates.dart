import 'dart:typed_data';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';
import 'package:ndef/ndef.dart' as ndef;
import 'flutter_nfc_kit_aurora_method_channel.dart';


/*********************************************************  
    Шаблонные представления основных классов и методов
    высокоуровневой части плагина
**********************************************************/


//-------------------- Platform Interface --------------------------
abstract class FlutterNfcKitAuroraPlatform extends PlatformInterface {
  FlutterNfcKitAuroraPlatform() : super(token: _token);

  static final Object _token = Object();

  static FlutterNfcKitAuroraPlatform _instance = MethodChannelFlutterNfcKitAurora();
  static FlutterNfcKitAuroraPlatform get instance => _instance;

  static set instance(FlutterNfcKitAuroraPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Stream<String?> checkChanges(){
    throw UnimplementedError('checkChanges() has not been implemented.');
  }

  Future<String?> getFooVersion() {
    throw UnimplementedError('getFooVersion() has not been implemented.');
  }
}



//------------------- Method Channel -------------------------------

const channelEvent = "flutter_nfc_kit_aurora_events";

class MethodChannelFlutterNfcKitAurora extends FlutterNfcKitAuroraPlatform {
  @visibleForTesting
  final methodChannel = const MethodChannel('flutter_nfc_kit_aurora');

  final eventChannel = const EventChannel(channelEvent);
  @override
  Stream<String?> checkChanges(){
    return eventChannel.receiveBroadcastStream().map((event) => event as String);
  }


  @override
  Future<String?> getFooVersion() async {
    final version =
        await methodChannel.invokeMethod<String>('getFooVersion');
    return version;
  }
}


//--------------------- API -----------------------------------------
import 'flutter_nfc_kit_aurora_platform_interface.dart';

class FlutterNfcKitAurora {

  Stream<String?> checkChanges(){
    return FlutterNfcKitAuroraPlatform.instance.checkChanges();
  }

  Future<String?> getFooVersion(){
    return FlutterNfcKitAuroraPlatform.instance.getFooVersion();
  }
}