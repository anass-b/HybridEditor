#ifndef MDICHILD_H
#define MDICHILD_H

#include <QTextEdit>
#include <QWebEngineView>
#include <QWebEnginePage>
#include "Document.h"
#include "Languages.h"
#include "Options.h"

class Editor : public QWebEngineView {
    Q_OBJECT

public:
    Editor(const Options& options);
    bool loadFile(const QString& filePath);
    bool saveFile(const QString& fileName);
    bool save();
    bool saveAs();
    const QString& filePath() const;
    void setGeneratedFilename(const QString& generatedFilename);
    static Languages& languages();
    void setFontFamily(const QString& fontFamily);
    void setFontSize(int fontSize);
    void setTheme(const QString& theme);
    void setCodeFolding(const QString& codeFolding);
    void setKeyBinding(const QString& keyBinding);
    void setSoftWrap(const QString& softWrap);
    void setShowInvisibles(bool showInvisibles);
    void setShowIndentRules(bool showIndentRules);
    void setShowGutter(bool showGutter);
    void setShowPrintMargin(bool showPrintMargin);
    void setUseSoftTab(bool useSoftTab);
    void setHighlightSelectedWord(bool highlightSelectedWord);

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
