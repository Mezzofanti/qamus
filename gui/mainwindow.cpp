#include <QApplication>
#include <QFileDialog>
#include <QSettings>

#include "common.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Options *const options, QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _searchCol(0),
    _qamusModel(options, this),
    _qamusProxy(this),
    QLX("qlx"),
    QRX("qrx"),
    XDXF("xdxf")
{
    ui->setupUi(this);
    ui->searchBox->setFocus();
    ui->searchBox->setFocusPolicy(Qt::StrongFocus);
    ui->statusBar->addPermanentWidget(&_progressBar, 0);

    connect(&_qamusModel, SIGNAL(progress(int)), this, SLOT(updateProgress(int)));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    _qamusProxy.setSortRole(Qt::DisplayRole);
    _qamusProxy.setSourceModel(&_qamusModel);
    ui->lexiconView->setModel(&_qamusProxy);

    setWordSort(0);
    _progressBar.hide();
    loadSettings();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::activateSystemTray(const bool activate)
{
    if (activate == true)
    {
        _systemTrayIcon.show();
    }
    else
    {
        _systemTrayIcon.hide();
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(1);
    _systemTrayIcon.showMessage("Qamus has been closed", tr("Click here to open Qamus again"), icon, 10000);
    hide();
    event->accept();
}

void MainWindow::setWordSort(const int col)
{
    _qamusProxy.sort(col, Qt::AscendingOrder);
}

void MainWindow::loadSettings()
{
    QSettings settings("qamus", "qamus");
    resize(settings.value("window/size", sizeHint()).toSize());
    move(settings.value("window/position", QPoint(0, 0)).toPoint());
    restoreState(settings.value("window/properties").toByteArray());
    _filename = settings.value("file").toString();
    openLexicon(_filename);
}

void MainWindow::openLexicon(const QString& filename)
{
    qDebug() << tr("opening %1").arg(filename);
    if (_qamusModel.loadLexicon(filename))
    {
        _filename = filename;
        qDebug() << tr("opened %1").arg(filename);

        for (int i = 0; i < _qamusModel.columnCount() -1; ++i)
        {
            QString language = _qamusModel.getLanguage(i);
            ui->columnSelectBox->insertItem(i, QIcon(), language);
        }

        int col = _qamusModel.columnCount() - 1;
        ui->lexiconView->horizontalHeader()->setResizeMode(col, QHeaderView::ResizeToContents);
        for (int i = 0; i < col; ++i)
        {
            ui->lexiconView->horizontalHeader()->setResizeMode(i, QHeaderView::Stretch);
        }
    }
    else
    {
        qCritical() << tr("failed to open %1").arg(filename);
    }
}

void MainWindow::openLexicon()
{
    QString path;
    if (_filename.isEmpty())
    {
        path = QDir::currentPath();
    }
    else
    {
        path = _filename;
    }

    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open lexicon"),
                                                    path,
                                                    tr("All lexicon files") + " (*." + QLX + " *." + XDXF + ") ;; " +
                                                    tr("All Qamus lexicon files") + " (*." + QLX + ") ;; " +
                                                    tr("All XDXF files") + " (*." + XDXF + ") ;; " +
                                                    tr("All files") + " (*.*)");
    if (!filename.isEmpty())
    {
        openLexicon(filename);
    }
}

void MainWindow::closeLexicon()
{
    if (_qamusModel.closeLexicon())
    {
        ui->columnSelectBox->clear();
        ui->lexiconView->reset();
    }
}

void MainWindow::searchLexicon()
{
    if (_qamusModel.columnCount() == 0 || _qamusModel.rowCount() == 0)
    {
        ui->searchBox->clear();
        return;
    }

    QString term = ui->searchBox->text();
    if (term.isEmpty())
    {
        _qamusModel.clearSearch();
        setWordSort(_searchCol);
        return;
    }
    else
    {
        _qamusProxy.setSortRole(Qt::DisplayRole);
        _qamusProxy.sort(_qamusModel.columnCount() - 1, Qt::DescendingOrder);
        _qamusProxy.setSourceModel(&_qamusModel);
        ui->lexiconView->setModel(&_qamusProxy);
    }

    qDebug() << tr("begin search: %1").arg(term.toLocal8Bit().data());
    _progressBar.setMaximum(_qamusModel.rowCount());
    _progressBar.show();
    SearchWorker* thread = new SearchWorker(&_qamusModel, _searchCol, term, this);
    connect(thread, SIGNAL(searchFinished(SearchWorker*)), this, SLOT(searchFinished(SearchWorker*)));
    thread->start();
}

void MainWindow::selectColumn(const int col)
{
    if (col >= 0 && col < _qamusModel.columnCount() - 1)
    {
        _searchCol = col;
        searchLexicon();
    }
}

void MainWindow::saveSettings()
{
    QSettings settings("qamus", "qamus");
    settings.setValue("window/size", size());
    settings.setValue("window/position", pos());
    settings.setValue("window/properties", saveState());
    settings.setValue("file", _filename);
}


void MainWindow::updateProgress(const int percent)
{
    _progressBar.setValue(percent);
}


void MainWindow::searchFinished(SearchWorker* searchWorker)
{
    delete searchWorker;
    qDebug() << tr("search completed");
    _progressBar.hide();
    _qamusProxy.invalidate();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() >= Qt::Key_F1 && event->key() <= Qt::Key_F12)
    {
        int col = event->key() - Qt::Key_F1;
        selectColumn(col);
        event->ignore();
    }
    else
    {
        event->accept();
    }
}