#include "singleevent.h"
#include "ui_singleevent.h"
#include <QStandardItemModel>
#include <QDebug>

SingleEvent::SingleEvent(bool isNew, int row, QTime *time, QString *description, QDate *date, QStandardItemModel &model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SingleEvent)
{
    ui->setupUi(this);
    ui->timeEdit->setTime(*time);
    ui->descriptionEdit->setText(*description);
    modelPassed = &model;
    eventDate = date;
    this->isNew = isNew;
    this->row = row;

}

SingleEvent::~SingleEvent()
{

    delete ui;

}


void SingleEvent::on_closeButton_clicked()
{
    this->close();
}



void SingleEvent::on_saveButton_clicked()
{
    QString timeString = ui->timeEdit->time().toString();
    QString description =  ui->descriptionEdit->toPlainText();
    if(isNew){
        QList<QStandardItem *> items;

        items.append(new QStandardItem(eventDate->toString("dd.MM.yyyy")));
        items.append(new QStandardItem(timeString));
        items.append(new QStandardItem(description));
        modelPassed->appendRow(items);
    }else{
        QModelIndex index = modelPassed ->index(row,1,QModelIndex());
        modelPassed->setData(index, timeString);
        index = modelPassed ->index(row,2,QModelIndex());
        modelPassed->setData(index, description);
    }
    emit valueChanged();


    this->close();


}
