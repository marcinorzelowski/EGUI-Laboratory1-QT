#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStandardItemModel *model;


private slots:

    void on_calendarWidget_clicked(const QDate &date);
    void setBackgroundColor();

private:
    Ui::MainWindow *ui;
    void saveToFile();
    void loadDataToTableModel(QStandardItemModel *model);
    void setDateBackgroundToCyan(QDate *date);
    QStringList getDataList();
};
#endif // MAINWINDOW_H
