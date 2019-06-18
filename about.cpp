#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    this->setMaximumSize(330, 220);
    this->setMinimumSize(330, 220);
    this->setWindowTitle("使用说明");
}

about::~about()
{
    delete ui;
}
