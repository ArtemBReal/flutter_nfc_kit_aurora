#ifndef FLUTTER_PLUGIN_FLUTTER_NFC_KIT_AURORA_PLUGIN_HELP_FUNCTIONS_H
#define FLUTTER_PLUGIN_FLUTTER_NFC_KIT_AURORA_PLUGIN_HELP_FUNCTIONS_H

#include <flutter_nfc_kit_aurora/qt_headers.h>

class HelpFunctions final : public QObject
{
    Q_OBJECT

public:
    explicit HelpFunctions(QObject *parent = nullptr);
    QString fromQBAtoQStr(const QByteArray inputArray);
    QString fromRDtoStr(const QByteArray inputArray);

private:

};

#endif // FLUTTER_PLUGIN_FLUTTER_NFC_KIT_AURORA_PLUGIN_HELP_FUNCTIONS_H