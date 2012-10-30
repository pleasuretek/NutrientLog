#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QMessageBox>
#include <QtSql>
#include <QFile>

#include "tracker.h"
#include "newfile.h"



namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void updateViews();

public slots:
    void about();
    void newFile();
    void openFile();
    //void createDocks();




protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);

private:
    Ui::MainWindow *ui;

    void initialState();
    bool okToContinue();
    bool loadFile(const QString&);
    void createActions();
    void createMenus();
    void createToolBars();


    void readSettings();
    void writeSettings();
    void setCurrentFile(const QString&);

    QSqlDatabase db;
    QString curFile;

    QMenu *fileMenu;
    QMenu *helpMenu;
    QMenu *viewMenu;
    QToolBar *fileToolBar;
    QToolBar *viewToolBar;
    QAction *newAction;
    QAction *openAction;
    QAction *exitAction;
    QAction *aboutAction;

    Tracker *tracker;
    //KeeperCycle *cycles;
    //KeeperDevice *devices;
    //KeeperProduct *products;
    //KeeperProfile *profiles;
    //Task *tasks;
    //Calendar *cal;
};

#endif // MAINWINDOW_H
