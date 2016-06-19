#ifndef YELLOWBIRD_H
#define YELLOWBIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define YBIRD_DENSITY 10.0f
#define YBIRD_FRICTION 1.2f
#define YBIRD_RESTITUTION 0.1f

class YellowBird:public GameItem
{
public:
    YellowBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
};

#endif // YELLOWBIRD_H
