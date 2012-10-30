/*
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

#include "newfile.h"
#include "ui_newfile.h"

NewFile::NewFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFile)
{
    ui->setupUi(this);

    ui->name->setText(QDir::homePath());

    //
    connect(ui->okBtn, SIGNAL(clicked()), this, SLOT(acceptCheck()));
    connect(ui->fileDialogBtn, SIGNAL(clicked()), this, SLOT(fileDialogOpen()));

}

NewFile::~NewFile()
{
    delete ui;
}

void NewFile::fileDialogOpen()
{
    QString path = ui->name->text();
    QString fullName = QFileDialog::getSaveFileName(this, tr("Where to create file?"), path , tr("Grower Files (*.gro"));
    if (!fullName.isEmpty()){
       // QString fileName = fullName.section("/", -1); // remove just filename from full path

        ui->name->setText(fullName);
    }
}

QString NewFile::getName()
{
    QString name = nameCheck(ui->name->text());
    return name;
}

QString NewFile::getPasswd()
{
    return ui->passwd->text();
}

void NewFile::acceptCheck()
{
    QString pass;
    pass = ui->passwd->text();
    if(pass != ui->passwdConfirm->text()) {
        QMessageBox::warning(this,tr("password error"),tr("Passwords do not match"));
        ui->passLabel->setText("*Password");
        ui->passLabel_2->setText("*Password Confirm");
        ui->passwd->setText("");
        ui->passwdConfirm->setText("");
    } else {
        accept();
    }
}

QString NewFile::nameCheck(QString name)
{
    //if filename doesnt contain .gro then add it
    QRegExp rx("*.gro");
     rx.setPatternSyntax(QRegExp::Wildcard);
     if(!rx.exactMatch(name))
         name.append(".gro");
     return name;
}
