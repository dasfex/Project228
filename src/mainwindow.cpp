#include "headers//mainwindow.h"
#include "headers//player.h"

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QString>
#include <QTextStream>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent) {

    view_ = new QGraphicsView();
    DrawMap();
    setFixedSize(1080, 720); // пока так, под конец сделаем full screen
    player_ = new Player(100, 100, 100, 100); // fix
}

void MainWindow::DrawMap() {

}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(Qt::green);
    painter.setBrush(Qt::blue);
    painter.drawEllipse(player_->GetX(), player_->GetY(), 20, 20);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    double time = 2;
    switch (event->key()) {
    case Qt::Key_W: {
        player_->UpdateSpeed();
        player_->Move(time);

        player_->SetDirection(Direction::N);

        break;
    }
    case Qt::Key_A: {
        player_->SetDirection(Direction::W);

        player_->UpdateSpeed();
        player_->Move(time);

        break;
    }
    case Qt::Key_S: {
        player_->SetDirection(Direction::S);

        player_->UpdateSpeed();
        player_->Move(time);

        break;
    }
    case Qt::Key_D: {
        player_->SetDirection(Direction::E);

        player_->UpdateSpeed();
        player_->Move(time);
        break;
    }
    }
    repaint();
    DrawMap();
}

QGraphicsView *MainWindow::view() const
{
    return view_;
}

void MainWindow::setView(QGraphicsView *view)
{
    view_ = view;
}

//QGraphicsView *MainWindow::view() const
//{
//    return view_;
//}

//void MainWindow::setView(QGraphicsView *view)
//{
//    view_ = view;
//}

MainWindow::~MainWindow() {
    delete scene_;
    delete player_;
}
