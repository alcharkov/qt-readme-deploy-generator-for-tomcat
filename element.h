#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>
#include <QList>
#include <QListWidgetItem>

class Element
{
public:
    Element();

    Element(QString name, QList<QListWidgetItem*> items, int nodes) {
            this->name = name;
            this->items = items;
            this->nodes = nodes;
    }

    QString name;
    int nodes;
    QList<QListWidgetItem*> items;
};

#endif // ELEMENT_H
