#include "Editor.h"
#include "MainWindow.h"
#include <QWebChannel>

Editor::Editor()
{
    QWebEnginePage* page = new QWebEnginePage(this);
    setPage(page);

    QWebChannel* channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("content"), &_content);
    page->setWebChannel(channel);

    page->load(QUrl("qrc:/ace/editor.html"));
}

const QString& Editor::filePath() const
{
    return _filePath;
}

void Editor::setGeneratedFilename(const QString& generatedFilename)
{
    if (_generatedFilename == generatedFilename)
        return;
    _generatedFilename = generatedFilename;
}

bool Editor::loadFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,
            tr("IDE4Pascal"),
            tr("Cannot read file %1:\n%2.").arg(filePath).arg(file.errorString()));
        return false;
    }

    _filePath = filePath;

    QTextStream in(&file);
    _content.setText(in.readAll());
    _content.setLang(MainWindow::lang(MainWindow::extLangMap(), QFileInfo(filePath).suffix()));

    return true;
}

bool Editor::save()
{
    if (_filePath.length() == 0) {
        return saveAs();
    }
    else {
        return saveFile(_filePath);
    }
    return false;
}

bool Editor::saveAs()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save As..."), _generatedFilename);

    if (filePath.isEmpty())
        return false;

    return saveFile(filePath);
}

bool Editor::saveFile(const QString& filePath)
{
    QString text = _content.text();

    QFile file(filePath);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,
            tr("IDE4Pascal"),
            tr("Cannot write file %1:\n%2.").arg(filePath).arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    out << text;
    out.flush();

    _filePath = filePath;

    return true;
}

void Editor::copy()
{
    this->triggerPageAction(QWebEnginePage::Copy);
}

void Editor::paste()
{
    this->triggerPageAction(QWebEnginePage::Paste);
}

void Editor::cut()
{
    this->triggerPageAction(QWebEnginePage::Cut);
}

void Editor::selectAll()
{
    this->triggerPageAction(QWebEnginePage::SelectAll);
}

void Editor::undo()
{
    this->triggerPageAction(QWebEnginePage::Undo);
}

void Editor::redo()
{
    this->triggerPageAction(QWebEnginePage::Redo);
}
