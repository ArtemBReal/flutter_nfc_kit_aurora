#include "help_functions.h"

HelpFunctions::HelpFunctions(QObject *parent)
{
}

QString HelpFunctions::fromQBAtoQStr(const QByteArray inputArray){
    if (!inputArray.isEmpty()){
        qDebug() << "Input array 1: " << inputArray;
        return QString::fromLatin1(inputArray.toHex());
    } else {
        qDebug() << "Input array Empty: " << inputArray;
        QString empty = QStringLiteral("empty");
        return empty;
    }
}

QString HelpFunctions::fromRDtoStr(const QByteArray inputArray){
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString string = codec->toUnicode(inputArray);
    const QChar *qCharPointer = string.constData();

    return QString::fromRawData(qCharPointer, inputArray.size());
}
