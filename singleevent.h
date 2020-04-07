#ifndef SINGLEEVENT_H
#define SINGLEEVENT_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class SingleEvent;
}

class SingleEvent : public QDialog
{
    Q_OBJECT

public:
    explicit SingleEvent(bool isNew, int row, QTime *time, QString *description, QDate *date, QStandardItemModel &model, QWidget *parent = nullptr);
    ~SingleEvent();

private slots:


    void on_closeButton_clicked();
    void on_saveButton_clicked();
signals:
    void valueChanged();
private:
    int row;
    bool isNew;
    QDate *eventDate;
    QStandardItemModel *modelPassed;
    Ui::SingleEvent *ui;
};

#endif // SINGLEEVENT_H
