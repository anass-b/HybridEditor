#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QProcess>
#include <QTabWidget>
#include <Editor.h>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

private:
    void createTabUi();
    Editor* activeTab();
    Editor* createTab(const QString& name = "");
    void createUI();
    QString newTabName();

private:
    QAction* _copyAction;
    QAction* _pasteAction;
    QAction* _cutAction;
    QAction* _selectAllAction;
    QAction* _undoAction;
    QAction* _redoAction;
    QTabWidget* _tabWidget;

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
    void open();
    void save();
    void saveAs();
    void closeTab(int);
};

#endif
