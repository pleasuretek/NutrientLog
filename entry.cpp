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

#include "entry.h"
#include "ui_entry.h"

Entry::Entry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Entry)
{
    ui->setupUi(this);

    QDate *today = new QDate;
    today->currentDate();
    startDateCal = new QCalendarWidget;

    //ui->imageGroup->setVisible(false);

    ui->dateEdit_date->setDate(today->currentDate());
    ui->dateEdit_date->setCalendarWidget(startDateCal);
    ui->dateEdit_date->setCalendarPopup(true);

    //TODO: connect addImageBtn to slot that adds an image to database

    //TODO: query database for images with EntryID to populate ui->imageTable

}

Entry::~Entry()
{
    delete ui;
}

QList<QVariant> Entry::getAmts() {
    QList<QVariant> list;
    list.append(ui->dateEdit_date->date());
    list.append(ui->spinBox_ppm->value());
    list.append(ui->doubleSpinBox_ph->value());
    list.append(ui->tempHiBox->value());
    list.append(ui->tempLoBox->value());
    list.append(ui->humidBox->value());
    list.append(ui->noteTextEdit->toPlainText());


    return list;

}

void Entry::setAmts(QList<QVariant> list) {
    if(!list.isEmpty()) {

        ui->dateEdit_date->setDate(QDate::fromString(list.at(0).toString()));
        ui->spinBox_ppm->setValue(list.at(1).toInt());
        ui->doubleSpinBox_ph->setValue(list.at(2).toDouble());
        ui->tempHiBox->setValue(list.at(3).toInt());
        ui->tempLoBox->setValue(list.at(4).toInt());
        ui->humidBox->setValue(list.at(5).toInt());
        ui->noteTextEdit->setPlainText(list.at(6).toString());
    }
}

void Entry::setImg() {

}

void Entry::getImg() {


  //  QSqlQuery q;
  //  q.prepare("SELECT COUNT(*) FROM Image WHERE EntryID = :entryID");
  //  q.bindValue(":entryID", id);

}
