#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "headers//player.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTime>
#include <QTimer>
#include <QWidget>
#include <QLabel>
#include <QGraphicsView>


QT_BEGIN_NAMESPACE
class QGraphicsScene;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    void keyPressEvent(QKeyEvent* event) override; // слот, который вызывается для управления игроков

    QGraphicsView *view() const;
    void setView(QGraphicsView *view);

private:

    QGraphicsScene* scene_;

    Player* player_;
    QGraphicsView* view_;

    void DrawMap();

};

#endif // MAINWINDOW_H
