#include <QFileDialog>
#include <QSettings>

#include "common.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Options *const options, QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _qamusView(options),
    _qamusProxy(this)
{
    ui->setupUi(this);
    ui->searchBox->setFocus();
    ui->searchBox->setFocusPolicy(Qt::StrongFocus);
    ui->statusBar->addPermanentWidget(&_progressBar, 0);

    connect(&_qamusView, SIGNAL(progress(int)), this, SLOT(updateProgress(int)));

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
    //event->ignore();
    event->accept();
}

void MainWindow::setWordSort(const int col)
{
    _qamusProxy.setSortRole(Qt::DisplayRole);
    _qamusProxy.sort(col, Qt::AscendingOrder);
    _qamusProxy.setSourceModel(&_qamusView);
    ui->lexiconView->setModel(&_qamusProxy);
}

void MainWindow::loadSettings()
{
    QSettings settings("qamus", "qamus");
    resize(settings.value("window/size", sizeHint()).toSize());
    move(settings.value("window/position", QPoint(0, 0)).toPoint());
    restoreState(settings.value("window/properties").toByteArray());
    _filename = settings.value("file").toString();
    _qamusView.loadLexicon(_filename);
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
    qDebug() << "[" << __FILE__ << "] open: " + filename;
    if (_qamusView.loadLexicon(filename))
    {
        _filename = filename;
        //ui->lexiconView->reset();
        //statusBar()->showMessage(tr("Lexicon loaded"), 1000);
    }
    else
    {
        //statusBar()->showMessage(tr("Unable to load lexicon"));
    }

    _progressBar.hide();
}

void MainWindow::closeLexicon()
{
    if (_qamusView.closeLexicon())
    {
        ui->lexiconView->reset();
    }
}

void MainWindow::searchLexicon()
{
    int col = 0; // change
    if (_qamusView.columnCount() == 0 || _qamusView.rowCount() == 0)
    {
        ui->searchBox->clear();
        return;
    }

    QString term = ui->searchBox->text();
    if (term.isEmpty())
    {
        _qamusView.startSearch(col, term);
        setWordSort(col);
        return;
    }
    else
    {
        _qamusProxy.setSortRole(Qt::DisplayRole);
        _qamusProxy.sort(_qamusView.columnCount() - 1, Qt::DescendingOrder);
        _qamusProxy.setSourceModel(&_qamusView);
        ui->lexiconView->setModel(&_qamusProxy);
    }

    qDebug("[%s] begin search: %s", __FILE__, term.toLocal8Bit().data());
    _progressBar.setMaximum(_qamusView.rowCount());
    _progressBar.show();
    SearchWorker* thread = new SearchWorker(&_qamusView, col, term, this);
    connect(thread, SIGNAL(searchFinished(SearchWorker*)), this, SLOT(searchFinished(SearchWorker*)));
    thread->start();
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
    qDebug() << "[" << __FILE__ << "] search completed";
    _progressBar.hide();
    _qamusProxy.invalidate();
    delete searchWorker;
}