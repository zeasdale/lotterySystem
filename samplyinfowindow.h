#ifndef SAMPLYINFOWINDOW_H
#define SAMPLYINFOWINDOW_H

#include <QDialog>
#include <QFileDialog>
#include <QListWidgetItem>
#include "mainwindow.h"

namespace Ui
{
    class SamplyInfoWindow;
}

class SamplyInfoWindow : public QDialog
{
    Q_OBJECT

public:

    explicit SamplyInfoWindow(QWidget *parent = nullptr);
    ~SamplyInfoWindow();

private slots:
    void on_exportButton_clicked();
    void reviewHistory();

private:

    Ui::SamplyInfoWindow *ui;
    MainWindow *pParent;
    QStringList * resultList;
    void showResult();
    void exportResult();

};

#endif // SAMPLYINFOWINDOW_H
