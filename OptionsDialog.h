#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QFontComboBox>
#include <QSpinBox>
#include "Options.h"

class OptionsDialogDelegate
{
public:
    virtual void fontFamilySettingsChanged(const QString& fontFamily) = 0;
    virtual void fontSizeSettingsChanged(int size) = 0;
    virtual void themeSettingsChanged(const QString& theme) = 0;
    virtual void codeFoldingSettingsChanged(const QString& codeFolding) = 0;
    virtual void keyBindingSettingsChanged(const QString& keyBinding) = 0;
    virtual void softWrapSettingsChanged(const QString& softWrap) = 0;
    virtual void showInvisiblesSettingsChanged(bool showInvisibles) = 0;
    virtual void showIndentRulesSettingsChanged(bool showIndentRules) = 0;
    virtual void showGutterSettingsChanged(bool showGutter) = 0;
    virtual void showPrintMarginSettingsChanged(bool showPrintMargin) = 0;
    virtual void useSoftTabSettingsChanged(bool useSoftTab) = 0;
    virtual void highlightSelectedWordSettingsChanged(bool highlightSelectedWord) = 0;
};

class OptionsDialog : public QDialog
{
public:
    explicit OptionsDialog(const Options& options, QWidget* parent = nullptr);
    void setDelegate(OptionsDialogDelegate* delegate);

private:
    OptionsDialogDelegate* _delegate;

};

#endif // OPTIONSDIALOG_H
