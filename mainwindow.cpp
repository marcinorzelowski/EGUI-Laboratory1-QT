#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "singleday.h"
#include <QFile>
#include <QTextFormat>
#include <QDebug>
#include <QDebug>
#include <QWindow>
#include <QDate>
#include <QTextCharFormat>
#include <QFile>
#include <QDir>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(801,581);
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    loadDataToTableModel(model);
    model->setHeaderData(1,Qt::Horizontal,tr("Time"));
    model->setHeaderData(2,Qt::Horizontal,tr("Description"));
    ui->calendarWidget->showToday();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    QDate selectedDate = ui->calendarWidget->selectedDate();
    SingleDay *singleDay = new SingleDay(*model, selectedDate, this);
    QString name = QString::number(date.year()) + "-" + QString::number(date.month()) + "-" + QString::number(date.day());
    singleDay ->setWindowTitle(name);
    singleDay -> show();
    QObject::connect(singleDay, SIGNAL(eventsUpdated()), this, SLOT(setBackgroundColor()));
}

void MainWindow::setBackgroundColor()
{
    QModelIndex index = model ->index(0,0,QModelIndex());
    for(int row = 0; row < model->rowCount(); row++){
        index = model ->index(row,0,QModelIndex());
        QDate date = QDate::fromString(model->data(index).toString(), "dd.MM.yyyy");
        setDateBackgroundToCyan(&date);
    }
}

void MainWindow::loadDataToTableModel(QStandardItemModel *model)
{
    QStringList dataList = getDataList();
    model->setRowCount(dataList.count());
    model->setColumnCount(3);
    //filling  the model:
    QStringList dataColumnsSeparatedList;
    dataColumnsSeparatedList.clear();
    for(int row = 0; row < dataList.count(); row++){
        dataColumnsSeparatedList = dataList.at(row).split(",");
        for(int col = 0; col < dataColumnsSeparatedList.count(); col++){
//            if(col==0){//set background for dates from file.
//                QDate date = QDate::fromString(dataColumnsSeparatedList.at(0),"dd.MM.yyyy");
//                setDateBackgroundToCyan(&date);
//            }
            QModelIndex index = model ->index(row,col,QModelIndex());
            model->setData(index, dataColumnsSeparatedList.at(col));
        }
    }
    setBackgroundColor();
}

void MainWindow::setDateBackgroundToCyan(QDate *date)
{
    QTextCharFormat *format = new QTextCharFormat();
    QBrush *color = new QBrush();
    color->setColor(Qt::cyan);
    format->setBackground(*color);
    ui->calendarWidget->setDateTextFormat(*date,*format);

}








QStringList MainWindow::getDataList()
{
    QFile file("data.txt");
    QString data;
    QStringList rowsOfData;
    data.clear();
    rowsOfData.clear();
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "No data";
        return rowsOfData;
    }
    data = file.readAll();
    rowsOfData = data.split("\n");
    return rowsOfData;
}

