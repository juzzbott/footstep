#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include "app/controls/mapscene.h"
#include "app/controls/mapview.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);


    MapScene *scene = new MapScene(this);
    MapView *view = new MapView(scene, this);
    view->setDragMode(QGraphicsView::ScrollHandDrag);

    QBrush greenBrush(Qt::green);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);

    //QGraphicsRectItem *rectangle = scene->addRect(100, 0, 80, 100, outlinePen, greenBrush);
    //rectangle->setFlag(QGraphicsItem::ItemIsMovable);

    QImage image("E:/Development/1.png");
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(item);

    QGraphicsPixmapItem* item2 = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    item2->setPos(768,0);
    scene->addItem(item2);

    setCentralWidget(view);


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
