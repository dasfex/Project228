#include "headers//mainwindow.h"
#include "headers//player.h"

#include <QHBoxLayout>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent) {

    DrawMap();
    setFixedSize(1080, 720); // пока так, под конец сделаем full screen

    player = new Player(100, 100, 100, 100);

    control_timer_ = new QTimer;
    connect(control_timer_, SIGNAL(timeout()), this, SLOT(keyPressEvent()));
    control_timer_->start(1000 / 50); // запуск слота 20 раз в секунду(наверное)
}

void MainWindow::DrawMap() {
    scene = new QGraphicsScene(this);

}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_W: {
        player->SetDirection(Direction::N);
        break;
    }
    case Qt::Key_A: {
        player->SetDirection(Direction::W);
        break;
    }
    case Qt::Key_S: {
        player->SetDirection(Direction::S);
        break;
    }
    case Qt::Key_D: {
        player->SetDirection(Direction::E);
        break;
    }
    }

    player->UpdateSpeed();

    player->Move(0.01);
}

MainWindow::~MainWindow() {}

