#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QDockWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include "OptionsDialog.h"
#include "Editor.h"
#include "Options.h"

class MainWindow : public QMainWindow, public OptionsDialogDelegate {
    Q_OBJECT

public:
    explicit MainWindow();

private:
    void createUI();
    void createMenu();
    void createToolbar();
    void createTabUi();
    void openFileExplorer(const QString& path);
    Editor* activeTab();
    Editor* createTab(const QString& name = "");
    static QString newTabName();
    void setOpenedFolderPath(const QString& path);
    const QString& openedFolderPath() const;

    virtual void fontFamilySettingsChanged(const QString& fontFamily);
    virtual void fontSizeSettingsChanged(int size);
    virtual void themeSettingsChanged(const QString& theme);
    virtual void codeFoldingSettingsChanged(const QString& codeFolding);
    virtual void keyBindingSettingsChanged(const QString& keyBinding);
    virtual void softWrapSettingsChanged(const QString& softWrap);
    virtual void showInvisiblesSettingsChanged(bool showInvisibles);
    virtual void showIndentRulesSettingsChanged(bool showIndentRules);
    virtual void showGutterSettingsChanged(bool showGutter);
    virtual void showPrintMarginSettingsChanged(bool showPrintMargin);
    virtual void useSoftTabSettingsChanged(bool useSoftTab);
    virtual void highlightSelectedWordSettingsChanged(bool highlightSelectedWord);

private:
    QAction* _newAction;
    QAction* _openFileAction;
    QAction* _openDirectoryAction;
    QAction* _saveAction;
    QAction* _saveAsAction;
    QAction* _quitAction;
    QAction* _copyAction;
    QAction* _pasteAction;
    QAction* _cutAction;
    QAction* _selectAllAction;
    QAction* _undoAction;
    QAction* _redoAction;
    QAction* _optionsAction;
    QString _openedFolderPath;
    QTabWidget* _tabWidget;
    QDockWidget* _fileExplorerDockWidget;
    QFileSystemModel* _fileSystemModel;
    QTreeView* _treeView;
    OptionsDialog *_optionsDialog;
    Options _options;

public slots:
    void newFile();
    void undo();
    void redo();
    void selectAll();
    void copy();
    void paste();
    void cut();
    void openFile();
    void openFile(const QModelIndex &index);
    void openDirectory();
    void save();
    void saveAs();
    void closeTab(int);
    void openOptions();
};

#endif
