#ifndef MDICHILD_H
#define MDICHILD_H

#include <QTextEdit>
#include <QWebEngineView>
#include <QWebEnginePage>
#include "Document.h"
#include "Languages.h"

class Editor : public QWebEngineView {
    Q_OBJECT

public:
    Editor();
    bool loadFile(const QString& filePath);
    bool saveFile(const QString& fileName);
    bool save();
    bool saveAs();
    const QString& filePath() const;
    void setGeneratedFilename(const QString& generatedFilename);
    static Languages& languages();

public slots:
    void copy();
    void paste();
    void cut();
    void selectAll();
    void undo();
    void redo();

private:
    QWebEnginePage* _page;
    Document _content;
    QString _filePath;
    QString _generatedFilename;
};

#endif
