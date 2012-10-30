/*
**program name: NutrientLog
**version: 0.1
**Author: Travis McCann (aka pleasuretek)
**Icon by Giorgos Vasiliadis
**
This file is part of NutrientLog.

    NutrientLog is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    NutrientLog is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with NutrientLog.  If not, see <http://www.gnu.org/licenses/>.
*/



#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");

    createActions();
    createMenus();

    readSettings();
    newFile();

    tracker = new Tracker();
    setCentralWidget(tracker);

    connect(this, SIGNAL(updateViews()), tracker, SLOT(updateView()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if (okToContinue()) {
        writeSettings();
        e->accept();
    } else {
        e->ignore();
    }
}

bool MainWindow::okToContinue()
{
    //isWindowModified is a built in function... need to implement my own modified funciton to be able to tell if changes were made that need to be saved (or databases that need deleting...)
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("Exit Application?"),
                        tr("Are You Sure You Want to Quit?"),
                        QMessageBox::Yes | QMessageBox::No
                        | QMessageBox::Cancel);
        if (r == QMessageBox::Yes) {
            return true;
        } else if (r == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

void MainWindow::createActions()
{
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/image/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new file"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openAction = new QAction(tr("&Open"), this);
    openAction->setIcon(QIcon(":/image/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));



    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    aboutAction = new QAction(tr("About"), this);
    aboutAction->setStatusTip(tr("About the application"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);

    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    menuBar()->addSeparator();

    viewMenu = menuBar()->addMenu(tr("&View"));

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);


    viewToolBar = addToolBar(tr("&View"));
}

/* //commented out because reused mainwindow from bigger project..
void MainWindow::createDocks()
{
     ui->propDock->setVisible(true);
     ui->tasksDock->setVisible(true);
    //set where the docs can be placed
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    //create dock objects
    cycles = new KeeperCycle();
    devices = new KeeperDevice();
    products = new KeeperProduct();
    profiles = new KeeperProfile();
    tasks = new Task();
    cal = new Calendar();

    setCentralWidget(cal);

    connect(this, SIGNAL(updateViews()), cycles, SLOT(updateView()));
    connect(this, SIGNAL(updateViews()), devices, SLOT(updateView()));
    connect(this, SIGNAL(updateViews()), products, SLOT(updateView()));
    connect(this, SIGNAL(updateViews()), profiles, SLOT(updateView()));
    QTabWidget *propTabWidget = new QTabWidget();
    propTabWidget->addTab(cycles, tr("Cycles"));
    propTabWidget->addTab(profiles, tr("Profiles"));
    propTabWidget->addTab(products, tr("Products"));
    propTabWidget->addTab(devices, tr("Electrical"));
    ui->propDock->setWidget(propTabWidget);
    viewMenu->addAction(ui->propDock->toggleViewAction());
    viewToolBar->addAction(ui->propDock->toggleViewAction());

    ui->tasksDock->setWidget(tasks);
    //ui->taskDock->toggleViewAction()->setIcon();
    viewMenu->addAction(ui->tasksDock->toggleViewAction());
    viewToolBar->addAction(ui->tasksDock->toggleViewAction());
    emit updateViews();
}
*/
void MainWindow::about()
{
    QMessageBox::about(this, tr("GroMo"),
            tr("<h2>GroMo</h2>"
               "<h3>An Indoor Gardening Calendar and Calculator</h3>"
               "<p>Copyright &copy; 2010 Digital Growth Systems LLC</p>"
               "<p>GroMo is designed to help "
               "indoor gardeners with many "
               "of the calculations and record keeping "
               "tasks assiociated with tending a productive garden. </p>"));
}

void MainWindow::readSettings()
{
   QSettings settings("Digital Growth Systems LLC", "GroMo");
    restoreGeometry(settings.value("mainGeo").toByteArray());
    restoreState(settings.value("mainState").toByteArray());

}

void MainWindow::writeSettings()
{
    QSettings settings("Digital Growth Systems LLC", "GroMo" );

    settings.setValue("mainGeo", saveGeometry());
    settings.setValue("mainState", saveState());
}

void MainWindow::newFile()
{

    NewFile *newFile = new NewFile();

    if(newFile->exec() != QDialog::Accepted) {
        //cancel clicked - Do Nothing
    } else {
        //create a new database with name
        //TODO: use password for encryption of data...
        QString fileName = newFile->getName();
        db.setDatabaseName(fileName);
        if(!db.open()){
            //handle fail
            QMessageBox::warning(this, tr("databse error"), db.lastError().databaseText());
        } else{
            db.transaction();
            QSqlQuery query;
            query.prepare("CREATE TABLE IF NOT EXISTS 'Tracker' ('EntryID' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 'Date' TEXT NOT NULL, 'PPM' INTEGER NOT NULL, 'PH' REAL NOT NULL, 'TempHi' INTEGER NOT NULL, 'TempLo' INTEGER NOT NULL, 'Humid' INTEGER NOT NULL, 'Note' TEXT)");
            query.exec();
            query.clear();
            query.prepare("CREATE TABLE IF NOT EXISTS 'Image' ('ImageID' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 'EntryID' INTEGER NOT NULL, 'IMG' BLOB NOT NULL)");
            query.exec();
            query.clear();

            db.commit();
            emit updateViews();
            setCurrentFile(fileName.section("/", -1));
        }
    }


}

void MainWindow::openFile()
{
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open Grower File"), ".",
                                   tr("Grower files (*.gro)"));
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::loadFile(const QString &fileName)
{
//load file and start transaction and isMEM flag to 0

    if ( QFile::exists(fileName)){

        db.setDatabaseName(fileName);

        if(!db.open()) {
            QMessageBox::warning(this, tr("Grower\'s file"),
                                 tr("Cannot read data file %1:\n%2."),tr("fileName"));
            return false;
        }
        else{
            //emit a signal to fire slots in each object...
            //each slot calls the updateView() funct for that class
            emit updateViews();
            setCurrentFile(fileName);
            return true;
        }
    } else {
        return false;
    }
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName; //= tr("Untitled");
    if (!curFile.isEmpty()) {
        shownName = QFileInfo(curFile).fileName();
    }

    MainWindow::setWindowTitle(tr("%1[*] - %2").arg(shownName)
                                   .arg(tr("GroMo")));

}


