#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QPushButton>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <Qcursor>
#include <QMediaPlayer>
#include <QMovie>
#include <QLabel>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <barrier.h>
#include <yellowbird.h>
#include <bluebird.h>
#include <brownbird.h>
#include <pigbird.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    static int const EXIT_REBOOT;
    void delete_bird();
    void keyPressEvent(QKeyEvent *e);

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void Btn1();
    void slotReboot();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer,*timer2;
    Bird *birdie;

    int x,Vx,Vy,Cursor_x1,Cursor_y1,Cursor_x2,Cursor_y2,count;
    int v_yellow,v_blue;
    QGraphicsPixmapItem *pixItem;
    YellowBird *birdieY;
    BlueBird *birdieB;
    BrownBird *birdieR1,*birdieR2,*birdieR3;
    PigBird *Pig1,*Pig2,*Pig3;
    Barrier *barrier1,*barrier2,*barrier3,*barrier4;
    QPushButton *button1,*button2;
    QMediaPlayer *player;
    QMovie *movie;
    QLabel *label;
};

#endif // MAINWINDOW_H
