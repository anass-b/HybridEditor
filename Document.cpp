#include "Document.h"

void Document::setText(const QString& text)
{
    if (text == _text) return;
    _text = text;
}

const QString& Document::text() const
{
    return _text;
}

void Document::setLang(const QString& lang)
{
    if (_lang == lang) return;
    _lang = lang;
}

const QString& Document::lang() const
{
    return _lang;
}

void Document::setTheme(const QString& theme)
{
    if (_theme == theme) return;
    _theme = theme;
    emit themeSettingsChanged(_theme);
}

const QString& Document::theme() const
{
    return _theme;
}

void Document::setFontFamily(const QString& fontFamily)
{
    if (_fontFamily == fontFamily) return;
    _fontFamily = fontFamily;
    emit fontFamilySettingsChanged(fontFamily);
}

const QString& Document::fontFamily() const
{
    return _fontFamily;
}

void Document::setFontSize(int fontSize)
{
    if (_fontSize == fontSize) return;
    _fontSize = fontSize;
    emit fontSizeSettingsChanged(fontSize);
}

int Document::fontSize() const
{
    return _fontSize;
}

void Document::setCodeFolding(const QString& codeFolding)
{
    if (_codeFolding == codeFolding) return;
    _codeFolding = codeFolding;
    emit codeFoldingSettingsChanged(codeFolding);
}

const QString& Document::codeFolding() const
{
    return _codeFolding;
}

void Document::setKeyBinding(const QString& keyBinding)
{
    if (_keyBinding == keyBinding) return;
    _keyBinding = keyBinding;
    emit keyBindingSettingsChanged(keyBinding);
}

const QString& Document::keyBinding() const
{
    return _keyBinding;
}

void Document::setSoftWrap(const QString& softWrap)
{
    if (_softWrap == softWrap) return;
    _softWrap = softWrap;
    emit softWrapSettingsChanged(softWrap);
}

const QString& Document::softWrap() const
{
    return _softWrap;
}

void Document::setShowInvisibles(bool showInvisibles)
{
    if (_showInvisibles == showInvisibles) return;
    _showInvisibles = showInvisibles;
    emit showInvisiblesSettingsChanged(showInvisibles);
}

bool Document::showInvisibles() const
{
    return _showInvisibles;
}

void Document::setShowIndentRules(bool showIndentRules)
{
    if (_showIndentRules == showIndentRules) return;
    _showIndentRules = showIndentRules;
    emit showIndentRulesSettingsChanged(showIndentRules);
}

bool Document::showIndentRules() const
{
    return _showIndentRules;
}

void Document::setShowGutter(bool showGutter)
{
    if (_showGutter == showGutter) return;
    _showGutter = showGutter;
    emit showGutterSettingsChanged(showGutter);
}

bool Document::showGutter() const
{
    return _showGutter;
}

void Document::setShowPrintMargin(bool showPrintMargin)
{
    if (_showPrintMargin == showPrintMargin) return;
    _showPrintMargin = showPrintMargin;
    emit showPrintMarginSettingsChanged(showPrintMargin);
}

bool Document::showPrintMargin() const
{
    return _showPrintMargin;
}

void Document::setHighlightSelectedWord(bool highlightSelectedWord)
{
    if (_highlightSelectedWord == highlightSelectedWord) return;
    _highlightSelectedWord = highlightSelectedWord;
    emit highlightSelectedWordSettingsChanged(highlightSelectedWord);
}

bool Document::highlightSelectedWord() const
{
    return _highlightSelectedWord;
}

void Document::setUseSoftTab(bool useSoftTab)
{
    if (_useSoftTab == useSoftTab) return;
    _useSoftTab = useSoftTab;
    emit useSoftTabSettingsChanged(useSoftTab);
}

bool Document::useSoftTab() const
{
    return _useSoftTab;
}
