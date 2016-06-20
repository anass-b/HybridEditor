#include "MainWindow.h"
#include <iostream>
#include <QStatusBar>
#include <QMenuBar>
#include <QToolBar>
#include <QFileDialog>

MainWindow::MainWindow():
    _newAction(nullptr),
    _openFileAction(nullptr),
    _openDirectoryAction(nullptr),
    _saveAction(nullptr),
    _saveAsAction(nullptr),
    _quitAction(nullptr),
    _copyAction(nullptr),
    _pasteAction(nullptr),
    _cutAction(nullptr),
    _selectAllAction(nullptr),
    _undoAction(nullptr),
    _redoAction(nullptr),
    _optionsAction(nullptr),
    _tabWidget(nullptr),
    _fileExplorerDockWidget(nullptr),
    _fileSystemModel(nullptr),
    _treeView(nullptr),
    _optionsDialog(nullptr)
{
    setWindowTitle("HybridEditor");
    createUI();
    Editor::languages().load();
}

void MainWindow::createUI()
{
    createMenu();
    createTabUi();

    // Statusbar
    QStatusBar* statusbar = statusBar();
    statusbar->showMessage(tr("Ready"));
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
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

    _newAction = fileMenu->addAction(tr("&New"));
    _newAction->setShortcut(QKeySequence("Ctrl+N"));
    _newAction->setStatusTip("Create new file");

    _openFileAction = fileMenu->addAction(tr("&Open file"));
    _openFileAction->setShortcut(QKeySequence("Ctrl+O"));
    _openFileAction->setStatusTip(tr("Open file"));

    _openDirectoryAction = fileMenu->addAction(tr("&Open directory"));
    _openDirectoryAction->setShortcut(QKeySequence("Ctrl+Alt+O"));
    _openDirectoryAction->setStatusTip(tr("Open directory"));

    _saveAction = fileMenu->addAction(tr("&Save"));
    _saveAction->setShortcut(QKeySequence("Ctrl+S"));
    _saveAction->setStatusTip(tr("Save file"));

    _saveAsAction = fileMenu->addAction(tr("&Save As..."));
    _saveAsAction->setShortcut(QKeySequence("Ctrl+Alt+S"));
    _saveAsAction->setStatusTip(tr("Save file as..."));

    fileMenu->addSeparator();

    _quitAction = fileMenu->addAction(tr("&Quit"));
    _quitAction->setShortcut(QKeySequence("Alt+F4"));
    _quitAction->setStatusTip(tr("Quit application"));

    // Edit
    QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));

    _undoAction = editMenu->addAction(tr("&Undo"));
    _undoAction->setShortcut(QKeySequence("Ctrl+Z"));

    _redoAction = editMenu->addAction(tr("&Redo"));
    _redoAction->setShortcut(QKeySequence("Ctrl+Y"));

    editMenu->addSeparator();

    _copyAction = editMenu->addAction(tr("&Copy"));
    _copyAction->setShortcut(QKeySequence("Ctrl+C"));

    _cutAction = editMenu->addAction(tr("&Cut"));
    _cutAction->setShortcut(QKeySequence("Ctrl+X"));

    _pasteAction = editMenu->addAction(tr("&Paste"));
    _pasteAction->setShortcut(QKeySequence("Ctrl+V"));

    _selectAllAction = editMenu->addAction(tr("&Select All"));
    _selectAllAction->setShortcut(QKeySequence("Ctrl+A"));

    editMenu->addSeparator();

    _optionsAction = editMenu->addAction(tr("&Options"));

    // Connect actions
    connect(_quitAction, SIGNAL(triggered()), this, SLOT(quit()));
    connect(_newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(_openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(_openDirectoryAction, SIGNAL(triggered()), this, SLOT(openDirectory()));
    connect(_saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(_saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(_undoAction, SIGNAL(triggered()), this, SLOT(undo()));
    connect(_redoAction, SIGNAL(triggered()), this, SLOT(redo()));
    connect(_copyAction, SIGNAL(triggered()), this, SLOT(copy()));
    connect(_pasteAction, SIGNAL(triggered()), this, SLOT(paste()));
    connect(_cutAction, SIGNAL(triggered()), this, SLOT(cut()));
    connect(_selectAllAction, SIGNAL(triggered()), this, SLOT(selectAll()));
    connect(_optionsAction, SIGNAL(triggered()), this, SLOT(openOptions()));
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

    createTab();
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
        Editor* editor = new Editor(_options);
        QString tabTitle = MainWindow::newTabName();
        editor->setGeneratedFilename(tabTitle);
        int index = _tabWidget->addTab(editor, tabTitle);
        _tabWidget->setCurrentIndex(index);
        editor->show();
    }
    else {
        QFileInfo fileInfo(path);
        if (!fileInfo.isFile()) return nullptr;

        // If the file is already open, we activate its tab
        for (int i = 0; i < _tabWidget->count(); i++) {
            Editor* e = (Editor*)_tabWidget->widget(i);
            if (e && e->filePath() == path) {
                _tabWidget->setCurrentIndex(i);
                return e;
            }
        }

        Editor* editor = new Editor(_options);
        QString tabTitle = fileInfo.fileName();
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

void MainWindow::openOptions()
{
    if (_optionsDialog == nullptr) {
        _optionsDialog = new OptionsDialog(_options, this);
        _optionsDialog->setDelegate(this);
#ifdef __APPLE__
        _optionsDialog->setWindowTitle(tr("Preferences"));
#else
        _optionsDialog->setWindowTitle(tr("Options"));
#endif
    }
    _optionsDialog->exec();
}

// Options Dialog Delegate

void MainWindow::fontFamilySettingsChanged(const QString& fontFamily)
{
    _options.setFontFamily(fontFamily);
    for (int i = 0; i < _tabWidget->count(); i++) {
        Editor* e = (Editor*)_tabWidget->widget(i);
        e->setFontFamily(fontFamily);
    }
}

void MainWindow::fontSizeSettingsChanged(int size)
{
    _options.setFontSize(size);
    for (int i = 0; i < _tabWidget->count(); i++) {
        Editor* e = (Editor*)_tabWidget->widget(i);
        e->setFontSize(size);
    }
}

void MainWindow::themeSettingsChanged(const QString& theme)
{
    _options.setTheme(theme);
    for (int i = 0; i < _tabWidget->count(); i++) {
        Editor* e = (Editor*)_tabWidget->widget(i);
        e->setTheme(theme);
    }
}

void MainWindow::codeFoldingSettingsChanged(const QString& codeFolding)
{
    _options.setCodeFolding(codeFolding);
    for (int i = 0; i < _tabWidget->count(); i++) {
        Editor* e = (Editor*)_tabWidget->widget(i);
        e->setCodeFolding(codeFolding);
    }
}

void MainWindow::keyBindingSettingsChanged(const QString& keyBinding)
{
    _options.setKeyBinding(keyBinding);
    for (int i = 0; i < _tabWidget->count(); i++) {
        Editor* e = (Editor*)_tabWidget->widget(i);
        e->setKeyBinding(keyBinding);
    }
}

void MainWindow::softWrapSettingsChanged(const QString& softWrap)
{
    _options.setSoftWrap(softWrap);
    for (int i = 0; i < _tabWidget->count(); i++) {
        Editor* e = (Editor*)_tabWidget->widget(i);
        e->setSoftWrap(softWrap);
    }
}

void MainWindow::showInvisiblesSettingsChanged(bool showInvisibles)
{
    _options.setShowInvisibles(showInvisibles);
    for (int i = 0; i < _tabWidget->count(); i++) {
        Editor* e = (Editor*)_tabWidget->widget(i);
        e->setShowInvisibles(showInvisibles);
    }
}

void MainWindow::showIndentRulesSettingsChanged(bool showIndentRules)
{
    _options.setShowIndentRules(showIndentRules);
    for (int i = 0; i < _tabWidget->count(); i++) {
        Editor* e = (Editor*)_tabWidget->widget(i);
        e->setShowIndentRules(showIndentRules);
    }
}

void MainWindow::showGutterSettingsChanged(bool showGutter)
{
    _options.setShowGutter(showGutter);
    for (int i = 0; i < _tabWidget->count(); i++) {
        Editor* e = (Editor*)_tabWidget->widget(i);
        e->setShowGutter(showGutter);
    }
}

void MainWindow::showPrintMarginSettingsChanged(bool showPrintMargin)
{
    _options.setShowPrintMargin(showPrintMargin);
    for (int i = 0; i < _tabWidget->count(); i++) {
        Editor* e = (Editor*)_tabWidget->widget(i);
        e->setShowPrintMargin(showPrintMargin);
    }
}

void MainWindow::useSoftTabSettingsChanged(bool useSoftTab)
{
    _options.setUseSoftTab(useSoftTab);
    for (int i = 0; i < _tabWidget->count(); i++) {
        Editor* e = (Editor*)_tabWidget->widget(i);
        e->setUseSoftTab(useSoftTab);
    }
}

void MainWindow::highlightSelectedWordSettingsChanged(bool highlightSelectedWord)
{
    _options.setHighlightSelectedWord(highlightSelectedWord);
    for (int i = 0; i < _tabWidget->count(); i++) {
        Editor* e = (Editor*)_tabWidget->widget(i);
        e->setHighlightSelectedWord(highlightSelectedWord);
    }
}
