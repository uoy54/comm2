#include "ClickableScene.h"

ClickableScene::ClickableScene(QObject *parent) : QGraphicsScene(parent)
{
}

void ClickableScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit sceneClicked(event->scenePos());
    QGraphicsScene::mousePressEvent(event);
}
