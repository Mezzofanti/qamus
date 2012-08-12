#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QMainWindow>
#include <QProgressBar>
#include <QSystemTrayIcon>

#include "options.h"
#include "qamusview.h"
#include "qamusproxy.h"
#include "searchworker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Options* const options, QWidget* parent = 0);
    ~MainWindow();
    void loadSettings();
    void saveSettings();

public slots:
    void openLexicon();
    void closeLexicon();
    void searchLexicon();
    void updateProgress(const int percent);
    void searchFinished(SearchWorker* searchWorker);

private:
    void activateSystemTray(const bool activate);
    void closeEvent(QCloseEvent* event);
    void setWordSort(const int col);

    Ui::MainWindow* ui;
#ifndef _WIN32
    Options* _options;
#endif // _WIN32
    QString _filename;
    QamusView _qamusView;
    QamusProxy _qamusProxy;
    QProgressBar _progressBar;
    QSystemTrayIcon _systemTrayIcon;

    const QString QLX = "qlx";
    const QString QRX = "qrx";
    const QString XDXF = "xdxf";
};

#endif // MAINWINDOW_H
