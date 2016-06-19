#ifndef BROWNBIRD_H
#define BROWNBIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define RBIRD_DENSITY 10.0f
#define RBIRD_FRICTION 0.2f
#define RBIRD_RESTITUTION 0.5f

class BrownBird:public GameItem
{
public:
    BrownBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
};

#endif // BROWNBIRD_H
