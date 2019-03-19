#include "headers//mainwindow.h"
#include "headers//player.h"

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QString>
#include <QTextStream>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent) {

    DrawMap();
    setFixedSize(1080, 720); // пока так, под конец сделаем full screen

    player_ = new Player(100, 100, 100, 100);
    player_ = new Player(100, 100, 100, 100); // fix
}

void MainWindow::DrawMap() {

}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    double time = 2;
    switch (event->key()) {
    case Qt::Key_W: {
        player_->UpdateSpeed();
        player_->Move(time);

        player_->SetDirection(Direction::N);
        player_->SetDirectionForFrame(Direction::N);

        break;
    }
    case Qt::Key_A: {
        player_->SetDirection(Direction::W);
        player_->SetDirectionForFrame(Direction::W);

        player_->UpdateSpeed();
        player_->Move(time);

        break;
    }
    case Qt::Key_S: {
        player_->SetDirection(Direction::S);
        player_->SetDirectionForFrame(Direction::S);

        player_->UpdateSpeed();
        player_->Move(time);

        break;
    }
    case Qt::Key_D: {
        player_->SetDirection(Direction::E);
        player_->SetDirectionForFrame(Direction::E);

        player_->UpdateSpeed();
        player_->Move(time);
        break;
    }
    }

    DrawMap();
}

MainWindow::~MainWindow() {
    delete scene_;
    delete player_;
}
