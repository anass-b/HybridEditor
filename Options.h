#ifndef OPTIONS_H
#define OPTIONS_H

#include <QString>

class Options
{
public:
    Options();

    bool setFontFamily(const QString& fontFamily);
    const QString& fontFamily() const;

    bool setFontSize(int fontSize);
    int fontSize() const;

    bool setTheme(const QString& theme);
    const QString& theme() const;

    bool setCodeFolding(const QString& codeFolding);
    const QString& codeFolding() const;

    bool setKeyBinding(const QString& keyBinding);
    const QString& keyBinding() const;

    bool setSoftWrap(const QString& softWrap);
    const QString& softWrap() const;

    bool setShowInvisibles(bool showInvisibles);
    bool showInvisibles() const;

    bool setShowIndentRules(bool showIndentRules);
    bool showIndentRules() const;

    bool setShowGutter(bool showGutter);
    bool showGutter() const;

    bool setShowPrintMargin(bool showPrintMargin);
    bool showPrintMargin() const;

    bool setHighlightSelectedWord(bool highlightSelectedWord);
    bool highlightSelectedWord() const;

    bool setUseSoftTab(bool useSoftTab);
    bool useSoftTab() const;

private:
    QString _fontFamily;
    int _fontSize;
    QString _theme;
    QString _codeFolding;
    QString _keyBinding;
    QString _softWrap;
    bool _showInvisibles;
    bool _showIndentRules;
    bool _showGutter;
    bool _showPrintMargin;
    bool _useSoftTab;
    bool _highlightSelectedWord;
};

#endif // OPTIONS_H
