#ifndef NFCD_CONSTANTS_H
#define NFCD_CONSTANTS_H

#include <QtCore/QString>

class NfcdConstants {

public:
    static const QString nfcdService;
    static const QString nfcdPath;

    static const char *nfcdDaemonIface;
    static const char *nfcdAdapterIface;
    static const char *nfcdIsoDepIface;
    static const char *nfcdNdefIface;
    static const char *nfcdTagIface;
    static const char *nfcdTagClassicIface;
    static const char *nfcdTagType2Iface;
    static const char *nfcdPeerIface;

private:
    explicit NfcdConstants() = delete;
    ~NfcdConstants() = default;
};

#endif //NFCD_CONSTANTS_H