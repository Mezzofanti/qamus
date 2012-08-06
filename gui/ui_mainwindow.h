/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Aug 5 11:48:44 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open;
    QAction *action_Close;
    QAction *actionE_xit;
    QAction *actionAbout_Qamus;
    QAction *actionAbout_Qt;
    QAction *actionSettings;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *searchBox;
    QTableView *lexiconView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QMenu *menu_Options;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(628, 368);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        action_Close = new QAction(MainWindow);
        action_Close->setObjectName(QString::fromUtf8("action_Close"));
        actionE_xit = new QAction(MainWindow);
        actionE_xit->setObjectName(QString::fromUtf8("actionE_xit"));
        actionAbout_Qamus = new QAction(MainWindow);
        actionAbout_Qamus->setObjectName(QString::fromUtf8("actionAbout_Qamus"));
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        verticalLayoutWidget = new QWidget(MainWindow);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(-1, 6, -1, -1);
        searchBox = new QLineEdit(verticalLayoutWidget);
        searchBox->setObjectName(QString::fromUtf8("searchBox"));
        searchBox->setMaxLength(256);
        searchBox->setCursorMoveStyle(Qt::VisualMoveStyle);

        verticalLayout->addWidget(searchBox);

        lexiconView = new QTableView(verticalLayoutWidget);
        lexiconView->setObjectName(QString::fromUtf8("lexiconView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lexiconView->sizePolicy().hasHeightForWidth());
        lexiconView->setSizePolicy(sizePolicy);
        lexiconView->setFocusPolicy(Qt::NoFocus);
        lexiconView->setSelectionMode(QAbstractItemView::NoSelection);
        lexiconView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        lexiconView->setShowGrid(false);
        lexiconView->setSortingEnabled(true);
        lexiconView->verticalHeader()->setVisible(false);
        lexiconView->verticalHeader()->setHighlightSections(false);

        verticalLayout->addWidget(lexiconView);

        MainWindow->setCentralWidget(verticalLayoutWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 628, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        menu_Options = new QMenu(menuBar);
        menu_Options->setObjectName(QString::fromUtf8("menu_Options"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menu_Options->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(action_Open);
        menuFile->addAction(action_Close);
        menuFile->addSeparator();
        menuFile->addAction(actionE_xit);
        menuAbout->addAction(actionAbout_Qamus);
        menuAbout->addAction(actionAbout_Qt);
        menu_Options->addAction(actionSettings);

        retranslateUi(MainWindow);
        QObject::connect(action_Open, SIGNAL(triggered()), MainWindow, SLOT(openLexicon()));
        QObject::connect(action_Close, SIGNAL(triggered()), MainWindow, SLOT(closeLexicon()));
        QObject::connect(actionE_xit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(searchBox, SIGNAL(textChanged(QString)), MainWindow, SLOT(searchLexicon()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Qamus", 0, QApplication::UnicodeUTF8));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", 0, QApplication::UnicodeUTF8));
        action_Close->setText(QApplication::translate("MainWindow", "&Close", 0, QApplication::UnicodeUTF8));
        actionE_xit->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        actionAbout_Qamus->setText(QApplication::translate("MainWindow", "About &Qamus", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setText(QApplication::translate("MainWindow", "About Qt", 0, QApplication::UnicodeUTF8));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        searchBox->setPlaceholderText(QApplication::translate("MainWindow", "search...", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("MainWindow", "&About", 0, QApplication::UnicodeUTF8));
        menu_Options->setTitle(QApplication::translate("MainWindow", "&Options", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
