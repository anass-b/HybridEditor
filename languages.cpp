#include "Languages.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMap>

void Languages::load(bool force)
{
    if (!_loaded || force) {
        QFile file(":/lang.json");
        file.open(QIODevice::ReadOnly);
        QString json = file.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(json.toUtf8());
        QJsonArray langJsonArr = jsonDoc.object()["lang"].toArray();
        for (int i = 0; i < langJsonArr.count(); i++) {
            _languages.append(langJsonArr.at(i).toObject());
        }
        _loaded = true;
    }
}

QString Languages::findId(const QString& extension)
{
    for (int i = 0; i < _languages.count(); i++) {
        QJsonObject l = _languages.at(i);
        QString key = l["id"].toString();
        QJsonArray extensions = l["ext"].toArray();
        for (int j = 0; j < extensions.count(); j++) {
            if (extensions.at(j) == extension) {
                return key;
            }
        }
    }
    return "";
}
