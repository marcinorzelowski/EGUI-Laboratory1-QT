#ifndef SINGLEDAY_H
#define SINGLEDAY_H

#include <QDialog>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

namespace Ui {
class SingleDay;
}

class SingleDay : public QDialog
{
    Q_OBJECT

public:
    explicit SingleDay(QStandardItemModel &model, QDate &selectedDate,QWidget *parent = nullptr);
    ~SingleDay();
    void addEventToModel(QTime *time, QString description);
private slots:
    void on_addNewButton_clicked();
    void updateData();
    void on_closeButton_clicked();
    void on_deleteSelectedButton_clicked();

    void on_editSelectedButton_clicked();

signals:
    void eventsUpdated();
private:
    QSortFilterProxyModel *proxyModel;
    QStandardItemModel *modelPassed;
    Ui::SingleDay *ui;
    QDate *date;
};

#endif // SINGLEDAY_H
