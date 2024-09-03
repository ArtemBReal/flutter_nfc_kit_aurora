#ifndef NFCD_TYPIFIER_H
#define NFCD_TYPIFIER_H

#include "qt_headers.h"

class NfcdModeType {
    Q_GADGET

public:
    enum Value {
        P2PInitiator = 0x01,
        ReaderWriter = 0x02,
        P2PTarget = 0x04,
        CardEmulation = 0x08,
    };
    Q_ENUM(Value)

private:

    explicit NfcdModeType() = delete;
    ~NfcdModeType() = delete;
};


class NfcdTagProtocolType {
    Q_GADGET

public:
    enum Value {
        UnknownProtocol = 0x00,
        Type1 = 0x01,
        Type2 = 0x02,
        Type3 = 0x03,
        Type4A = 0x04,
        Type4B = 0x08,
        DEP = 0x20,
        Classic = 0x21,
    };
    Q_ENUM(Value)

private:
    explicit NfcdTagProtocolType() = delete;
    ~NfcdTagProtocolType() = delete;
};


class NfcdTagTechnologyType {
    Q_GADGET

public:
    enum Value {
        UnknownTechnology = 0x00,
        NfcA = 0x01,
        NfcB = 0x02,
        NfcF = 0x04,
    };
    Q_ENUM(Value)

private:
    explicit NfcdTagTechnologyType() = delete;
    ~NfcdTagTechnologyType() = delete;
};

class NfcdTagTypeType {
    Q_GADGET

public:
    enum Value {
        UnknownType = 0x00,
        TypeFelica = 0x01,
        TypeMifareClassic = 0x02,
        TypeMifareUlralight = 0x04,
    };
    Q_ENUM(Value)

private:
    explicit NfcdTagTypeType() = delete;
    ~NfcdTagTypeType() = delete;
};

class NfcdNdefFlagType {
    Q_GADGET

public:
    enum Value {
        FirstRecord = 0x01,
        LastRecord = 0x02,
    };
    Q_ENUM(Value)

private:
    explicit NfcdNdefFlagType() = delete;
    ~NfcdNdefFlagType() = delete;
};

class NfcdNdefTNFType {
    Q_GADGET

public:
    enum Value {
        TNF0 = 0x00,
        TNF1 = 0x01,
        TNF2 = 0x02,
        TNF3 = 0x03,
        TNF4 = 0x04,
        TNF5 = 0x05,
        TNF6 = 0x06,
        TNF7 = 0x07,
    };
    Q_ENUM(Value)

private:
    explicit NfcdNdefTNFType() = delete;
    ~NfcdNdefTNFType() = delete;
};

struct NfcdIsoDepResult {
    Q_GADGET

    Q_PROPERTY(QString response MEMBER response)
    Q_PROPERTY(uchar sw1 MEMBER sw1)
    Q_PROPERTY(uchar sw2 MEMBER sw2)

public:
    QString response { QString::null};
    quint8 sw1 { 0 };
    quint8 sw2 { 0 };
};

using NfcdMode = NfcdModeType::Value;
using NfcdModes = QList<qint32>;
using NfcdTagProtocol = NfcdTagProtocolType::Value;
using NfcdTagProtocols = QList<qint32>;
using NfcdTagType = NfcdTagTypeType::Value;
using NfcdTagTypes = QList<qint32>;
using NfcdTagTechnology = NfcdTagTechnologyType::Value;
using NfcdTagTechnologies = QList<qint32>;
using NfcdNdefFlag = NfcdNdefFlagType::Value;
using NfcdNdefFlags = QList<qint32>;
using NfcdNdefTNF = NfcdNdefTNFType::Value;
using NfcdNdefTNFs = QList<qint32>;

Q_DECLARE_METATYPE(NfcdIsoDepResult)

#endif // NFCD_TYPIFIER_H