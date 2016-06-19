#ifndef LANGUAGES_H
#define LANGUAGES_H

#include <QObject>
#include <QJsonObject>
#include <QList>

class Languages
{
public:
    void load(bool force = false);
    QString findId(const QString& extension);

private:
    QList<QJsonObject> _languages;
    bool _loaded = false;
};

#endif // LANGUAGES_H
