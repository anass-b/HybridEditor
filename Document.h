#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QString>

class Document : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString text MEMBER _text)
    Q_PROPERTY(QString lang MEMBER _lang)
public:
    explicit Document(QObject* parent = nullptr)
        : QObject(parent)
    {
    }

    void setText(const QString& text);
    const QString& text() const;
    void setLang(const QString& lang);
    const QString& lang() const;

//signals:
    //void textChanged(const QString& text);

private:
    QString _text;
    QString _lang;
};

#endif // DOCUMENT_H
