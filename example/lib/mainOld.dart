import 'dart:convert';
import 'dart:ffi';
import 'dart:typed_data';
import 'package:ndef/ndef.dart' as ndef;

import 'package:flutter/material.dart';
import 'dart:async';

import 'package:flutter/services.dart';
import 'package:flutter_nfc_kit_aurora/flutter_nfc_kit_aurora.dart';
import 'package:ndef/record.dart';
import 'package:ndef/utilities.dart';

void main() {
  runApp(const MyApp());
}


class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class NfcGlobalVariables{
  int _counter = 10;
  int counter2 = 1;
}

class _MyAppState extends State<MyApp> {
  late Future<void> _changeState;
  final NfcGlobalVariables globals = NfcGlobalVariables();

  int _counter = 0;
  int _dIVcounter = 0;
  int _dVcounter = 0;
  int _aLcounter = 0;

  String _daemonVersion = 'Unknown';
  String _daemonInterfaceVersion = 'Unknown';
  String _adaptersModel = 'Unknown';
  List<String> _adaptersList = ['Unknown adapter'];
  String _daemonMode = 'Unknown';

  String _adapterInterfaceVersion = 'Unknown';
  bool _adapterEnabled = false;
  bool _adapterPowered = false;
  bool _adapterTargetPresent = false;
  List<String> _adapterSupportedModes = ['Unknown Mode'];
  List<String> _adapterTagsList = ['No tags'];
  String _adapterMode = 'Unknown';
  Map<int, String> _adapterTagsModel = {0: 'Unknown tag'};

  String _tagInterfaceVersion = 'Unknown';
  bool _tagPresent = false;
  String _tagProtocol = 'Unknown';
  String _tagTechnology = 'Unknown';
  String _tagType = 'Unknown';
  List<String> _tagInterfaces = ['Unknown'];
  List<String> _tagNdefRecords = ['Unknown'];

  String _isoDepInterfaceVersion = 'Unknown';
  List<String> _isoDepTransmitResponse = ['Unknown'];

  String _ndefInterfaceVersion = 'Unknown';
  List<String> _ndefFlags = ['Unknown'];
  TypeNameFormat _ndefTypeNF = TypeNameFormat.unknown;
  String _ndefType = 'Unknown';
  String _ndefId = 'Unknown';
  String _ndefPayload = 'Unknown';
  List<ndef.NDEFRecord> _ndefRawData = [];
  ndef.NDEFRecord _ndefRecord = ndef.NDEFRecord();
  List<ndef.NDEFRecord> _ndefRecordList = [ndef.NDEFRecord()];
  List<String> _ndefInterfaces = ['Unknown'];

  String _classicInterfaceVersion = 'Unknown';
  String _classicSerial = 'Unknown';

  String _tt2InterfaceVersion = 'Unknown';
  String _tt2BlockSize = 'Unknown';
  String _tt2DataSize = 'Unknown';
  String _tt2AllData = 'Unknwon';
  String _tt2Serial = 'Unknown';

  final _flutterNfcKitAuroraPlugin = FlutterNfcKitAurora();
  final TextEditingController _controller = TextEditingController();

  StreamSubscription<String?>? _eventSubsription;

  bool _showDaAdWidget = true;
  bool _showTagWidget = false;
  @override
  void initState() {
    super.initState();
    initPlatformState();
    _eventSubsription = _flutterNfcKitAuroraPlugin.checkChanges().listen((event){
      print('Hi. Its canon event: $event');
      setState(() {
        _showDaAdWidget = !_showDaAdWidget;
        _showTagWidget = !_showTagWidget;
      });
      print('$_showDaAdWidget : $_showTagWidget');
      changePlarformState();
    });
  }

  void dispose(){
    _eventSubsription?.cancel();
    super.dispose();
  }

  Future<void> initPlatformState() async {
    getDaemon();
    getAdapter();
    getTag();
    getIsoDep();
    getNdef();
    getTagClassic();
    getTagType2();
  }

  Future<void> getDaemon() async {
    String daemonInterfaceVersion;
    try {
      daemonInterfaceVersion =
          await _flutterNfcKitAuroraPlugin.getDaemonInterfaceVersion() ??
              'Unknown daemon interface version';
    } catch (e) {
      daemonInterfaceVersion = 'Failed to get daemon interface version.';
    }

    String daemonVersion;
    try {
      daemonVersion = await _flutterNfcKitAuroraPlugin.getDaemonVersion() ??
          'Unknown daemon version';
    } catch (e) {
      daemonVersion = 'Failed to get daemon version.';
    }

    List<String> adaptersList;
    try {
      adaptersList = await _flutterNfcKitAuroraPlugin.getDaemonAdaptersList() ??
          ['Unknown adapter'];
      _aLcounter++;
    } catch (e) {
      adaptersList = ['No adapters'];
      _aLcounter--;
    }

    String daemonMode;
    try {
      daemonMode = await _flutterNfcKitAuroraPlugin.getDaemonMode() ??
          'Unknown daemon mode';
    } catch (e) {
      daemonMode = 'Failed to get daemon mode';
    }

    setState(() {
      _daemonInterfaceVersion = daemonInterfaceVersion;
      _daemonVersion = daemonVersion;
      _adaptersList = adaptersList;
      _daemonMode = daemonMode;
      _counter++;
      _aLcounter = _aLcounter;
    });
  }

  Future<void> getAdapter() async {
    String adapterInterfaceVersion;
    try {
      adapterInterfaceVersion =
          await _flutterNfcKitAuroraPlugin.getAdapterInterfaceVersion() ??
              'Unknown adapter interface version';
    } catch (e) {
      adapterInterfaceVersion = 'Failed to get adapter interface version';
    }

    bool adapterEnabled;
    try {
      adapterEnabled =
          await _flutterNfcKitAuroraPlugin.getAdapterEnabled() ?? false;
    } catch (e) {
      adapterEnabled = false;
    }

    bool adapterPowered;
    try {
      adapterPowered =
          await _flutterNfcKitAuroraPlugin.getAdapterPowered() ?? false;
    } catch (e) {
      adapterPowered = false;
    }

    bool adapterTargetPresent;
    try {
      adapterTargetPresent =
          await _flutterNfcKitAuroraPlugin.getAdapterTargetPresent() ?? false;
    } catch (e) {
      adapterTargetPresent = false;
    }

    List<String> adapterSupportedModes;
    try {
      adapterSupportedModes =
          await _flutterNfcKitAuroraPlugin.getAdapterSupportedModes() ??
              ['Unknown mode'];
    } catch (e) {
      adapterSupportedModes = ['Failed to get Supported Modes'];
    }

    String adapterMode;
    try {
      adapterMode = await _flutterNfcKitAuroraPlugin.getAdapterMode() ??
          'Unknown adapter mode';
    } catch (e) {
      adapterMode = 'Failed to get adapter Mode';
    }

    List<String> adapterTagsList;
    try {
      adapterTagsList =
          await _flutterNfcKitAuroraPlugin.getAdapterTagsList() ?? ['No tags'];
    } catch (e) {
      adapterTagsList = ['Failed to get Tags'];
    }

    Map<int, String> adapterTagsModel = {0: 'Unknown tag'};

    setState(() {
      _adapterInterfaceVersion = adapterInterfaceVersion;
      _adapterEnabled = adapterEnabled;
      _adapterPowered = adapterPowered;
      _adapterTargetPresent = adapterTargetPresent;
      _adapterSupportedModes = adapterSupportedModes;
      _adapterMode = adapterMode;
      _adapterTagsList = adapterTagsList;
      _adapterTagsModel = adapterTagsModel;
    });
  }

  Future<void> getTag() async {
    String tagInterfaceVersion;
    try {
      tagInterfaceVersion =
          await _flutterNfcKitAuroraPlugin.getTagInterfaceVersion() ??
              'Unknown tag interface version';
    } catch (e) {
      tagInterfaceVersion = 'Failed to get tag interface version';
    }

    bool tagPresent;
    try {
      tagPresent = await _flutterNfcKitAuroraPlugin.getTagPresent() ?? false;
    } catch (e) {
      tagPresent = false;
    }

    String tagProtocol;
    try {
      tagProtocol = await _flutterNfcKitAuroraPlugin.getTagProtocol() ??
          'Unknown protocol?';
    } catch (e) {
      tagProtocol = 'Failed to get tag protocol';
    }

    String tagTechnology;
    try {
      tagTechnology = await _flutterNfcKitAuroraPlugin.getTagTechnology() ??
          'Unknown technology?';
    } catch (e) {
      tagTechnology = 'Failed to get tag technology';
    }

    String tagType;
    try {
      tagType =
          await _flutterNfcKitAuroraPlugin.getTagType() ?? 'Unknown type?';
    } catch (e) {
      tagType = 'Failed to get tag type';
    }

    List<String> tagInterfaces;
    try {
      tagInterfaces = await _flutterNfcKitAuroraPlugin.getTagInterfaces() ??
          ['Unknown interface?'];
    } catch (e) {
      tagInterfaces = ['Failed to get tag interfaces'];
    }

    List<String> tagNdefRecords;
    try {
      tagNdefRecords = await _flutterNfcKitAuroraPlugin.getTagNdefRecords() ??
          ['Unknown NDEF Records?'];
    } catch (e) {
      tagNdefRecords = ['Failed to get tag ndef records'];
    }

    setState(() {
      _tagInterfaceVersion = tagInterfaceVersion;
      _tagPresent = tagPresent;
      _tagProtocol = tagProtocol;
      _tagTechnology = tagTechnology;
      _tagType = tagType;
      _tagInterfaces = tagInterfaces;
      _tagNdefRecords = tagNdefRecords;
    });
  }

  //-------------------------------- ISO DEP -----------------------------
  Future<void> getIsoDep() async {
    String isoDepInterfaceVersion;
    try {
      isoDepInterfaceVersion =
          await _flutterNfcKitAuroraPlugin.getIsoDepInterfaceVersion() ??
              'Unknown ISO DEP iFace version?';
    } catch (e) {
      isoDepInterfaceVersion = 'Failed to get ISO DEP iFace version';
    }

    List<String> isoDepTransmitResponse;
    try {
      isoDepTransmitResponse =
          await _flutterNfcKitAuroraPlugin.getIsoDepTransmit() ??
              ['Unknwon ISO DEP transmit response?'];
    } catch (e) {
      isoDepTransmitResponse = ['Failed to get ISO DEP transmit response'];
    }

    setState(() {
      _isoDepInterfaceVersion = isoDepInterfaceVersion;
      _isoDepTransmitResponse = isoDepTransmitResponse;
    });
  }

  //-------------------------------- NDEF --------------------------------

  Future<void> getNdef() async {
    String ndefInterfaceVersion;
    try {
      ndefInterfaceVersion =
          await _flutterNfcKitAuroraPlugin.getNdefInterfaceVersion() ??
              'Unknown ndef interface version';
    } on PlatformException {
      ndefInterfaceVersion = 'Failed to get ndef interface version.';
    }

    List<String> ndefFlags;
    try {
      ndefFlags = await _flutterNfcKitAuroraPlugin.getNdefFlags() ??
          ['Unknown ndef flags?'];
    } catch (e) {
      ndefFlags = ['Failed to get ndef flags'];
    }

    TypeNameFormat ndefTypeNF;
    try {
      ndefTypeNF = await _flutterNfcKitAuroraPlugin.getNdefTypeNameFormat() ??
          TypeNameFormat.unknown;
    } catch (e) {
      ndefTypeNF = TypeNameFormat.unknown;
    }

    String ndefType;
    try {
      ndefType = await _flutterNfcKitAuroraPlugin.getNdefType() ??
          'Unknown ndef type?';
    } catch (e) {
      ndefType = 'Failed to get ndef Type';
    }

    String ndefId;
    try {
      ndefId =
          await _flutterNfcKitAuroraPlugin.getNdefId() ?? 'Unknown ndef Id?';
    } catch (e) {
      ndefId = 'Failed to get ndef Id';
    }

    String ndefPayload;
    try {
      ndefPayload = await _flutterNfcKitAuroraPlugin.getNdefPayload() ??
          'Unknown ndef Payload?';
    } catch (e) {
      ndefPayload = 'Failed to get ndef Payload';
    }

    List<ndef.NDEFRecord> ndefRawData;
    try {
      ndefRawData = await _flutterNfcKitAuroraPlugin.getNdefRawData() ?? [];
    } catch (e) {
      ndefRawData = [];
    }
    print("Raw Data: ${ndefRawData}");
    //ndef.NDEFRecord ndefRecord;
    List<ndef.NDEFRecord> ndefRecordList;
    try {
      var result = await _flutterNfcKitAuroraPlugin.getNdefRecord();
      if (result != null) {
        //ndefRecord = result;
        ndefRecordList = result;
      } else {
        //ndefRecord = ndef.NDEFRecord();
        ndefRecordList = [ndef.NDEFRecord()];
      }
    } catch (e) {
      print('exception: ${e}');
      //ndefRecord = ndef.NDEFRecord();
      ndefRecordList = [ndef.NDEFRecord()];
    }
    print('NDEF Record: ${ndefRecordList}');

    //Uint8List typeDecoded = Uint8List.fromList(utf8.encode(ndefType!));
    //Uint8List idDecoded = Uint8List.fromList(utf8.encode(ndefId));
    //Uint8List payloadlDecoded = Uint8List.fromList(utf8.encode(ndefPayload));

    //ndefRecord = ndef.NDEFRecord(type: typeDecoded, tnf: ndefTypeNF, id: idDecoded, payload: payloadlDecoded );
    //print('NDEF Record new: ${ndefRecord}');

    List<String> ndefInterfaces;
    try {
      ndefInterfaces = await _flutterNfcKitAuroraPlugin.getNdefInterfaces() ??
          ['Unknown ndef Interfaces'];
    } catch (e) {
      ndefInterfaces = ['Failed to get ndef Interfaces'];
    }

    setState(() {
      _ndefInterfaceVersion = ndefInterfaceVersion;
      _ndefFlags = ndefFlags;
      _ndefTypeNF = ndefTypeNF;
      _ndefType = ndefType;
      _ndefId = ndefId;
      _ndefPayload = ndefPayload;
      _ndefRawData = ndefRawData;
      _ndefRecordList = ndefRecordList;
      _ndefInterfaces = ndefInterfaces;
    });
  }

  //---------------------------------- TAG CLASSIC ------------------------------------

  Future<void> getTagClassic() async {
    String classicInterfaceVersion;
    try {
      classicInterfaceVersion =
          await _flutterNfcKitAuroraPlugin.getTagClassicInterfaceVersion() ??
              'Unknown classic iFace version';
    } catch (e) {
      classicInterfaceVersion = 'Failed to get classic iFace Version';
    }

    String classicSerial;
    try {
      classicSerial = await _flutterNfcKitAuroraPlugin.getTagClassicSerial() ??
          'Unknown classic serial';
    } catch (e) {
      classicSerial = 'Failed to get classic serial';
    }

    setState(() {
      _classicInterfaceVersion = classicInterfaceVersion;
      _classicSerial = classicSerial;
    });
  }

  //---------------------------------- TAG TYPE 2 ---------------------------------

  Future<void> getTagType2() async {
    String tt2InterfaceVersion;
    try {
      tt2InterfaceVersion =
          await _flutterNfcKitAuroraPlugin.getTagType2InterfaceVersion() ??
              'Unknown tt2 iFace version';
    } catch (e) {
      tt2InterfaceVersion = 'Failed to get tt2 Interface Version';
    }

    String tt2BlockSize;
    try {
      tt2BlockSize = await _flutterNfcKitAuroraPlugin.getTagType2BlockSize() ??
          'Unknown tt2 Block Size';
    } catch (e) {
      tt2BlockSize = 'Failed to get tt2 Block Size';
    }

    String tt2DataSize;
    try {
      tt2DataSize = await _flutterNfcKitAuroraPlugin.getTagType2DataSize() ??
          'Unknown tt2 Data Size';
    } catch (e) {
      tt2DataSize = 'Failed to get tt2 Data Size';
    }

    String tt2AllData;
    try {
      tt2AllData = await _flutterNfcKitAuroraPlugin.getTagType2AllData() ??
          'Unknown tt2 All Data';
    } catch (e) {
      tt2AllData = 'Failed to get tt2 All Data';
    }

    String tt2Serial;
    try {
      tt2Serial = await _flutterNfcKitAuroraPlugin.getTagType2Serial() ??
          'Unknown tt2 Tag Type 2';
    } catch (e) {
      tt2Serial = 'Failed to get tt2 Serial';
    }

    setState(() {
      _tt2InterfaceVersion = tt2InterfaceVersion;
      _tt2BlockSize = tt2BlockSize;
      _tt2DataSize = tt2DataSize;
      _tt2AllData = tt2AllData;
      _tt2Serial = tt2Serial;
    });
  }

  Future<void> updateText() async {
    _controller.text = _daemonInterfaceVersion;
  }

  Future<void> changePlarformState() async {
    await getDaemon();
    await getAdapter();
    await getTag();
    await getIsoDep();
    await getNdef();
    await getTagClassic();
    await getTagType2();
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        backgroundColor: Colors.deepOrangeAccent,
        appBar: AppBar(
          title: Text(
            'NFC Plugin Test',
            style: TextStyle(color: Colors.white),
          ),
          centerTitle: true,
          backgroundColor: Colors.black87,
        ),
        body: SafeArea(
          child: Row(mainAxisAlignment: MainAxisAlignment.start, children: [
            Column(children: [
              /*
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('Updates: $_counter',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('Daemon Interface Version: $_daemonInterfaceVersion',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('Daemon Version: $_daemonVersion',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(
                children: [
                  Text('Adapters:',
                      style: TextStyle(color: Colors.white, fontSize: 10)),
                  SizedBox(height: 15),
                  Column(
                    crossAxisAlignment: CrossAxisAlignment.center,
                    children: _adaptersList
                        .map((item) => Text(item,
                            style:
                                TextStyle(color: Colors.white, fontSize: 10)))
                        .toList(),
                  ),
                ],
              ),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('Adapters list counter: $_aLcounter',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('Daemon mode: $_daemonMode',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 30)),
              Padding(padding: EdgeInsets.only(top: 30)),
              */
              Padding(padding: EdgeInsets.only(top: 15)),
              _showDaAdWidget? TagUnknownWidget0(globals:globals): TagUnknownWidget(globals: globals),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('Tag present: $_tagPresent',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('Tag protocol: $_tagProtocol',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('Tag technology: $_tagTechnology',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('Tag type: $_tagType',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('Tag interfaces:',
                    style: TextStyle(color: Colors.white, fontSize: 10)),
                Column(
                  crossAxisAlignment: CrossAxisAlignment.center,
                  children: _tagInterfaces
                      .map((item) => Text(item,
                          style: TextStyle(color: Colors.white, fontSize: 10)))
                      .toList(),
                ),
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('NDEF Records:',
                    style: TextStyle(color: Colors.white, fontSize: 10)),
                Column(
                  crossAxisAlignment: CrossAxisAlignment.center,
                  children: _tagNdefRecords
                      .map((item) => Text(item,
                          style: TextStyle(color: Colors.white, fontSize: 10)))
                      .toList(),
                ),
              ]),
              /*
              Padding(padding: EdgeInsets.only(top: 30)),
              Row(children: [
                Text('ISO DEP iFace: $_isoDepInterfaceVersion',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(
                children: [
                  Text('ISO DEP response:',
                      style: TextStyle(color: Colors.white, fontSize: 10)),
                  SizedBox(height: 15),
                  Column(
                    crossAxisAlignment: CrossAxisAlignment.center,
                    children: _isoDepTransmitResponse
                        .map((item) => Text(item,
                            style:
                                TextStyle(color: Colors.white, fontSize: 10)))
                        .toList(),
                  ),
                ],
              ),
              */
              Padding(padding: EdgeInsets.only(top: 30)),
              Row(children: [
                Text('NDEF iFace Version: $_ndefInterfaceVersion',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(
                children: [
                  Text('NDEF Flags:',
                      style: TextStyle(color: Colors.white, fontSize: 10)),
                  SizedBox(height: 15),
                  Column(
                    crossAxisAlignment: CrossAxisAlignment.center,
                    children: _ndefFlags
                        .map((item) => Text(item,
                            style:
                                TextStyle(color: Colors.white, fontSize: 10)))
                        .toList(),
                  ),
                ],
              ),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('NDEF TypeNF: $_ndefTypeNF',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('NDEF Type: $_ndefType',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('NDEF Id: $_ndefId',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('NDEF Payload: $_ndefPayload',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text(
                    'NDEF Record: \nid: ${_ndefRecordList[0].idString}, \ntnf: ${_ndefRecordList[0].tnf}, \ntype: ${_ndefRecordList[0].type?.toHexString()}, \npayload: ${_ndefRecordList[0].payload?.toHexString()}',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(
                children: [
                  Text('NDEF Interfaces:',
                      style: TextStyle(color: Colors.white, fontSize: 10)),
                  SizedBox(height: 15),
                  Column(
                    crossAxisAlignment: CrossAxisAlignment.center,
                    children: _ndefInterfaces
                        .map((item) => Text(item,
                            style:
                                TextStyle(color: Colors.white, fontSize: 10)))
                        .toList(),
                  ),
                ],
              ),
              Padding(padding: EdgeInsets.only(top: 30)),
              Row(children: [
                Text('Classic iFace Ver.: $_classicInterfaceVersion',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 10)),
              Row(children: [
                //Text('Classic Serial: $_classicSerial',
                //    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),

              Padding(padding: EdgeInsets.only(top: 30)),
              Row(children: [
                Text('TT2 Serial: $_tt2Serial',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('TT2 iFace: $_tt2InterfaceVersion',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('TT2 Block Size: $_tt2BlockSize',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('TT2 Data Size: $_tt2DataSize',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
              Padding(padding: EdgeInsets.only(top: 15)),
              Row(children: [
                Text('TT2 All Data: $_tt2AllData',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]),
            ]),
            Column(
              children: [
                Column(children: [
                  Row(children: [
                    Text('Adapter Interface Version: $_adapterInterfaceVersion',
                        style: TextStyle(color: Colors.white, fontSize: 10))
                  ]),
                  Padding(padding: EdgeInsets.only(top: 10)),
                  Row(children: [
                    Text('Adapter Enabled: $_adapterEnabled',
                        style: TextStyle(color: Colors.white, fontSize: 10))
                  ]),
                  Padding(padding: EdgeInsets.only(top: 10)),
                  Row(children: [
                    Text('Adapter Powered: $_adapterPowered',
                        style: TextStyle(color: Colors.white, fontSize: 10))
                  ]),
                  Padding(padding: EdgeInsets.only(top: 15)),
                  Row(children: [
                    Text('Adapter Supported Modes:',
                        style: TextStyle(color: Colors.white, fontSize: 10)),
                    Column(
                      crossAxisAlignment: CrossAxisAlignment.center,
                      children: _adapterSupportedModes
                          .map((item) => Text(item,
                              style:
                                  TextStyle(color: Colors.white, fontSize: 10)))
                          .toList(),
                    ),
                  ]),
                  Padding(padding: EdgeInsets.only(top: 15)),
                  Row(children: [
                    Text('Adapter Mode: $_adapterMode',
                        style: TextStyle(color: Colors.white, fontSize: 10))
                  ]),
                  Padding(padding: EdgeInsets.only(top: 15)),
                  Row(children: [
                    Text('Target Present: $_adapterTargetPresent',
                        style: TextStyle(color: Colors.white, fontSize: 10))
                  ]),
                  Padding(padding: EdgeInsets.only(top: 15)),
                  Row(children: [
                    Text('Tags:',
                        style: TextStyle(color: Colors.white, fontSize: 10)),
                    Column(
                      crossAxisAlignment: CrossAxisAlignment.center,
                      children: _adapterTagsList
                          .map((item) => Text(item,
                              style:
                                  TextStyle(color: Colors.white, fontSize: 10)))
                          .toList(),
                    ),
                  ]),
                ]),
              ],
            ),
          ]),
        ),
        floatingActionButton: FloatingActionButton(
          child: Icon(Icons.info, color: Colors.white, size: 35),
          backgroundColor: Colors.black,
          onPressed: () {
            setState(() {
              _changeState = changePlarformState();
            });
          },
        ),
      ),
    );
  }
}

class TagUnknownWidget extends StatelessWidget{
  final NfcGlobalVariables globals;
  TagUnknownWidget({required this.globals});
  @override
  Widget build(BuildContext context){
    return SafeArea(child:
    Row(children: [
                Text('TagUnknown ${globals._counter}',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]));
  }
}

class TagUnknownWidget0 extends StatelessWidget{
  final NfcGlobalVariables globals;
  TagUnknownWidget0({required this.globals});
  @override
  Widget build(BuildContext context){
    return SafeArea(child:
    Row(children: [
                Text('TagUnknown ${globals.counter2}',
                    style: TextStyle(color: Colors.white, fontSize: 10))
              ]));
  }
}
