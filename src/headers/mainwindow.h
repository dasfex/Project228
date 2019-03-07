#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "headers//player.h"
#include <QGraphicsScene>
#include <QMainWindow>
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

protected slots:
    void keyPressEvent(QKeyEvent* event) override; // слот, который вызывается для управления игроком

signals:

private:
    QGraphicsScene* scene;

    Player* player;

    QTimer* control_timer_; // таймер для вызова слота управления героем

    void DrawMap();

};

#endif // MAINWINDOW_H
