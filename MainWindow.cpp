#include "MainWindow.h"

MainWindow::MainWindow()
{
    setWindowTitle("HybridEditor");
    createUI();
}

void MainWindow::createUI()
{
    createMenu();
    createToolbar();
    createTabUi();

    // Statusbar
    QStatusBar* statusbar = statusBar();
    statusbar->showMessage("Ready");
}

void MainWindow::openFileExplorer(const QString& path)
{
    setOpenedFolderPath(path);

    if (_fileSystemModel == nullptr || _treeView == nullptr) {
        _fileExplorerDockWidget = new QDockWidget(QFileInfo(path).fileName(), this);
        addDockWidget(Qt::LeftDockWidgetArea, _fileExplorerDockWidget);

        _fileSystemModel = new QFileSystemModel;
        _fileSystemModel->setRootPath(path);

        _treeView = new QTreeView(_fileExplorerDockWidget);
        _treeView->setModel(_fileSystemModel);
        _treeView->setRootIndex(_fileSystemModel->index(path));
        _treeView->setColumnHidden(1, true);
        _treeView->setColumnHidden(2, true);
        _treeView->setColumnHidden(3, true);
        _treeView->setHeaderHidden(true);
        connect(_treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(openFile(QModelIndex)));

        _fileExplorerDockWidget->setWidget(_treeView);
    }
    else {
        _fileExplorerDockWidget->setWindowTitle(QFileInfo(path).fileName());
        _fileSystemModel->setRootPath(path);
        _treeView->setRootIndex(_fileSystemModel->index(path));
    }
}

void MainWindow::createMenu()
{
    // File
    QMenu* fileMenu = menuBar()->addMenu("&File");

    _newAction = fileMenu->addAction("&New");
    _newAction->setShortcut(QKeySequence("Ctrl+N"));
    _newAction->setIcon(QIcon(":/res/document-new.png"));
    _newAction->setStatusTip("Create new file");

    _openFileAction = fileMenu->addAction("&Open file");
    _openFileAction->setShortcut(QKeySequence("Ctrl+O"));
    _openFileAction->setIcon(QIcon(":/res/document-open.png"));
    _openFileAction->setStatusTip("Open file");

    _openDirectoryAction = fileMenu->addAction("&Open directory");
    _openDirectoryAction->setShortcut(QKeySequence("Ctrl+O"));
    _openDirectoryAction->setIcon(QIcon(":/res/folder.png"));
    _openDirectoryAction->setStatusTip("Open directory");

    _saveAction = fileMenu->addAction("&Save");
    _saveAction->setShortcut(QKeySequence("Ctrl+S"));
    _saveAction->setIcon(QIcon(":/res/document-save.png"));
    _saveAction->setStatusTip("Save file");

    _saveAsAction = fileMenu->addAction("&Save As...");
    _saveAsAction->setShortcut(QKeySequence("Ctrl+Alt+S"));
    _saveAsAction->setIcon(QIcon(":/res/document-save-as.png"));
    _saveAsAction->setStatusTip("Save file as...");

    fileMenu->addSeparator();

    _quitAction = fileMenu->addAction("&Quit");
    _quitAction->setShortcut(QKeySequence("Alt+F4"));
    _quitAction->setIcon(QIcon(":/res/system-log-out.png"));
    _quitAction->setStatusTip("Quit application");

    // Edit
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

    // Format
    QMenu* formatMenu = menuBar()->addMenu("&Format");

    _changeFontAction = formatMenu->addAction("&Change font");
    _changeFontAction->setIcon(QIcon(":/res/preferences-desktop-font.png"));

    // About
    QMenu* helpMenu = menuBar()->addMenu("&About");

    _aboutAction = helpMenu->addAction("&About");
    _aboutAction->setIcon(QIcon(":/res/help-browser.png"));

    // Connect actions
    connect(_quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(_newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(_openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(_openDirectoryAction, SIGNAL(triggered()), this, SLOT(openDirectory()));
    connect(_saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(_saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(_aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    connect(_undoAction, SIGNAL(triggered()), this, SLOT(undo()));
    connect(_redoAction, SIGNAL(triggered()), this, SLOT(redo()));
    connect(_copyAction, SIGNAL(triggered()), this, SLOT(copy()));
    connect(_pasteAction, SIGNAL(triggered()), this, SLOT(paste()));
    connect(_cutAction, SIGNAL(triggered()), this, SLOT(cut()));
    connect(_selectAllAction, SIGNAL(triggered()), this, SLOT(selectAll()));
    connect(_changeFontAction, SIGNAL(triggered()), this, SLOT(changeFont()));
}

void MainWindow::createToolbar()
{
    // File
    QToolBar* fileToolbar = addToolBar("File");
    fileToolbar->addAction(_newAction);
    fileToolbar->addAction(_openFileAction);
    fileToolbar->addAction(_openDirectoryAction);
    fileToolbar->addAction(_saveAction);
    fileToolbar->addAction(_saveAsAction);

    // Edit
    QToolBar* editToolbar = addToolBar("Edit");
    editToolbar->addAction(_undoAction);
    editToolbar->addAction(_redoAction);
    editToolbar->addAction(_copyAction);
    editToolbar->addAction(_cutAction);
    editToolbar->addAction(_pasteAction);
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

QString MainWindow::newTabName()
{
    static int sequenceNumber = 1;
    return tr("Untitled%1.txt").arg(sequenceNumber++);
}

Editor* MainWindow::createTab(const QString& path)
{
    if (path.isEmpty()) {
        // New empty tab
        Editor* editor = new Editor;
        QString tabTitle = MainWindow::newTabName();
        editor->setGeneratedFilename(tabTitle);
        int index = _tabWidget->addTab(editor, tabTitle);
        _tabWidget->setCurrentIndex(index);
        editor->show();
    }
    else {
        // If the file is already open, we activate its tab
        for (int i = 0; i < _tabWidget->count(); i++) {
            Editor* e = (Editor*)_tabWidget->widget(i);
            if (e && e->filePath() == path) {
                _tabWidget->setCurrentIndex(i);
                return e;
            }
        }

        Editor* editor = new Editor;
        QString tabTitle = QFileInfo(path).fileName();
        editor->setGeneratedFilename(tabTitle);
        if (editor->loadFile(path)) {
            int index = _tabWidget->addTab(editor, tabTitle);
            _tabWidget->setCurrentIndex(index);
            editor->show();
            statusBar()->showMessage(tr("File loaded"), 2000);
            return editor;
        }
        else {
            delete editor;
            return nullptr;
        }
    }

    return nullptr;
}

Editor* MainWindow::activeTab()
{
    return (Editor*)_tabWidget->currentWidget();
}

void MainWindow::setOpenedFolderPath(const QString& path)
{
    if (path != _openedFolderPath) {
        _openedFolderPath = path;
    }
}

const QString& MainWindow::openedFolderPath() const
{
    return _openedFolderPath;
}

// --- Slots ---

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

void MainWindow::newFile()
{
    createTab();
}

void MainWindow::openFile()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setDirectory(QDir::homePath());
    dialog.setWindowTitle(tr("Open File"));
    if (dialog.exec() && dialog.selectedFiles().count() > 0) {
        QString path = dialog.selectedFiles().at(0);
        if (QFileInfo(path).isFile()) {
            createTab(path);
        }
    }
}

void MainWindow::openFile(const QModelIndex &index)
{
    QString path = _fileSystemModel->filePath(index);
    if (QFileInfo(path).isFile()) {
        createTab(path);
    }
}

void MainWindow::openDirectory()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QDir::homePath());
    dialog.setWindowTitle(tr("Open File"));
    if (dialog.exec() && dialog.selectedFiles().count() > 0) {
        QString path = dialog.selectedFiles().at(0);
        if (QFileInfo(path).isDir()) {
            openFileExplorer(path);
        }
    }
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
        QFont font = QFontDialog::getFont(&ok, activeTab()->font(), this, "Change font");
        if (ok) {
            activeTab()->setFont(font);
        }
    }
}
