#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "app/controls/maplayer.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    MapLayer *mapLayer = new MapLayer(parent);
    setCentralWidget(mapLayer);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::fileExit() {
    qApp->exit(0);
}

void MainWindow::openFile() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
}

void MainWindow::showAbout() {
    mAboutWindow = new About();
    mAboutWindow->setModal(true);
    mAboutWindow->show();
}
