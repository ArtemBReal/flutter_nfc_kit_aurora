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
  State<MyApp> createState() => _MainPage();
}

class NfcGlobalVariables {
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
  StreamSubscription<String?>? _eventSubscription;
}

class _MainPage extends State<MyApp> {
  late Future<void> _changeState;
  final NfcGlobalVariables globals = NfcGlobalVariables();

  final _flutterNfcKitAuroraPlugin = FlutterNfcKitAurora();
  final TextEditingController _controller = TextEditingController();

  StreamSubscription<String?>? _eventSubsription;

  bool _showDaAdWidget = true;
  bool _showTagWidget = false;

  @override
  void initState() {
    super.initState();
    initPlatformState();
    _eventSubsription =
        _flutterNfcKitAuroraPlugin.checkChanges().listen((event) {
      print('Hi. Its canon event: $event');
      setState(() {
        _showDaAdWidget = !_showDaAdWidget;
        _showTagWidget = !_showTagWidget;
      });
      print('$_showDaAdWidget : $_showTagWidget');
      changePlarformState();
    });
  }

  void dispose() {
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

  //------------------------ DAEMON --------------------------------

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
      globals._aLcounter++;
    } catch (e) {
      adaptersList = ['No adapters'];
      globals._aLcounter--;
    }

    String daemonMode;
    try {
      daemonMode = await _flutterNfcKitAuroraPlugin.getDaemonMode() ??
          'Unknown daemon mode';
    } catch (e) {
      daemonMode = 'Failed to get daemon mode';
    }

    setState(() {
      globals._daemonInterfaceVersion = daemonInterfaceVersion;
      globals._daemonVersion = daemonVersion;
      globals._adaptersList = adaptersList;
      globals._daemonMode = daemonMode;
      globals._counter++;
      globals._aLcounter = 0;
    });
  }

  //--------------------------------- ADAPTER --------------------------------

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
      globals._adapterInterfaceVersion = adapterInterfaceVersion;
      globals._adapterEnabled = adapterEnabled;
      globals._adapterPowered = adapterPowered;
      globals._adapterTargetPresent = adapterTargetPresent;
      globals._adapterSupportedModes = adapterSupportedModes;
      globals._adapterMode = adapterMode;
      globals._adapterTagsList = adapterTagsList;
      globals._adapterTagsModel = adapterTagsModel;
    });
  }

  //------------------------------- TAG ---------------------------

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
      globals._tagInterfaceVersion = tagInterfaceVersion;
      globals._tagPresent = tagPresent;
      globals._tagProtocol = tagProtocol;
      globals._tagTechnology = tagTechnology;
      globals._tagType = tagType;
      globals._tagInterfaces = tagInterfaces;
      globals._tagNdefRecords = tagNdefRecords;
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
      globals._isoDepInterfaceVersion = isoDepInterfaceVersion;
      globals._isoDepTransmitResponse = isoDepTransmitResponse;
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

    // Отладочная печать 
    print("Raw Data: ${ndefRawData}");

    List<ndef.NDEFRecord> ndefRecordList;
    try {
      var result = await _flutterNfcKitAuroraPlugin.getNdefRecord();
      if (result != null) {
        ndefRecordList = result;
      } else {
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
      globals._ndefInterfaceVersion = ndefInterfaceVersion;
      globals._ndefFlags = ndefFlags;
      globals._ndefTypeNF = ndefTypeNF;
      globals._ndefType = ndefType;
      globals._ndefId = ndefId;
      globals._ndefPayload = ndefPayload;
      globals._ndefRawData = ndefRawData;
      globals._ndefRecordList = ndefRecordList;
      globals._ndefInterfaces = ndefInterfaces;
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
      globals._classicInterfaceVersion = classicInterfaceVersion;
      globals._classicSerial = classicSerial;
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
      globals._tt2InterfaceVersion = tt2InterfaceVersion;
      globals._tt2BlockSize = tt2BlockSize;
      globals._tt2DataSize = tt2DataSize;
      globals._tt2AllData = tt2AllData;
      globals._tt2Serial = tt2Serial;
    });
  }

  Future<void> updateText() async {
    _controller.text = globals._daemonInterfaceVersion;
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
      backgroundColor: Color(0xFFCBCBE9),
      body: SingleChildScrollView(
        child: _showTagWidget
            ? TagContainer(globals: globals)
            : Column(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  _showDaAdWidget ? DaemonInfo(globals: globals) : SizedBox(),
                  _showDaAdWidget
                      ? Column(
                          mainAxisAlignment: MainAxisAlignment.center,
                          children: [
                            (globals._adapterEnabled && globals._adapterPowered)
                                ? AdapterInfo(globals: globals)
                                : SizedBox(height: 15),
                            Warning(globals: globals)
                          ],
                        )
                      : SizedBox(),
                ],
              ),
      ),
    ));
  }
}

class DaemonExpandedBlock extends StatelessWidget {
  final NfcGlobalVariables globals;
  DaemonExpandedBlock({required this.globals});

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Column(
        children: [
          Column(children: [
            Row(children: [
              Text(
                  'Daemon Interface Version: ${globals._daemonInterfaceVersion}',
                  style: TextStyle(color: Colors.white, fontSize: 10))
            ]),
            Padding(padding: EdgeInsets.only(top: 10)),
          ]),
        ],
      ),
    );
  }
}

class AdapterExpandedBlock extends StatelessWidget {
  final NfcGlobalVariables globals;
  AdapterExpandedBlock({required this.globals});

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Column(
        children: [
          Column(children: [
            Row(children: [
              Text(
                  'Adapter Interface Version: ${globals._adapterInterfaceVersion}',
                  style: TextStyle(color: Colors.white, fontSize: 10))
            ]),
            Padding(padding: EdgeInsets.only(top: 10)),
          ]),
        ],
      ),
    );
  }
}

class TagWidget extends StatelessWidget {
  final NfcGlobalVariables globals;
  TagWidget({required this.globals});

  @override
  Widget build(BuildContext context) {
    return Container(
      padding: EdgeInsets.all(20),
      color: Colors.white,
      child: Text(
        'Tag widget: ${globals._tagInterfaceVersion}',
        style: TextStyle(fontSize: 24),
      ),
    );
  }
}

class DaemonInfo extends StatelessWidget {
  final NfcGlobalVariables globals;
  DaemonInfo({required this.globals});

  @override
  Widget build(BuildContext context) {
    return Center(
      child: Padding(
        padding: const EdgeInsets.fromLTRB(8.0, 120.0, 8.0, 8),
        child: Card(
            elevation: 4.0,
            shape: RoundedRectangleBorder(
              borderRadius: BorderRadius.circular(10.0),
            ),
            child: SingleChildScrollView(
                padding: EdgeInsets.all(16.0),
                child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      Row(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        children: [
                          Text(
                            'Информация о демоне NFCD',
                            style: TextStyle(
                              color: Colors.black,
                              fontSize: 20.0,
                              fontFamily: 'Inter',
                              fontWeight: FontWeight.w700,
                              height: 0,
                            ),
                          ),
                        ],
                      ),
                      SizedBox(height: 15),
                      Text(
                        'Версия демона: ${globals._daemonVersion}',
                        style: TextStyle(
                          color: Colors.black,
                          fontSize: 15.0,
                          fontFamily: 'Inter',
                          fontWeight: FontWeight.w500,
                          height: 0,
                        ),
                      ),
                      Text(
                        'Версия интерфейса: ${globals._daemonInterfaceVersion}',
                        style: TextStyle(
                          color: Colors.black,
                          fontSize: 15.0,
                          fontFamily: 'Inter',
                          fontWeight: FontWeight.w500,
                          height: 0,
                        ),
                      ),
                    ]))),
      ),
    );
  }
}

class AdapterInfo extends StatelessWidget {
  final NfcGlobalVariables globals;
  AdapterInfo({required this.globals});

  @override
  Widget build(BuildContext context) {
    return Center(
      child: Padding(
        padding: const EdgeInsets.all(8.0),
        child: Card(
          elevation: 4.0,
          shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(10.0),
          ),
          child: SingleChildScrollView(
            padding: EdgeInsets.all(16.0),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Row(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text(
                      'Адаптер',
                      style: TextStyle(
                        color: Colors.black,
                        fontSize: 20.0,
                        fontFamily: 'Inter',
                        fontWeight: FontWeight.w700,
                        height: 0,
                      ),
                    ),
                  ],
                ),
                SizedBox(height: 15),
                Row(
                  children: [
                    Text('Путь до адаптера: ',
                        style: TextStyle(
                          color: Colors.black,
                          fontSize: 15.0,
                          fontWeight: FontWeight.w500,
                        )),
                    SizedBox(height: 15),
                    Column(
                      crossAxisAlignment: CrossAxisAlignment.center,
                      children: globals._adaptersList
                          .map((item) => Text(item,
                              style: TextStyle(
                                color: Colors.black,
                                fontSize: 15.0,
                                fontWeight: FontWeight.w500,
                              )))
                          .toList(),
                    ),
                  ],
                ),
                Text(
                  'Версия интерфейса: ${globals._adapterInterfaceVersion}',
                  style: TextStyle(
                    color: Colors.black,
                    fontSize: 15.0,
                    fontWeight: FontWeight.w500,
                  ),
                ),
                Text(
                  'Доступность: ${globals._adapterEnabled}',
                  style: TextStyle(
                    color: Colors.black,
                    fontSize: 15.0,
                    fontWeight: FontWeight.w500,
                  ),
                ),
                Text(
                  'Питание: ${globals._adapterPowered}',
                  style: TextStyle(
                    color: Colors.black,
                    fontSize: 15.0,
                    fontWeight: FontWeight.w500,
                  ),
                ),
                Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text('Поддерживаемые режимы: ',
                        style: TextStyle(
                          color: Colors.black,
                          fontSize: 15.0,
                          fontWeight: FontWeight.w500,
                        )),
                    Row(
                      children: [
                        SizedBox(width: 40),
                        Column(
                          crossAxisAlignment: CrossAxisAlignment.start,
                          children: globals._adapterSupportedModes
                              .map((item) => Text(
                                    item,
                                    style: TextStyle(
                                      color: Colors.black,
                                      fontSize: 15.0,
                                      fontWeight: FontWeight.w500,
                                    ),
                                    softWrap: true,
                                    overflow: TextOverflow.ellipsis,
                                  ))
                              .toList(),
                        ),
                      ],
                    )
                  ],
                ),
                Text(
                  'Текущий режим: ${globals._adapterMode}',
                  style: TextStyle(
                    color: Colors.black,
                    fontSize: 15.0,
                    fontWeight: FontWeight.w500,
                  ),
                ),
                Text(
                  'Наличие метки: ${globals._adapterTargetPresent}',
                  style: TextStyle(
                    color: Colors.black,
                    fontSize: 15.0,
                    fontWeight: FontWeight.w500,
                  ),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}

class Warning extends StatelessWidget {
  final NfcGlobalVariables globals;
  Warning({required this.globals});
  @override
  Widget build(BuildContext context) {
    Widget warningText;
    Color warningBorderColor;

    if (globals._adapterPowered == true && globals._adapterEnabled == true) {
      warningText = Text(
        'Для получения информации о метке приложите её к задней панели устройства',
        textAlign: TextAlign.center,
        style: TextStyle(
          color: Colors.black,
          fontSize: 20.0,
          fontFamily: 'Inter',
          fontWeight: FontWeight.w700,
          height: 1.0,
        ),
      );
      warningBorderColor = Color.fromARGB(255, 10, 219, 69);
    } else {
      warningText = Text(
        'Для работы с NFC-метками включите адаптер',
        textAlign: TextAlign.center,
        style: TextStyle(
          color: Colors.redAccent,
          fontSize: 20.0,
          fontFamily: 'Inter',
          fontWeight: FontWeight.w700,
          height: 1.0,
        ),
      );
      warningBorderColor = Colors.redAccent;
    }

    return Center(
        child: Padding(
      padding: const EdgeInsets.all(10.0),
      child: Card(
          //elevation: 4.0,
          shape: RoundedRectangleBorder(
              side: BorderSide(color: warningBorderColor),
              borderRadius: BorderRadius.circular(10.0)),
          child: SingleChildScrollView(
              padding: EdgeInsets.all(16.0),
              child: Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    warningText,
                  ]))),
    ));
  }
}

class TagContainer extends StatelessWidget {
  final NfcGlobalVariables globals;
  TagContainer({required this.globals});
  @override
  Widget build(BuildContext context) {
    Widget tagInfo;
    Widget ndefRecord;

    if (globals._tagNdefRecords.isEmpty) {
      ndefRecord = Text(
        'NDEF-записей нет',
        textAlign: TextAlign.center,
        style: TextStyle(
          color: Colors.black,
          fontSize: 20.0,
          fontFamily: 'Inter',
          fontWeight: FontWeight.w700,
          height: 1.0,
        ),
      );
    } else {
      ndefRecord = Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Row(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Text(
                'NDEF-запись',
                style: TextStyle(
                  color: Colors.black,
                  fontSize: 15.0,
                  fontFamily: 'Inter',
                  fontWeight: FontWeight.w700,
                  height: 0,
                ),
              ),
            ],
          ),
          SizedBox(
            height: 10.0,
          ),
          Text(
            'Версия интерфейса: ${globals._ndefInterfaceVersion}',
            style: TextStyle(
              color: Colors.black,
              fontSize: 15.0,
              fontFamily: 'Inter',
              fontWeight: FontWeight.w500,
              height: 0,
            ),
          ),
          Text(
            'TNF: ${globals._ndefRecordList[0].tnf}',
            style: TextStyle(
              color: Colors.black,
              fontSize: 15.0,
              fontFamily: 'Inter',
              fontWeight: FontWeight.w500,
              height: 0,
            ),
          ),
          Text(
            'Тип: ${globals._ndefRecordList[0].type}',
            style: TextStyle(
              color: Colors.black,
              fontSize: 15.0,
              fontFamily: 'Inter',
              fontWeight: FontWeight.w500,
              height: 0,
            ),
          ),
          Text(
            'ID: ${globals._ndefRecordList[0].idString}',
            style: TextStyle(
              color: Colors.black,
              fontSize: 15.0,
              fontFamily: 'Inter',
              fontWeight: FontWeight.w500,
              height: 0,
            ),
          ),
          Text(
            'Payload: ${globals._ndefRecordList[0].payload}',
            style: TextStyle(
              color: Colors.black,
              fontSize: 15.0,
              fontFamily: 'Inter',
              fontWeight: FontWeight.w500,
              height: 0,
            ),
          ),
        ],
      );
    }

    if (globals._tagInterfaces.any((str) => str.contains("TagClassic"))) {
      tagInfo = Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Row(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Text(
                'Данные с интерфейса TagClassic',
                style: TextStyle(
                  color: Colors.black,
                  fontSize: 15.0,
                  fontFamily: 'Inter',
                  fontWeight: FontWeight.w700,
                  height: 0,
                ),
              ),
            ],
          ),
          SizedBox(
            height: 10.0,
          ),
          Text(
            'Версия интерфейса: ${globals._classicInterfaceVersion}',
            style: TextStyle(
              color: Colors.black,
              fontSize: 15.0,
              fontFamily: 'Inter',
              fontWeight: FontWeight.w500,
              height: 0,
            ),
          ),
          Text(
            'Серийный номер: ${globals._classicSerial}',
            style: TextStyle(
              color: Colors.black,
              fontSize: 15.0,
              fontFamily: 'Inter',
              fontWeight: FontWeight.w500,
              height: 0,
            ),
          ),
        ],
      );
    } else if (globals._tagInterfaces.any((str) => str.contains("TagType2"))) {
      tagInfo = Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Row(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Text(
                'Данные с интерфейса TagType2',
                style: TextStyle(
                  color: Colors.black,
                  fontSize: 15.0,
                  fontFamily: 'Inter',
                  fontWeight: FontWeight.w700,
                  height: 0,
                ),
              ),
            ],
          ),
          SizedBox(
            height: 10.0,
          ),
          Text(
            'Версия интерфейса: ${globals._tt2InterfaceVersion}',
            style: TextStyle(
              color: Colors.black,
              fontSize: 15.0,
              fontFamily: 'Inter',
              fontWeight: FontWeight.w500,
              height: 0,
            ),
          ),
          Text(
            'Серийный номер: ${globals._tt2Serial}',
            style: TextStyle(
              color: Colors.black,
              fontSize: 15.0,
              fontFamily: 'Inter',
              fontWeight: FontWeight.w500,
              height: 0,
            ),
          ),
          Text(
            'Данные: ${globals._tt2AllData}',
            style: TextStyle(
              color: Colors.black,
              fontSize: 15.0,
              fontFamily: 'Inter',
              fontWeight: FontWeight.w500,
              height: 0,
            ),
          ),
        ],
      );
    } else if (globals._tagInterfaces.any((str) => str.contains("IsoDep"))) {
      tagInfo = Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Row(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Text(
                'Данные с интерфейса IsoDep',
                style: TextStyle(
                  color: Colors.black,
                  fontSize: 15.0,
                  fontFamily: 'Inter',
                  fontWeight: FontWeight.w700,
                  height: 0,
                ),
              ),
            ],
          ),
          SizedBox(
            height: 10.0,
          ),
          Text(
            'Версия интерфейса: ${globals._isoDepInterfaceVersion}',
            style: TextStyle(
              color: Colors.black,
              fontSize: 15.0,
              fontFamily: 'Inter',
              fontWeight: FontWeight.w500,
              height: 0,
            ),
          ),
          Column(
            children: [
              Text('Ответ на запрос: ',
                  style: TextStyle(
                    color: Colors.black,
                    fontSize: 15.0,
                    fontWeight: FontWeight.w500,
                  )),
              SizedBox(width: 40),
              Column(
                crossAxisAlignment: CrossAxisAlignment.center,
                children: globals._isoDepTransmitResponse
                    .map((item) => Text(item,
                        style: TextStyle(
                          color: Colors.black,
                          fontSize: 15.0,
                          fontWeight: FontWeight.w500,
                        )))
                    .toList(),
              ),
            ],
          ),
        ],
      );
    } else {
      tagInfo = Text(
        'Все доступные данные получены',
        textAlign: TextAlign.center,
        style: TextStyle(
          color: Colors.black,
          fontSize: 20.0,
          fontFamily: 'Inter',
          fontWeight: FontWeight.w700,
          height: 1.0,
        ),
      );
    }

    return Center(
      child: Padding(
          padding: const EdgeInsets.fromLTRB(8.0, 100.0, 8.0, 8.0),
          child: Card(
              elevation: 4.0,
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(10.0),
              ),
              child: SingleChildScrollView(
                  padding: EdgeInsets.all(16.0),
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      Row(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        children: [
                          Text(
                            'NFC-метка',
                            style: TextStyle(
                              color: Colors.black,
                              fontSize: 20.0,
                              fontFamily: 'Inter',
                              fontWeight: FontWeight.w700,
                              height: 0,
                            ),
                          ),
                        ],
                      ),
                      SizedBox(
                        height: 15.0,
                      ),
                      Row(
                        children: [
                          Text('Путь: ',
                              style: TextStyle(
                                color: Colors.black,
                                fontSize: 15.0,
                                fontWeight: FontWeight.w500,
                              )),
                          SizedBox(height: 15),
                          Column(
                            crossAxisAlignment: CrossAxisAlignment.center,
                            children: globals._adapterTagsList
                                .map((item) => Text(item,
                                    style: TextStyle(
                                      color: Colors.black,
                                      fontSize: 15.0,
                                      fontWeight: FontWeight.w500,
                                    )))
                                .toList(),
                          ),
                        ],
                      ),
                      Text(
                        'Тип: ${globals._tagType}',
                        style: TextStyle(
                          color: Colors.black,
                          fontSize: 15.0,
                          fontFamily: 'Inter',
                          fontWeight: FontWeight.w500,
                          height: 0,
                        ),
                      ),
                      Text(
                        'Версия интерфейса: ${globals._tagInterfaceVersion}',
                        style: TextStyle(
                          color: Colors.black,
                          fontSize: 15.0,
                          fontFamily: 'Inter',
                          fontWeight: FontWeight.w500,
                          height: 0,
                        ),
                      ),
                      Text(
                        'Технология: ${globals._tagTechnology}',
                        style: TextStyle(
                          color: Colors.black,
                          fontSize: 15.0,
                          fontFamily: 'Inter',
                          fontWeight: FontWeight.w500,
                          height: 0,
                        ),
                      ),
                      Column(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        children: [
                          Text('Интерфейсы обмена: ',
                              style: TextStyle(
                                color: Colors.black,
                                fontSize: 15.0,
                                fontWeight: FontWeight.w500,
                              )),
                          Row(
                            children: [
                              SizedBox(width: 40),
                              Column(
                                crossAxisAlignment: CrossAxisAlignment.start,
                                children: globals._tagInterfaces
                                    .map((item) => Text(
                                          item,
                                          style: TextStyle(
                                            color: Colors.black,
                                            fontSize: 15.0,
                                            fontWeight: FontWeight.w500,
                                          ),
                                          softWrap: true,
                                          overflow: TextOverflow.ellipsis,
                                        ))
                                    .toList(),
                              ),
                            ],
                          )
                        ],
                      ),
                      
                      Column(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        children: [
                          Text('NDEF-записи: ',
                              style: TextStyle(
                                color: Colors.black,
                                fontSize: 15.0,
                                fontWeight: FontWeight.w500,
                              )),
                          Row(
                            children: [
                              SizedBox(width: 40),
                              Column(
                                crossAxisAlignment: CrossAxisAlignment.center,
                                children: globals._tagNdefRecords
                                    .map((item) => Text(
                                          item,
                                          style: TextStyle(
                                            color: Colors.black,
                                            fontSize: 15.0,
                                            fontWeight: FontWeight.w500,
                                          ),
                                          softWrap: true,
                                          overflow: TextOverflow.ellipsis,
                                        ))
                                    .toList(),
                              ),
                            ],
                          )
                        ],
                      ),
                      

          
                      SizedBox(height: 15.0),
                      Divider(
                        color: Colors.grey,
                        thickness: 2.0,
                      ),
                      SizedBox(height: 15.0),
                      ndefRecord,
                      SizedBox(height: 15.0),
                      Divider(
                        color: Colors.grey,
                        thickness: 2.0,
                      ),
                      SizedBox(height: 15.0),
                      tagInfo,
                    ],
                  )))),
    );
  }
}

