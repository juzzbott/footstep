#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create the actions
    this->createActions();
    this->createMenus();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenus() {

}

void MainWindow::createActions() {

}

void MainWindow::fileExit() {

    qApp->exit(0);

}

void MainWindow::openFile() {

    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));

}
