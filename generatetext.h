#ifndef GENERATETEXT_H
#define GENERATETEXT_H
#include <QListWidgetItem>
#include <QObject>
#include <QList>
#include <QString>
#include "element.h"

class GenerateText: QObject
{
    Q_OBJECT
public:
    GenerateText();
    QString build(QList<Element*> listItems, bool updateScript, bool rollbackScript, bool webIncluded);
private:
     void removeLastChars(QString* str, QChar ch);
     void iterateItemsWithAppendedText(QList<QListWidgetItem*>list, QString* text, QString preText, QString afterText);
};

#endif // GENERATETEXT_H
