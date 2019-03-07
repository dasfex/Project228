#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "headers//player.h"
#include <QGraphicsScene>
#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void PaintEvent();

protected slots:
    void keyPressEvent(QKeyEvent* event) override; // слот, который вызывается для управления игроком

signals:

private:
    QGraphicsScene* scene_;

    Player* player_;

    QTimer* control_timer_; // таймер для вызова слота управления героем
    QTime* time_for_player_ = new QTime(0, 0, 0, 0); // счётчик времени для изменения состояния героя

    void DrawMap();

};

#endif // MAINWINDOW_H
