#include "samplyinfowindow.h"
#include "ui_samplyinfowindow.h"

SamplyInfoWindow::SamplyInfoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SamplyInfoWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("结果集");
    this->setMaximumSize(400, 650);
    this->setMinimumSize(400, 650);
    // 获取主窗口父指针，非常重要，不要漏了
    pParent = (MainWindow *)parentWidget();
    QStringList * list = new QStringList;
    resultList = list;
    showResult();
    QObject::connect(ui->historyButton, SIGNAL(clicked()), this, SLOT(reviewHistory()));
}

SamplyInfoWindow::~SamplyInfoWindow()
{
    delete ui;
}
void SamplyInfoWindow::showResult()
{
    int randNum = pParent->randNumList->size();
    for (int i = 0; i < randNum; i++) {
        QString name  = pParent->importDataList->at(pParent->randNumList->at(i));
        QListWidgetItem *item = new QListWidgetItem();
        resultList->append(name);
        item->setText("第" + QString::number(i + 1) + "个抽取到的数据为： " + name);
        ui->listWidget->addItem(item);
    }
}
void SamplyInfoWindow::exportResult()
{
    if(resultList->isEmpty()) {
        QMessageBox::information(this, "information", "没有抽取结果");
        return;
    }
    //获取创建的csv文件名
    QString fileName = QFileDialog::getSaveFileName(this, tr("CSV file"), qApp->applicationDirPath (),
                       tr("Files (*.csv)"));
    CsvParser * csvparser = new CsvParser;
    csvparser->exportCsv(fileName, resultList);
}

void SamplyInfoWindow::on_exportButton_clicked()
{
    exportResult();
}
void SamplyInfoWindow::reviewHistory()
{
    QMessageBox::information(this, "information", "以后再写啦，休息下！");
}
