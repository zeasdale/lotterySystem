#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QList>
#include <QMessageBox>
#include <QFileDialog>
#include <QTime>
#include "csvparser.h"
#include "about.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QList<int> *randNumList;     // 随机抽取后的数组（无重复）
    QStringList *importDataList; // 导入的csv数据
    bool verify();
    void countData();

private slots:

    QStringList* importCSV();
    //QList<int> * startSamply();
    QList<int> getUnrepeatRandNum(int, int);
    QList<int> getrepeatRandNum(int, int);
    void showAbout();
    void on_startSamplyButton_clicked();

private:

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
