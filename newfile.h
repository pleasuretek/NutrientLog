#ifndef NEWFILE_H
#define NEWFILE_H

#include <QDialog>
#include <QtCore>
#include <QtGui>

namespace Ui {
    class NewFile;
}

class NewFile : public QDialog
{
    Q_OBJECT

public:
    explicit NewFile(QWidget *parent = 0);
    ~NewFile();

public slots:
    void fileDialogOpen();
    QString getName();
    QString getPasswd();
    void acceptCheck();
    QString nameCheck(QString);

private:
    Ui::NewFile *ui;
};

#endif // NEWFILE_H
