#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "samplyinfowindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("随机抽取系统");
    this->setMinimumSize(400, 300);
    this->setMaximumSize(400, 300);
    QStringList * strList = new QStringList;
    importDataList = strList; // 初始化导入数据的数组
    QList<int> * intList = new QList<int>;
    randNumList = intList;
    countData();
    QObject::connect(ui->importButton, SIGNAL(clicked()), this,
                     SLOT(importCSV()));
//    QObject::connect(ui->startSamplyButton, SIGNAL(clicked()), this,
//                     SLOT(getUnrepeatRandNum()));
    QObject::connect(ui->aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::verify()
{
    if (ui->randNumInput->text().isEmpty() ||
        (ui->randNumInput->text().toInt() <= 0)) {
        QMessageBox::warning(this, "Warning!", "没有填写需要抽取的数量,或抽取数量小于零！");
        return false;
    } else if (importDataList->isEmpty() || importDataList->size() < ui->randNumInput->text().toInt()) {
        QMessageBox::warning(this, "Warning!", "需要抽取的数量超过导入的总数据！");
        return false;
    } else {
        return true;
    }
}

// 导入csv文件
QStringList * MainWindow::importCSV()
{
    QString file =
        QFileDialog::getOpenFileName(this, QStringLiteral("选择CSV文件"), "",
                                     tr("CSV file(*.csv)"));
    QStringList *temp = new QStringList();
    if (file.isEmpty()) { // 如果选择为空，返回一个空列表；
        QMessageBox::information(this, "information", "选择了错误的路径或文件！");
        QStringList *error = new QStringList;
        return error;
    } else {
        // 调用excelhelper帮助类
        CsvParser *csvPaser = new CsvParser();
        temp = csvPaser->importCsv(file); // 返回临时列表，里面记录了所有的CSV数据，目前作为全局变量，方便子窗口通过父指针调用；
        if(!importDataList->isEmpty()) {
            QMessageBox::warning(this, "Warning!", "已经有数据存在，将覆盖之前的数据！");
            importDataList->clear();
        }
        importDataList = temp;
        QMessageBox::information(this,
                                 "information",
                                 "本次总共导入了" + QString::number(
                                     temp->count()) + "条数据！");
    }
    countData();
    return temp;
}

//QList<int> * MainWindow::startSamply()
//{
//    QList<int> *intList = new QList<int>();
//    int sampleNum = ui->randNumInput->text().toInt();    // 用来确认需要在tempList中抽取多少个数
//    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime())); // 建立种子，没啥好说的，不懂自己去跳海
//    int a;                                               // 临时变量，用来临时记录每次抽取到的数字
//    int b = 0;                                           // 计数器
//    // 首先把tempList中的所有数字以下标数字的形式存入临时数组lntList
//    for (int i = 0; i < importDataList->size(); i++) {
//        intList->append(i);
//    }
//    // 开始打乱数字顺序，并选取sampleNum个个数
//    for (int i = intList->size(); i >= intList->size(); i--) {
//        a = qrand() % intList->size();
//        int rmInt = intList->takeAt(a);
//        randNumList->append(rmInt);
//        b++;
//        if (b == sampleNum) {
//            break;
//        }
//    }
//    // 打印数字，一会给我删了
//    for (int i = 0; i < randNumList->size(); i++) {
//        qDebug() << randNumList->at(i) << endl;
//    }
//    return intList;
//}
QList<int> MainWindow::getUnrepeatRandNum(int maxNum, int timesNum)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime())); // 建立种子，没啥好说的，不懂自己去跳海
    int a;                                               // 临时变量，用来临时记录每次抽取到的数字
    int b = 0;
    QList<int> list;
    QList<int> resultList;
    // 计数器
    // 首先把tempList中的所有数字以下标数字的形式存入临时数组lntList
    for (int i = 0; i < maxNum; i++) {
        list.append(i);
    }
    // 开始打乱数字顺序，并选取sampleNum个个数
    for (int i = list.size(); i >= list.size(); i--) {
        a = qrand() % list.size();
        int rmInt = list.takeAt(a);
        resultList.append(rmInt);
        b++;
        if (b == timesNum) {
            break;
        }
    }
    // 打印数字，一会给我删了
//    for (int i = 0; i < resultList.size(); i++) {
//        qDebug() << resultList.at(i) << endl;
//    }
    return resultList;
}
QList<int> MainWindow::getrepeatRandNum(int maxNum, int timesNum)
{
    QList<int> list;
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    for(int i = 0; i < timesNum; i++) {
        int a = qrand() % maxNum; //随机生成0到sampleNum的随机数
        list.append(a);
        //qDebug() << a;
    }
    return list;
}
void MainWindow::showAbout()
{
    about *a = new about();
    a->exec();
}

void MainWindow::on_startSamplyButton_clicked()
{
    if(!verify()) {
        return;
    } else {
        int timesNum = ui->randNumInput->text().toInt();
        int samplingNum = importDataList->size();
        QList<int> temp;
        if(ui->unrepeatRadioButton->isChecked()) {
            temp = getUnrepeatRandNum(samplingNum, timesNum);
            randNumList = &temp;
        } else {
            temp = getrepeatRandNum(samplingNum, timesNum);
            randNumList = &temp;
        }
        SamplyInfoWindow * samplyWin = new SamplyInfoWindow(this);
        samplyWin->exec();
    }
}

void MainWindow::countData()
{
    ui->statusBar->showMessage("目前有" + QString::number(importDataList->size()) + "条数据...");
}
