#include "generatetext.h"
#include <QList>
#include <string>
#include "element.h"

GenerateText::GenerateText()
{


}

/*
Pre:
1. backup app, svc:
    * war
    * esavitarna.application.properties files
    * jasperReports
2. backup web.
3. backup db.

Install:
1. Stop app1 & app2 & svc.
2. Update app1 from app folder (war, properties, jasperReports).
3. Update app2 from app folder (war, properties, jasperReports).
4. Update svc from svc folder (war, properties, jasperReports).
5. Execute db/update.sql script on esav DB.
6. Start svc & app1 & app2.
7. Update web


Rollback:
1. restore DB
2. restore app & svc war, esavitarna.application.properties and jasperReports files & restart services.
3. restore web

 */

QString GenerateText::build(QList<Element*> listItems, bool updateScript, bool rollbackScript, bool webIncluded)
 {
    QString text = "Pre:";
    text += "\n";

    int cnt = 1;

    //Pre

    bool anyService = false;
    Q_FOREACH (Element* element, listItems) {
        if(!element->items.isEmpty()) {
            anyService = true;
            text.append(QString::number(cnt) + ". backup "  + element->name + ":\n");
            this->iterateItemsWithAppendedText(element->items, &text, "\t* ", "\n");
            cnt++;
        }
    }

    if(webIncluded) {
        text.append(QString::number(cnt) + ". backup web.");
        text.append("\n");
        cnt++;
    }

    if(updateScript) {
        text.append(QString::number(cnt) + ". backup db.");
        text.append("\n");
        cnt++;
    }


    //Install
    text.append("\n");
    text.append("Install:");
    text.append("\n");

    cnt = 1;
    if (anyService) {
        text.append(QString::number(cnt) + ". stop");
    }
    Q_FOREACH (Element* element, listItems) {
        if(!element->items.isEmpty()) {
            if(element->nodes > 1) {
                for(int i = 1; i <= element->nodes; i++) {
                    text.append(" " + element->name + QString::number(i) + " &");
                }
            } else {
                text.append(" " + element->name + " &");
            }
        }
    }

    if (anyService) {
        cnt++;
        this->removeLastChars(&text, '&');
        this->removeLastChars(&text, ' ');
        text.append(".");
        text.append("\n");
    }

    Q_FOREACH (Element* element, listItems) {
        if(!element->items.isEmpty()) {
            if(element->nodes > 1) {
                for(int i = 1; i <= element->nodes; i++) {
                    text.append(QString::number(cnt) + ". update");
                    text.append(" " + element->name + QString::number(i) + " from " + element->name + " folder (");
                    this->iterateItemsWithAppendedText(element->items, &text, "", ", ");
                    this->removeLastChars(&text, ',');
                    text.append(").");
                    text.append("\n");
                    cnt++;
                }
            } else {
                text.append(QString::number(cnt) + ". update");
                text.append(" " + element->name + " from " + element->name + " folder (");
                this->iterateItemsWithAppendedText(element->items, &text, "", ", ");
                this->removeLastChars(&text, ',');
                text.append(").");
                text.append("\n");
                cnt++;
            }

        }
    }


    if(updateScript) {
        text.append(QString::number(cnt) + ". execute db/update.sql script on esav DB.");
        text.append("\n");
        cnt++;
    }


    if(anyService) {
        text.append(QString::number(cnt) + ". start");
    }

    Q_FOREACH (Element* element, listItems) {
        if(!element->items.isEmpty()) {
            if(element->nodes > 1) {
                for(int i = 1; i <= element->nodes; i++) {
                    text.append(" " + element->name + QString::number(i) + " &");
                }
            } else {
                text.append(" " + element->name + " &");
            }
        }
    }

    if (anyService) {
        this->removeLastChars(&text, '&');
        this->removeLastChars(&text, ' ');
        text.append(".");
        text.append("\n");
        cnt++;
    }

    if(webIncluded) {
        text.append(QString::number(cnt) + ". update web.");
        text.append("\n");
        cnt++;
    }

    text.append("\n");
    text.append("Rollback:");
    text.append("\n");

    cnt = 1;
    if(rollbackScript) {
        text.append(QString::number(cnt) + ". rollback script at db/update.sql or if it's fails then restore DB.");
        text.append("\n");
        cnt++;
    } else if(updateScript) {
        text.append(QString::number(cnt) + ". restore DB.");
        text.append("\n");
        cnt++;
    }

    Q_FOREACH (Element* element, listItems) {
        if(!element->items.isEmpty()) {
            text.append(QString::number(cnt) + ". restore "  + element->name + ":\n");
            this->iterateItemsWithAppendedText(element->items, &text, "\t* ", "\n");
            cnt++;
        }
    }

    if (anyService) {
        text.append(QString::number(cnt) + ". restart services.");
        text.append("\n");
        cnt++;
    }

    if(webIncluded) {
        text.append(QString::number(cnt) + ". restore web.");
        text.append("\n");
        cnt++;
    }

    return text;
}

void GenerateText::removeLastChars(QString* str, QChar ch) {
     str->truncate(str->lastIndexOf(ch));
}

void GenerateText::iterateItemsWithAppendedText(QList<QListWidgetItem*>list, QString* text, QString preText, QString afterText) {
    Q_FOREACH (QListWidgetItem* item, list) {
        text->append(preText + item->text());
        text->append(afterText);
    }
}
