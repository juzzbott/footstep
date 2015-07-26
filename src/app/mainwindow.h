#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGridLayout>

#include "about.h"

class QAction;
class QMenu;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QGridLayout gridMapView;

    About *mAboutWindow;

public slots:

    //! Exit Footstep
    void fileExit();
    void openFile();
    void showAbout();

};

#endif // MAINWINDOW_H
