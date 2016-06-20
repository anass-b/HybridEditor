#include "Options.h"

Options::Options() :
    _fontFamily("Monaco"),
    _fontSize(12),
    _theme("twilight"),
    _codeFolding("markbegin"),
    _keyBinding("ace"),
    _softWrap("off"),
    _showInvisibles(false),
    _showIndentRules(true),
    _showGutter(true),
    _showPrintMargin(true),
    _useSoftTab(true),
    _highlightSelectedWord(true)
{
}

bool Options::setTheme(const QString& theme)
{
    if (_theme == theme) return false;
    _theme = theme;
    return true;
}

const QString& Options::theme() const
{
    return _theme;
}

bool Options::setFontFamily(const QString& fontFamily)
{
    if (_fontFamily == fontFamily) return false;
    _fontFamily = fontFamily;
    return true;
}

const QString& Options::fontFamily() const
{
    return _fontFamily;
}

bool Options::setFontSize(int fontSize)
{
    if (_fontSize == fontSize) return false;
    _fontSize = fontSize;
    return true;
}

int Options::fontSize() const
{
    return _fontSize;
}

bool Options::setCodeFolding(const QString& codeFolding)
{
    if (_codeFolding == codeFolding) return false;
    _codeFolding = codeFolding;
    return true;
}

const QString& Options::codeFolding() const
{
    return _codeFolding;
}

bool Options::setKeyBinding(const QString& keyBinding)
{
    if (_keyBinding == keyBinding) return false;
    _keyBinding = keyBinding;
    return true;
}

const QString& Options::keyBinding() const
{
    return _keyBinding;
}

bool Options::setSoftWrap(const QString& softWrap)
{
    if (_softWrap == softWrap) return false;
    _softWrap = softWrap;
    return true;
}

const QString& Options::softWrap() const
{
    return _softWrap;
}

bool Options::setShowInvisibles(bool showInvisibles)
{
    if (_showInvisibles == showInvisibles) return false;
    _showInvisibles = showInvisibles;
    return true;
}

bool Options::showInvisibles() const
{
    return _showInvisibles;
}

bool Options::setShowIndentRules(bool showIndentRules)
{
    if (_showIndentRules == showIndentRules) return false;
    _showIndentRules = showIndentRules;
    return true;
}

bool Options::showIndentRules() const
{
    return _showIndentRules;
}

bool Options::setShowGutter(bool showGutter)
{
    if (_showGutter == showGutter) return false;
    _showGutter = showGutter;
    return true;
}

bool Options::showGutter() const
{
    return _showGutter;
}

bool Options::setShowPrintMargin(bool showPrintMargin)
{
    if (_showPrintMargin == showPrintMargin) return false;
    _showPrintMargin = showPrintMargin;
    return true;
}

bool Options::showPrintMargin() const
{
    return _showPrintMargin;
}

bool Options::setHighlightSelectedWord(bool highlightSelectedWord)
{
    if (_highlightSelectedWord == highlightSelectedWord) return false;
    _highlightSelectedWord = highlightSelectedWord;
    return true;
}

bool Options::highlightSelectedWord() const
{
    return _highlightSelectedWord;
}

bool Options::setUseSoftTab(bool useSoftTab)
{
    if (_useSoftTab == useSoftTab) return false;
    _useSoftTab = useSoftTab;
    return true;
}

bool Options::useSoftTab() const
{
    return _useSoftTab;
}
