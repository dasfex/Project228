#include "headers//mainwindow.h"
#include "headers//player.h"

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QString>
#include <QTextStream>
QTextStream cout(stdout);
QTextStream cin(stdin);

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent) {

    DrawMap();
    setFixedSize(1080, 720); // пока так, под конец сделаем full screen

<<<<<<< HEAD
    player_ = new Player(100, 100, 100, 100);
=======
    player_ = new Player(100, 100, 100, 100); // fix
>>>>>>> ccc7dfd4b233592d2473e48c838bf5ad8b957e8a
}

void MainWindow::DrawMap() {

}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    double time = 2;
    switch (event->key()) {
    case Qt::Key_W: {
        player_->SetDirection(Direction::N);
<<<<<<< HEAD
        player_->UpdateSpeed();
        player_->Move(time);
=======
        player_->SetDirectionForFrame(Direction::N);
>>>>>>> ccc7dfd4b233592d2473e48c838bf5ad8b957e8a
        break;
    }
    case Qt::Key_A: {
        player_->SetDirection(Direction::W);
<<<<<<< HEAD
        player_->UpdateSpeed();
        player_->Move(time);
=======
        player_->SetDirectionForFrame(Direction::W);
>>>>>>> ccc7dfd4b233592d2473e48c838bf5ad8b957e8a
        break;
    }
    case Qt::Key_S: {
        player_->SetDirection(Direction::S);
<<<<<<< HEAD
        player_->UpdateSpeed();
        player_->Move(time);
=======
        player_->SetDirectionForFrame(Direction::S);
>>>>>>> ccc7dfd4b233592d2473e48c838bf5ad8b957e8a
        break;
    }
    case Qt::Key_D: {
        player_->SetDirection(Direction::E);
<<<<<<< HEAD
        player_->UpdateSpeed();
        player_->Move(time);
        break;
    }
    }
    repaint();
=======
        player_->SetDirectionForFrame(Direction::E);
        break;
    }
    }

    player_->UpdateSpeed();
    player_->Move(time);

    DrawMap();
>>>>>>> ccc7dfd4b233592d2473e48c838bf5ad8b957e8a
}

MainWindow::~MainWindow() {
    delete scene_;
    delete player_;
<<<<<<< HEAD
=======
    delete control_timer_;
>>>>>>> ccc7dfd4b233592d2473e48c838bf5ad8b957e8a
}
