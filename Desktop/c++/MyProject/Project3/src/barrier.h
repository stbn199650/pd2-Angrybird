#ifndef BARRIER_H
#define BARRIER_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define BARRIER_DENSITY 10.0f
#define BARRIER_FRICTION 0.4f
#define BARRIER_RESTITUTION 0.1f

class Barrier:public GameItem
{
public:
    Barrier(float x, float y, float w,float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // BARRIER_H
