#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <ctime>
#include <QProcess>

int const MainWindow::EXIT_REBOOT = -123456789;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
    setWindowTitle("Angry Birds");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    setMouseTracking(true);
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    // Set Background
    ui->graphicsView->setObjectName("Background");
    ui->graphicsView->setStyleSheet("background-image:url(./image/back.PNG)");
    // Add SlingShot
    QPixmap pix = QPixmap::fromImage(QImage(":/image/Slingshot_2.png"));
    pixItem = new QGraphicsPixmapItem();
    pixItem->setPos(170,340);
    pixItem->setPixmap(pix);
    scene->addItem(pixItem);

    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    // Create ground (You can edit here)
    itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/image/GROUND2.PNG").scaled(width(),height()/6.0),world,scene));

    // Create Barrier
    barrier1=new Barrier(17.0f,20.0f,1.0f,6.0f,&timer,QPixmap(":/image/wood1.png").scaled(30,180),world,scene);
    itemList.push_back(barrier1);
    barrier2=new Barrier(21.0f,25.0f,4.0f,1.0f,&timer,QPixmap(":/image/wood.png").scaled(120,30),world,scene);
    itemList.push_back(barrier2);
    barrier3=new Barrier(25.0f,20.0f,1.0f,6.0f,&timer,QPixmap(":/image/wood1.png").scaled(30,180),world,scene);
    itemList.push_back(barrier3);
    barrier4=new Barrier(21.0f,25.0f,9.0f,1.0f,&timer,QPixmap(":/image/wood.png").scaled(270,30),world,scene);
    itemList.push_back(barrier4);
    Pig1=new PigBird(17.0f,26.0f,0.8f,&timer,QPixmap(":/image/bird_gray.png").scaled(40,48),world,scene);
    itemList.push_back(Pig1);
    Pig2=new PigBird(25.0f,26.0f,0.8f,&timer,QPixmap(":/image/bird_gray.png").scaled(40,48),world,scene);
    itemList.push_back(Pig2);
    Pig3=new PigBird(21.0f,12.0f,1.0f,&timer,QPixmap(":/image/bird_gray.png").scaled(50,60),world,scene);
    itemList.push_back(Pig3);

    // Music
    player =new QMediaPlayer();
    player->setMedia(QUrl("qrc:/image/stone_break.mp3"));
    // GIF
    label = new QLabel(this);
    movie = new QMovie(":/image/bomb.gif");
    label->setMovie(movie);
    label->setGeometry(10,350,100,100);
    movie->start();
    label->show();

    // Initialize
    v_yellow=0;
    v_blue=0;
    count=0;
    timer2=new QTimer();
    x=-1;

    // Push Button
    button1 = new QPushButton(this);
    button1->setGeometry(0,0,70,70);
    button1->setIcon(QIcon(":/image/ICON_EXIT.png"));
    button1->setIconSize(QSize(70,70));
    button1->show();
    button2 = new QPushButton(this);
    button2->setGeometry(70,0,70,70);
    button2->setIcon(QIcon(":/image/BUTTON_RESTART.png"));
    button2->setIconSize(QSize(70,70));
    button2->show();
    connect(button1,SIGNAL(clicked(bool)),this,SLOT(Btn1()));
    connect(button2,SIGNAL(clicked(bool)),this,SLOT(slotReboot()));

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Y && x==1){
        v_yellow+=2;
        Vx+=v_yellow;
        Vy+=v_yellow;
        birdieY->setLinearVelocity(b2Vec2(Vx,Vy));
    }
    if(e->key() == Qt::Key_B && x==2){
        v_blue-=6;
        Vx+=v_blue;
        Vy+=v_blue;
        birdieB->setLinearVelocity(b2Vec2(Vx,Vy));
    }
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress && (QCursor::pos().x()>80 && QCursor::pos().y()>200))
    {
        /* TODO : add your code here */
        std::cout << "Press !" << std::endl ;

        // Delete Bird generate before
        if(count!=0)
            delete_bird();
        count++;
        // Generate new bird
        x=rand()%4;
        if(x==0)
            birdie = new Bird(3.0f,4.0f,0.6f,&timer,QPixmap(":/bird.png").scaled(36,36),world,scene);
        else if(x==1){
            birdieY = new YellowBird(4.0f,4.0f,0.6f,&timer,QPixmap(":/image/bird_yellow.png").scaled(36,36),world,scene);
            v_yellow=0;
        }
        else if(x==2){
            birdieB = new BlueBird(5.0f,4.0f,0.6f,&timer,QPixmap(":/image/bird_blue.png").scaled(36,36),world,scene);
            v_blue=0;
        }
        else if(x==3){
            birdieR1 = new BrownBird(6.0f,4.0f,0.6f,&timer,QPixmap(":/image/XMAS_COOKIE_BIRD.png").scaled(36,36),world,scene);
            birdieR2 = new BrownBird(10.0f,4.0f,0.6f,&timer,QPixmap(":/image/XMAS_COOKIE_BIRD.png").scaled(36,36),world,scene);
            birdieR3 = new BrownBird(6.0f,8.0f,0.6f,&timer,QPixmap(":/image/XMAS_COOKIE_BIRD.png").scaled(36,36),world,scene);
        }

        // Catch Mouse position
        Cursor_x1=QCursor::pos().x();
        Cursor_y1=QCursor::pos().y();

        return true;
    }
    if(event->type() == QEvent::MouseMove && x==3)
    {
        /* TODO : add your code here */
        //std::cout << "Move !" << std::endl ;
    }
    if(event->type() == QEvent::MouseButtonRelease && (QCursor::pos().x()>80 && QCursor::pos().y()>200))
    {
        /* TODO : add your code here */
        // Catch last Mouse Position
        Cursor_x2=QCursor::pos().x();
        Cursor_y2=QCursor::pos().y();
        Vx=0.1*(Cursor_x1-Cursor_x2);
        Vy=0.1*(Cursor_y2-Cursor_y1);
        std::cout << "Release !" << std::endl ;
        if(x==0){
            birdie->setLinearVelocity(b2Vec2(Vx,Vy));
            itemList.push_back(birdie);
        }
        else if(x==1){

            birdieY->setLinearVelocity(b2Vec2(Vx,Vy));
            itemList.push_back(birdieY);
        }
        else if(x==2){
            birdieB->setLinearVelocity(b2Vec2(Vx,Vy));
            itemList.push_back(birdieB);
        }
        else if(x==3){
            birdieR1->setLinearVelocity(b2Vec2(Vx,Vy));
            birdieR2->setLinearVelocity(b2Vec2(Vx,Vy));
            birdieR3->setLinearVelocity(b2Vec2(Vx,Vy));
            itemList.push_back(birdieR1);
            itemList.push_back(birdieR2);
            itemList.push_back(birdieR3);
        }
        player->play();
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::delete_bird()
{
    if(x==0 ){delete birdie;}
    else if(x==1){delete birdieY;}
    else if(x==2){delete birdieB;}
    else if(x==3){delete birdieR1;delete birdieR2;delete birdieR3;}
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::Btn1()
{
    // Exit Game
    this->close();
}

void MainWindow::slotReboot()
{
    // Restart Game
    qApp->exit( EXIT_REBOOT );
}
