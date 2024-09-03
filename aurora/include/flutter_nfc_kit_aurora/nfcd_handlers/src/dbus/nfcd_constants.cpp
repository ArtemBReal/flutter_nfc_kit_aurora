#include "nfcd_constants.h"

const QString NfcdConstants::nfcdService = QStringLiteral("org.sailfishos.nfc.daemon");
const QString NfcdConstants::nfcdPath = QStringLiteral("/");

const char *NfcdConstants::nfcdDaemonIface = "org.sailfishos.nfc.Daemon";
const char *NfcdConstants::nfcdAdapterIface = "org.sailfishos.nfc.Adapter";
const char *NfcdConstants::nfcdIsoDepIface = "org.sailfishos.nfc.IsoDep";
const char *NfcdConstants::nfcdNdefIface= "org.sailfishos.nfc.NDEF";
const char *NfcdConstants::nfcdTagIface = "org.sailfishos.nfc.Tag";
const char *NfcdConstants::nfcdTagClassicIface = "org.sailfishos.nfc.TagClassic";
const char *NfcdConstants::nfcdTagType2Iface = "org.sailfishos.nfc.TagType2";
const char *NfcdConstants::nfcdPeerIface = "org.sailfishos.nfc.Peer";
