#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QDebug>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , graph(29)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);

    // Инициализация графа
    graph.addEdge(0,17);
    graph.addEdge(0,1);
    graph.addEdge(1,2);
    graph.addEdge(1,17);
    graph.addEdge(2,3);
    graph.addEdge(2,17);
    graph.addEdge(2,1);
    graph.addEdge(3,17);
    graph.addEdge(3,4);
    graph.addEdge(4,17);
    graph.addEdge(4,5);
    graph.addEdge(5,17);
    graph.addEdge(5,6);
    graph.addEdge(6,17);
    graph.addEdge(7,18);
    graph.addEdge(7,8);
    graph.addEdge(8,18);
    graph.addEdge(8,9);
    graph.addEdge(9,18);
    graph.addEdge(9,10);
    graph.addEdge(10,18);
    graph.addEdge(10,11);
    graph.addEdge(11,18);
    graph.addEdge(12,19);
    graph.addEdge(12,13);
    graph.addEdge(13,19);
    graph.addEdge(13,14);
    graph.addEdge(14,19);
    graph.addEdge(14,15);
    graph.addEdge(15,19);
    graph.addEdge(15,16);
    graph.addEdge(16,19);
    graph.addEdge(17,18);
    graph.addEdge(17,20);
    graph.addEdge(17,28);
    graph.addEdge(18,19);
    graph.addEdge(18,28);
    graph.addEdge(19,28);
    graph.addEdge(24,19);
    graph.addEdge(21,20);
    graph.addEdge(22,20);
    graph.addEdge(23,20);
    graph.addEdge(21,22);
    graph.addEdge(22,23);
    graph.addEdge(24,25);
    graph.addEdge(24,26);
    graph.addEdge(24,27);
    graph.addEdge(25,26);
    graph.addEdge(26,27);

    nodePositions = {
        QPointF(185,176), QPointF(173,157), QPointF(161,136),
        QPointF(149,114), QPointF(131,93), QPointF(117,70),
        QPointF(134,57),  QPointF(232,101), QPointF(222,75),
        QPointF(214,54),  QPointF(209,27),  QPointF(223,21),
        QPointF(402,105), QPointF(420,84), QPointF(434,65),
        QPointF(457,36),  QPointF(473,46),  QPointF(208,181),
        QPointF(250,122), QPointF(390,141), QPointF(210,203),
        QPointF(186,224), QPointF(184,234), QPointF(235,226),
        QPointF(414,230), QPointF(372,293), QPointF(415,293),
        QPointF(489,293), QPointF(310,133)
    };

    drawMap();
    drawNodes();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setupScene() {
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 962, 504);
    ui->graphicsView->setScene(scene);
}

void MainWindow::drawMap() {
    scene->clear();
    if (mapPixmap.isNull()) {
        mapPixmap.load(":/images/Screenshot_2.bmp");
    }

    QPixmap scaledPixmap = mapPixmap.scaled(ui->graphicsView->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    mapItem = scene->addPixmap(scaledPixmap);

    scene->setSceneRect(mapItem->boundingRect());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    qDebug() << "Размер окна:" << ui->graphicsView->size();
    qDebug() << "Размер изображения:" << scaledPixmap.size();
    qDebug() << "Размер сцены:" << scene->sceneRect();
}


void MainWindow::drawNodes() {
    for (QPointF &pos : nodePositions) {
        // Корректируем координаты узлов относительно масштаба карты
        QPointF scaledPos = pos * mapScaleFactor;

        // Отрисовываем узел
        scene->addEllipse(scaledPos.x() - 3, scaledPos.y() - 3, 6, 6, QPen(Qt::black), QBrush(Qt::black));
    }
}


void MainWindow::drawPath(const std::vector<int> &path)
{
    if (path.empty()) return;

    for (size_t i = 1; i < path.size(); ++i) {
        QPointF p1 = nodePositions[path[i - 1]];
        QPointF p2 = nodePositions[path[i]];
        scene->addLine(QLineF(p1, p2), QPen(Qt::blue, 3));
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (!scene || !mapItem)
        return;

    // Преобразуем координаты клика в координаты сцены
    QPointF scenePos = ui->graphicsView->mapToScene(event->pos());

    // Находим ближайший узел к месту клика
    int clickedNode = findNearestNode(scenePos);

    if (clickedNode != -1) {
        qDebug() << "Клик по точке: " << clickedNode << " (" << nodePositions[clickedNode] << ")";

        if (startNode == -1) {
            startNode = clickedNode;
        } else if (endNode == -1) {
            endNode = clickedNode;
        } else {
            startNode = clickedNode;
            endNode = -1; // Сброс конечной точки, если выбираем новую начальную
        }

        if (startNode != -1 && endNode != -1) {
            std::vector<int> path = graph.bfs(startNode, endNode);
            drawPath(path);
        }
    }
    qDebug() << "Ищем путь от" << startNode << "до" << endNode;

    std::vector<int> path = graph.bfs(startNode, endNode);

    if (path.empty()) {
        qDebug() << "Путь не найден!";
    } else {
        qDebug() << "Найден путь:" << path;
    }
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (scene && mapItem) {
        ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    }
}


int MainWindow::findNearestNode(const QPointF &pos)
{
    int nearest = -1;
    qreal minDist = std::numeric_limits<qreal>::max();
    if (nodePositions.empty()) {
        qDebug() << "Ошибка: массив nodePositions пуст!";
        return -1;
    };


    for (int i = 0; i < nodePositions.size(); ++i) {
        qreal dist = std::hypot(pos.x() - nodePositions[i].x(), pos.y() - nodePositions[i].y());
        if (dist < minDist) {
            minDist = dist;
            nearest = i;
        }
    }
    qDebug() << "Координаты клика:" << pos;
    qDebug() << "Ближайший узел:" << nearest<< "с координатами" << nodePositions[nearest];
    return nearest;
}
