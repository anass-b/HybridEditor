#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QTabWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include <Editor.h>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

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

private:
    QAction* _newAction;
    QAction* _openFileAction;
    QAction* _openDirectoryAction;
    QAction* _saveAction;
    QAction* _saveAsAction;
    QAction* _quitAction;
    QAction* _changeFontAction;
    QAction* _aboutAction;
    QAction* _copyAction;
    QAction* _pasteAction;
    QAction* _cutAction;
    QAction* _selectAllAction;
    QAction* _undoAction;
    QAction* _redoAction;
    QTabWidget* _tabWidget;
    QDockWidget* _fileExplorerDockWidget;
    QFileSystemModel* _fileSystemModel;
    QTreeView* _treeView;
    QString _openedFolderPath;

public slots:
    void newFile();
    void about();
    void changeFont();
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
};

//QMap<QString, QList<QString>> MainWindow::_extLangMap;

#endif
