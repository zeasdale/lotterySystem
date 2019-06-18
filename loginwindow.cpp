#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(255, 145);
    this->setMaximumSize(255, 145);
    this->setWindowTitle("随机抽取系统");
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);
    QObject::connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(login()));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::login()
{
    QString username = ui->userLineEdit->text().trimmed();
    QString password = ui->pwdLineEdit->text().trimmed();

    if ((username == "admin") && (password == "admin"))
    {
        MainWindow *mainwindow = new MainWindow();
        mainwindow->show();
        this->close();
    }
    else
    {
        QMessageBox::information(this, "Permission error!", "用户名或者密码错误！");
        return;
    }
}
