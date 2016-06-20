#include "OptionsDialog.h"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>

OptionsDialog::OptionsDialog(const Options& options, QWidget* parent) :
    QDialog(parent),
    _delegate(nullptr)
{
    QFormLayout* layout = new QFormLayout;
    layout->setSizeConstraint(QLayout::SetFixedSize);

    QFontComboBox* fontFamily = new QFontComboBox(this);
    fontFamily->setCurrentText(options.fontFamily());
    connect(fontFamily, static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged), [=](const QString& text) {
       if (_delegate) {
           _delegate->fontFamilySettingsChanged(text);
       }
    });

    QSpinBox* fontSize = new QSpinBox(this);
    fontSize->setValue(options.fontSize());
    fontSize->setMinimum(8);
    fontSize->setMaximum(72);
    connect(fontSize, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](int value) {
       if (_delegate) {
           _delegate->fontSizeSettingsChanged(value);
       }
    });

    QComboBox* theme = new QComboBox(this);
    theme->addItem("Ambiance", "ambiance");
    theme->addItem("Monokai", "monokai");
    theme->addItem("Tomorrow Night", "tomorrow_night");
    theme->addItem("Twilight", "twilight");
    theme->setCurrentIndex(3);
    connect(theme, static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged), [=] {
        if (_delegate) {
            _delegate->themeSettingsChanged(theme->currentData().toString());
        }
    });

    QComboBox* codeFolding = new QComboBox(this);
    codeFolding->addItem(tr("Manual"), "manual");
    codeFolding->addItem(tr("Mark begin"), "markbegin");
    codeFolding->addItem(tr("Mark begin and end"), "markbeginend");
    codeFolding->setCurrentIndex(1);
    connect(codeFolding, static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged), [=] {
        if (_delegate) {
            _delegate->codeFoldingSettingsChanged(codeFolding->currentData().toString());
        }
    });

    QComboBox* keyBinding = new QComboBox(this);
    keyBinding->addItem("Ace", "ace");
    keyBinding->addItem("Vim", "vim");
    keyBinding->addItem("Emacs", "emacs");
    keyBinding->addItem("Custom", "custom");
    keyBinding->setCurrentIndex(0);
    connect(keyBinding, static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged), [=] {
        if (_delegate) {
            _delegate->keyBindingSettingsChanged(keyBinding->currentData().toString());
        }
    });

    QComboBox* softWrap = new QComboBox(this);
    softWrap->addItem(tr("Off"), "off");
    softWrap->addItem(tr("40 Chars"), "40");
    softWrap->addItem(tr("80 Chars"), "80");
    softWrap->addItem(tr("Free"), "free");
    softWrap->setCurrentIndex(0);
    connect(softWrap, static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged), [=] {
        if (_delegate) {
            _delegate->softWrapSettingsChanged(softWrap->currentData().toString());
        }
    });

    QCheckBox* showInvisibles = new QCheckBox(this);
    showInvisibles->setChecked(options.showInvisibles());
    connect(showInvisibles, static_cast<void(QCheckBox::*)(int)>(&QCheckBox::stateChanged), [=](int state) {
       if (_delegate) {
           _delegate->showInvisiblesSettingsChanged((bool)state);
       }
    });

    QCheckBox* showIndentGuides = new QCheckBox(this);
    showIndentGuides->setChecked(options.showIndentRules());
    connect(showIndentGuides, static_cast<void(QCheckBox::*)(int)>(&QCheckBox::stateChanged), [=](int state) {
       if (_delegate) {
           _delegate->showIndentRulesSettingsChanged((bool)state);
       }
    });

    QCheckBox* showGutter = new QCheckBox(this);
    showGutter->setChecked(options.showGutter());
    connect(showGutter, static_cast<void(QCheckBox::*)(int)>(&QCheckBox::stateChanged), [=](int state) {
       if (_delegate) {
           _delegate->showGutterSettingsChanged((bool)state);
       }
    });

    QCheckBox* showPrintMargin = new QCheckBox(this);
    showPrintMargin->setChecked(options.showPrintMargin());
    connect(showPrintMargin, static_cast<void(QCheckBox::*)(int)>(&QCheckBox::stateChanged), [=](int state) {
       if (_delegate) {
           _delegate->showPrintMarginSettingsChanged((bool)state);
       }
    });

    QCheckBox* useSoftTab = new QCheckBox(this);
    useSoftTab->setChecked(options.useSoftTab());
    connect(useSoftTab, static_cast<void(QCheckBox::*)(int)>(&QCheckBox::stateChanged), [=](int state) {
       if (_delegate) {
           _delegate->useSoftTabSettingsChanged((bool)state);
       }
    });

    QCheckBox* highlightSelectedWord = new QCheckBox(this);
    highlightSelectedWord->setChecked(options.highlightSelectedWord());
    connect(highlightSelectedWord, static_cast<void(QCheckBox::*)(int)>(&QCheckBox::stateChanged), [=](int state) {
       if (_delegate) {
           _delegate->highlightSelectedWordSettingsChanged((bool)state);
       }
    });

    layout->addRow(tr("&Font family:"), fontFamily);
    layout->addRow(tr("&Font size:"), fontSize);
    layout->addRow(tr("&Theme:"), theme);
    layout->addRow(tr("&Code Folding:"), codeFolding);
    layout->addRow(tr("&Key Binding:"), keyBinding);
    layout->addRow(tr("&Soft Wrap:"), softWrap);
    layout->addRow(tr("&Show Invisibles:"), showInvisibles);
    layout->addRow(tr("&Show Indent Guides:"), showIndentGuides);
    layout->addRow(tr("&Show Gutter:"), showGutter);
    layout->addRow(tr("&Show Print Margin:"), showPrintMargin);
    layout->addRow(tr("&Use Soft Tab:"), useSoftTab);
    layout->addRow(tr("&Highlight selected word:"), highlightSelectedWord);

    QDialogButtonBox* dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::RestoreDefaults);

    layout->addRow(dialogButtonBox);

    setLayout(layout);
}

void OptionsDialog::setDelegate(OptionsDialogDelegate* delegate)
{
    _delegate = delegate;
}
