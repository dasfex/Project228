#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "headers//player.h"
#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    QGraphicsScene* scene;

    Player* player;

    void DrawMap();

};

#endif // MAINWINDOW_H
