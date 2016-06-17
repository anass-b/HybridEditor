#include "MainWindow.h"

MainWindow::MainWindow()
{
    setWindowTitle("HybridEditor");
    createUI();
}

void MainWindow::createUI()
{
    // File menu
    QMenu* fileMenu = menuBar()->addMenu("&File");

    QAction* newAction = fileMenu->addAction("&New");
    newAction->setShortcut(QKeySequence("Ctrl+N"));
    newAction->setIcon(QIcon(":/res/document-new.png"));
    newAction->setStatusTip("Create new file");

    QAction* openAction = fileMenu->addAction("&Open");
    openAction->setShortcut(QKeySequence("Ctrl+O"));
    openAction->setIcon(QIcon(":/res/document-open.png"));
    openAction->setStatusTip("Open file");

    QAction* saveAction = fileMenu->addAction("&Save");
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    saveAction->setIcon(QIcon(":/res/document-save.png"));
    saveAction->setStatusTip("Save file");

    QAction* saveAsAction = fileMenu->addAction("&Save As...");
    saveAsAction->setShortcut(QKeySequence("Ctrl+Alt+S"));
    saveAsAction->setIcon(QIcon(":/res/document-save-as.png"));
    saveAsAction->setStatusTip("Save file as...");

    fileMenu->addSeparator();

    QAction* quitAction = fileMenu->addAction("&Quit");
    quitAction->setShortcut(QKeySequence("Alt+F4"));
    quitAction->setIcon(QIcon(":/res/system-log-out.png"));
    quitAction->setStatusTip("Quit application");

    // Edit menu
    QMenu* editMenu = menuBar()->addMenu("&Edit");

    _undoAction = editMenu->addAction("&Undo");
    _undoAction->setShortcut(QKeySequence("Ctrl+Z"));
    _undoAction->setIcon(QIcon(":/res/edit-undo.png"));

    _redoAction = editMenu->addAction("&Redo");
    _redoAction->setShortcut(QKeySequence("Ctrl+Y"));
    _redoAction->setIcon(QIcon(":/res/edit-redo.png"));

    editMenu->addSeparator();

    _copyAction = editMenu->addAction("&Copy");
    _copyAction->setShortcut(QKeySequence("Ctrl+C"));
    _copyAction->setIcon(QIcon(":/res/edit-copy.png"));

    _cutAction = editMenu->addAction("&Cut");
    _cutAction->setShortcut(QKeySequence("Ctrl+X"));
    _cutAction->setIcon(QIcon(":/res/edit-cut.png"));

    _pasteAction = editMenu->addAction("&Paste");
    _pasteAction->setShortcut(QKeySequence("Ctrl+V"));
    _pasteAction->setIcon(QIcon(":/res/edit-paste.png"));

    _selectAllAction = editMenu->addAction("&Select All");
    _selectAllAction->setShortcut(QKeySequence("Ctrl+A"));
    _selectAllAction->setIcon(QIcon(":/res/edit-select-all.png"));

    // Format menu
    QMenu* formatMenu = menuBar()->addMenu("&Format");

    QAction* changeFontAction = formatMenu->addAction("&Change font");
    changeFontAction->setIcon(QIcon(":/res/preferences-desktop-font.png"));

    // About menu
    QMenu* helpMenu = menuBar()->addMenu("&About");

    QAction* aboutAction = helpMenu->addAction("&About");
    aboutAction->setIcon(QIcon(":/res/help-browser.png"));

    // File toolbar
    QToolBar* fileToolbar = addToolBar("File");
    fileToolbar->addAction(newAction);
    fileToolbar->addAction(openAction);
    fileToolbar->addAction(saveAction);
    fileToolbar->addAction(saveAsAction);

    // Edit toolbar
    QToolBar* editToolbar = addToolBar("Edit");
    editToolbar->addAction(_undoAction);
    editToolbar->addAction(_redoAction);
    editToolbar->addAction(_copyAction);
    editToolbar->addAction(_cutAction);
    editToolbar->addAction(_pasteAction);

    // Statusbar
    QStatusBar* statusbar = statusBar();
    statusbar->showMessage("Ready");

    // Central Widget
    createTabUi();

    // Actions
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    connect(_undoAction, SIGNAL(triggered()), this, SLOT(undo()));
    connect(_redoAction, SIGNAL(triggered()), this, SLOT(redo()));
    connect(_copyAction, SIGNAL(triggered()), this, SLOT(copy()));
    connect(_pasteAction, SIGNAL(triggered()), this, SLOT(paste()));
    connect(_cutAction, SIGNAL(triggered()), this, SLOT(cut()));
    connect(_selectAllAction, SIGNAL(triggered()), this, SLOT(selectAll()));
    connect(changeFontAction, SIGNAL(triggered()), this, SLOT(changeFont()));
}

void MainWindow::createTabUi()
{
    _tabWidget = new QTabWidget;
    _tabWidget->setMovable(true);
    _tabWidget->setDocumentMode(true);
    _tabWidget->setTabsClosable(true);

    connect(_tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));

    setCentralWidget(_tabWidget);
}

void MainWindow::closeTab(int index)
{
    _tabWidget->removeTab(index);
}

void MainWindow::cut()
{
    Editor* tab = activeTab();
    if (tab) {
        tab->cut();
    }
}

void MainWindow::copy()
{
    Editor* tab = activeTab();
    if (tab) {
        tab->copy();
    }
}

void MainWindow::paste()
{
    Editor* tab = activeTab();
    if (tab) {
        tab->paste();
    }
}

void MainWindow::selectAll()
{
    Editor* tab = activeTab();
    if (tab) {
        tab->selectAll();
    }
}

void MainWindow::undo()
{
    Editor* tab = activeTab();
    if (tab) {
        tab->undo();
    }
}

void MainWindow::redo()
{
    Editor* tab = activeTab();
    if (tab) {
        tab->redo();
    }
}

QString MainWindow::newTabName()
{
    static int sequenceNumber = 1;
    return tr("Untitled%1.txt").arg(sequenceNumber++);
}

void MainWindow::newFile()
{
    createTab();
}

Editor* MainWindow::createTab(const QString& name)
{
    QString tabTitle = name.length() == 0 ? newTabName() : name;

    Editor* child = new Editor;
    child->setGeneratedFilename(tabTitle);

    int index = _tabWidget->addTab(child, tabTitle);
    _tabWidget->setCurrentIndex(index);

    return child;
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath());
    if (!fileName.isEmpty()) {
        Editor* child = createTab(QFileInfo(fileName).fileName());
        if (child->loadFile(fileName)) {
            statusBar()->showMessage(tr("File loaded"), 2000);
            child->show();
        }
        else {
            child->close();
        }
    }
}

Editor* MainWindow::activeTab()
{
    return (Editor*)_tabWidget->currentWidget();
}

void MainWindow::save()
{
    if (activeTab() && activeTab()->save()) {
        statusBar()->showMessage(tr("File saved"), 2000);
    }
}

void MainWindow::saveAs()
{
    if (activeTab() && activeTab()->saveAs())
        statusBar()->showMessage(tr("File saved"), 2000);
}

void MainWindow::about()
{
    QMessageBox::about(this, "About", "HybridEditor v0.0.1");
}

void MainWindow::changeFont()
{
    bool ok = false;
    if (activeTab()) {
        QFont cEditFont = QFontDialog::getFont(&ok, activeTab()->font(), this, "Change font");
        if (ok) {
            activeTab()->setFont(cEditFont);
        }
    }
}
