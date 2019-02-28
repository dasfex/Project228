#include "headers//mainwindow.h"

#include <QHBoxLayout>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent) {

    DrawMap();
    setFixedSize(1080, 720); // пока так, под конец сделаем full screen
}

void MainWindow::DrawMap() {
    scene = new QGraphicsScene(this);

}

MainWindow::~MainWindow() {}

