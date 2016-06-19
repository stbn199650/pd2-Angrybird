#ifndef BLUEBIRD_H
#define BLUEBIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QDragMoveEvent>
#include <QGraphicsItem>

#define BBIRD_DENSITY 10.0f
#define BBIRD_FRICTION 0.2f
#define BBIRD_RESTITUTION 0.7f

class BlueBird:public GameItem
{
public:
    BlueBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
};

#endif // BLUEBIRD_H
