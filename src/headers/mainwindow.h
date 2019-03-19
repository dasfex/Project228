#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "headers//player.h"
#include <QMainWindow>
#include <QGraphicsScene>
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
<<<<<<< HEAD
    ~MainWindow() override;
    void keyPressEvent(QKeyEvent* event) override; // слот, который вызывается для управления игроков
=======

    ~MainWindow() override;

    void keyPressEvent(QKeyEvent* event) override; // слот, который вызывается для управления игроком
>>>>>>> ccc7dfd4b233592d2473e48c838bf5ad8b957e8a

private:

    QGraphicsScene* scene_;

    Player* player_;

    void DrawMap();

};

#endif // MAINWINDOW_H
