#include "singleday.h"
#include "ui_singleday.h"
#include <QSortFilterProxyModel>
#include <QDate>
#include "singleevent.h"
#include <QDebug>

SingleDay::SingleDay(QStandardItemModel &model,QDate &selectedDate, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SingleDay)
{
    ui->setupUi(this);

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(&model);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setSelectionBehavior( QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    proxyModel->setFilterKeyColumn(0);
    proxyModel->setFilterFixedString(selectedDate.toString("dd.MM.yyyy"));

    date = new QDate(selectedDate);
    modelPassed = &model;
}

SingleDay::~SingleDay()
{
    delete ui;
}

void SingleDay::on_addNewButton_clicked()
{
    QTime *time = new QTime();
    QString *description = new QString();
    SingleEvent *singleEvent = new SingleEvent(true, 0, time, description, date,*modelPassed);
    singleEvent->show();
    QObject::connect(singleEvent, SIGNAL(valueChanged()), this, SLOT(updateData()));


}

void SingleDay::updateData()
{
    ui->tableView->update();
    emit(eventsUpdated());
}



void SingleDay::on_closeButton_clicked()
{
    emit eventsUpdated();
    this->close();

}

void SingleDay::on_deleteSelectedButton_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    proxyModel->removeRow(indexes[0].row());
    updateData();

}

void SingleDay::on_editSelectedButton_clicked()
{

    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    QModelIndex index = proxyModel->mapToSource(indexes[0]);

    QString description =  ui->tableView->model()->data(ui->tableView->model()->index(indexes[0].row(),2)).toString();
    QTime time =  QTime::fromString(ui->tableView->model()->data(ui->tableView->model()->index(indexes[0].row(),1)).toString().trimmed()+":00.000", "hh:mm:ss.zzz");


    SingleEvent *singleEvent = new SingleEvent(false, index.row(),&time, &description, date,*modelPassed);
    singleEvent->show();
    QObject::connect(singleEvent, SIGNAL(valueChanged()), this, SLOT(updateData()));

}
