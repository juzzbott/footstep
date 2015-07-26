#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>

#include "app/controls/maplayer.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Add the map layer to the
    MapLayer *mapLayer = new MapLayer(parent);

    QLabel *myimage = new QLabel();

    QPixmap pix ("E:\\Development\\map_tiles\\1.png");
    myimage->setPixmap(pix);

    setCentralWidget(myimage);

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
