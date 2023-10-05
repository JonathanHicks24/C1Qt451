#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLoginClicked(){
    QString username = ui->lineEdit_2->text();
    QString password = ui->lineEdit->text();

    if (username == "username" && password == "password"){
        //Run Stuff
        QMessageBox::information(this, "Login", "Succsessful Login");
        dungeon d;
        d.begin();
    }else{
        QMessageBox::warning(this, "Login", "Failed Login");
    }
}
