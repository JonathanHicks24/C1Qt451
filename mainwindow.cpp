#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dungeon.h"
#include <fcntl.h>
#include <windows.h>

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
        run_game();
    }else{
        QMessageBox::warning(this, "Login", "Failed Login");
    }
}

void MainWindow::run_game() {
    if (!AllocConsole()) {
        QMessageBox::warning(this, "Error", "Failed to allocate console.");
        return;
    }

    FILE* fp;

    // Redirect stdout
    fp = freopen("CON", "w", stdout);
    if (!fp) {
        QMessageBox::warning(this, "Error", "Failed to redirect stdout.");
        FreeConsole();
        return;
    }

    // Redirect stderr
    fp = freopen("CON", "w", stderr);
    if (!fp) {
        QMessageBox::warning(this, "Error", "Failed to redirect stderr.");
        FreeConsole();
        return;
    }

    // Redirect stdin
    fp = freopen("CON", "r", stdin);
    if (!fp) {
        QMessageBox::warning(this, "Error", "Failed to redirect stdin.");
        FreeConsole();
        return;
    }

    dungeon d;
    d.begin();

    // Optionally, if you want to close the console after the game ends:
    // FreeConsole();
}