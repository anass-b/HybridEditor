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
