#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QString>

class Document : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString text MEMBER _text)
    Q_PROPERTY(QString lang MEMBER _lang)
    Q_PROPERTY(QString fontFamily MEMBER _fontFamily NOTIFY fontFamilySettingsChanged)
    Q_PROPERTY(int fontSize MEMBER _fontSize NOTIFY fontSizeSettingsChanged)
    Q_PROPERTY(QString theme MEMBER _theme NOTIFY themeSettingsChanged)
    Q_PROPERTY(QString codeFolding MEMBER _codeFolding NOTIFY codeFoldingSettingsChanged)
    Q_PROPERTY(QString keyBinding MEMBER _keyBinding NOTIFY keyBindingSettingsChanged)
    Q_PROPERTY(QString softWrap MEMBER _softWrap NOTIFY softWrapSettingsChanged)
    Q_PROPERTY(bool showInvisibles MEMBER _showInvisibles NOTIFY showInvisiblesSettingsChanged)
    Q_PROPERTY(bool showIndentRules MEMBER _showIndentRules NOTIFY showIndentRulesSettingsChanged)
    Q_PROPERTY(bool showGutter MEMBER _showGutter NOTIFY showGutterSettingsChanged)
    Q_PROPERTY(bool showPrintMargin MEMBER _showPrintMargin NOTIFY showPrintMarginSettingsChanged)
    Q_PROPERTY(bool useSoftTab MEMBER _useSoftTab NOTIFY useSoftTabSettingsChanged)
    Q_PROPERTY(bool highlightSelectedWord MEMBER _highlightSelectedWord NOTIFY highlightSelectedWordSettingsChanged)

public:
    explicit Document(QObject* parent = nullptr)
        : QObject(parent)
    {
    }

    void setLang(const QString& lang);
    const QString& lang() const;

    void setText(const QString& text);
    const QString& text() const;

    void setFontFamily(const QString& fontFamily);
    const QString& fontFamily() const;

    void setFontSize(int fontSize);
    int fontSize() const;

    void setTheme(const QString& theme);
    const QString& theme() const;

    void setCodeFolding(const QString& codeFolding);
    const QString& codeFolding() const;

    void setKeyBinding(const QString& keyBinding);
    const QString& keyBinding() const;

    void setSoftWrap(const QString& softWrap);
    const QString& softWrap() const;

    void setShowInvisibles(bool showInvisibles);
    bool showInvisibles() const;

    void setShowIndentRules(bool showIndentRules);
    bool showIndentRules() const;

    void setShowGutter(bool showGutter);
    bool showGutter() const;

    void setShowPrintMargin(bool showPrintMargin);
    bool showPrintMargin() const;

    void setHighlightSelectedWord(bool highlightSelectedWord);
    bool highlightSelectedWord() const;

    void setUseSoftTab(bool useSoftTab);
    bool useSoftTab() const;

signals:
    void fontFamilySettingsChanged(const QString& fontFamily);
    void fontSizeSettingsChanged(int fontSize);
    void themeSettingsChanged(const QString& theme);
    void codeFoldingSettingsChanged(const QString& codeFolding);
    void keyBindingSettingsChanged(const QString& keyBinding);
    void softWrapSettingsChanged(const QString& softWrap);
    void showInvisiblesSettingsChanged(bool showInvisibles);
    void showIndentRulesSettingsChanged(bool showIndentRules);
    void showGutterSettingsChanged(bool showGutter);
    void showPrintMarginSettingsChanged(bool showPrintMargin);
    void useSoftTabSettingsChanged(bool useSoftTab);
    void highlightSelectedWordSettingsChanged(bool highlightSelectedWord);
    void textChanged(const QString& text);

private:
    QString _text;
    QString _lang;
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

#endif // DOCUMENT_H
