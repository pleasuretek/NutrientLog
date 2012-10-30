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

#include "tracker.h"
#include "ui_tracker.h"

Tracker::Tracker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tracker)
{
    ui->setupUi(this);

    updateView();
    connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(addEntry()));
    connect(ui->editBtn, SIGNAL(clicked()),this, SLOT(editEntry()));
    connect(ui->removeBtn, SIGNAL(clicked()), this, SLOT(removeEntry()));
    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(selectEntry(QModelIndex)));

}

Tracker::~Tracker()
{
    delete ui;
}

void Tracker::addEntry() {
    Entry *e = new Entry();

    if(e->exec() != QDialog::Accepted) {
        //cancel clicked
    } else {
        //ok clicked do stuff here
        dbInsert(e->getAmts());
        updateView();
    }
}

void Tracker::editEntry() {
    Entry *e = new Entry();
    //QString oldName ="";
    QList<QVariant> oldAmts;
    bool toggle = false;
   // bool reAdd = false;

    while(!toggle){
        if(!ui->tableView->selectionModel()->selectedIndexes().isEmpty()) {
            QList<QModelIndex> selectedItems = ui->tableView->selectionModel()->selectedIndexes();
            QVariant id = selectedItems.takeFirst().data().toInt();

            QSqlQuery q;
            q.prepare("SELECT * FROM Tracker WHERE EntryID = :id");
            q.bindValue(":id",id);
            q.exec();
            if(!q.isActive()){
                //query failed
                QMessageBox::warning(this, tr("Entry Query"), tr("query failed to execute..."));
            } else {
                if(q.next()){ //populate with preExisting data
                    oldAmts.append(q.value(1).toString());
                    oldAmts.append(q.value(2).toInt());
                    oldAmts.append(q.value(3).toDouble());
                    oldAmts.append(q.value(4).toInt());
                    oldAmts.append(q.value(5).toInt());
                    oldAmts.append(q.value(6).toInt());
                    oldAmts.append(q.value(7).toString());

                    e->setAmts(oldAmts);

                }

            }
            q.clear();
            if(e->exec() != QDialog::Accepted) {
                //cancel was clicked
                toggle = true;
            } else { //UPDATE data
                if(dbUpdate(e->getAmts(),id)) {
                    updateView();
                    toggle = true;
                }else{
                   //print last error from database
                }
            }
        }
        toggle = true;
    }
}

void Tracker::removeEntry() {
    QList<QModelIndex> selectedItems = ui->tableView->selectionModel()->selectedIndexes();
    QVariant id = selectedItems.takeFirst().data().toInt();

    QSqlQuery q;
    q.prepare("DELETE FROM Tracker WHERE EntryID = :id");
    q.bindValue(":id", id.toInt());
    if(!q.exec()){
        //delete failed
        QMessageBox::warning(this, tr("delete failed"), tr("didn't remove data"));
    } else {
        updateView();
    }
}

void Tracker::selectEntry(QModelIndex model){
    ui->tableView->selectRow(model.row());
}

bool Tracker::dbInsert(QList<QVariant> l) {
    QSqlQuery q;
    q.prepare("INSERT INTO Tracker (Date, PPM, PH, TempHi, TempLo, Humid, Note) VALUES (?,?,?,?,?,?,?)");
    q.bindValue(0, l.at(0).toDate().toString());
    q.bindValue(1, l.at(1).toInt());
    q.bindValue(2, l.at(2).toDouble());
    q.bindValue(3, l.at(3).toInt());
    q.bindValue(4, l.at(4).toInt());
    q.bindValue(5, l.at(5).toInt());
    q.bindValue(6, l.at(6).toString());

    if(!q.exec()){
        //update failed
        //TODO: have message box print error..
        QMessageBox::warning(this, tr("Insert error"), tr("Error inserting database, please try again =)"));
        return false;
    } else {
        return true;
    }

}

bool Tracker::dbUpdate(QList<QVariant> l, QVariant id) {
    QSqlQuery q;
    q.prepare("UPDATE Tracker SET Date = :date, PPM = :ppm, PH = :ph, TempHi = :tempHi, TempLo = :tempLo, Humid = :humid, Note = :note WHERE EntryID = :id");
    q.bindValue(":date", l.at(0).toDate().toString());
    q.bindValue(":ppm", l.at(1).toInt());
    q.bindValue(":ph", l.at(2).toDouble());
    q.bindValue(":tempHi", l.at(3).toInt());
    q.bindValue(":tempLo", l.at(4).toInt());
    q.bindValue(":humid", l.at(5).toInt());
    q.bindValue(":note", l.at(6).toString());
    q.bindValue(":id", id);

    if(!q.exec()){
        //update failed
        QMessageBox::warning(this, tr("Update error"), tr("Error updating database, please try again =)"));
        return false;
    } else {
        return true;
    }
}

void Tracker::updateView() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT EntryID, Date, PPM, PH, TempHi, TempLo, Humid FROM Tracker");
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

