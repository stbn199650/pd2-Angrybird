#ifndef PIGBIRD_H
#define PIGBIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define PBIRD_DENSITY 10.0f
#define PBIRD_FRICTION 0.3f
#define PBIRD_RESTITUTION 0.4f

class PigBird:public GameItem
{
public:
    PigBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // PIGBIRD_H
