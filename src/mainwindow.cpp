#include "headers//mainwindow.h"
#include "headers//player.h"

#include <QHBoxLayout>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent) {

    DrawMap();
    setFixedSize(1080, 720); // пока так, под конец сделаем full screen    

    player_ = new Player(100, 100, 100, 100);

    PaintEvent();

    control_timer_ = new QTimer;
    connect(control_timer_, SIGNAL(timeout()), this, SLOT(keyPressEvent()));
    control_timer_->start(1000 / 50); // запуск слота 20 раз в секунду(наверное)

}

void MainWindow::DrawMap() {
    scene_ = new QGraphicsScene(this);

}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    double time = time_for_player_->currentTime().msec() / 1000;
    time_for_player_->setHMS(0, 0, 0, 0);
    switch (event->key()) {
    case Qt::Key_W: {
        player_->SetDirection(Direction::N);
        break;
    }
    case Qt::Key_A: {
        player_->SetDirection(Direction::W);
        break;
    }
    case Qt::Key_S: {
        player_->SetDirection(Direction::S);
        break;
    }
    case Qt::Key_D: {
        player_->SetDirection(Direction::E);
        break;
    }
    }

    player_->UpdateSpeed();

    player_->Move(time);
}

void MainWindow::PaintEvent() {
    QPainter painter(this); // определяем объект painter, который обеспечивает рисование
    painter.drawImage(0,0, player_->GetPlayerImage().scaled(this->size())); // рисуем наше изображение от 0,0 и растягиваем по всему виджету
}

MainWindow::~MainWindow() {
    delete scene_;
    delete player_;
    delete control_timer_;
    delete time_for_player_;
}

