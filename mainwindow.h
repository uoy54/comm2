#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>  // Добавил для работы с картинкой
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *mapItem = nullptr;  // Добавлено, чтобы избежать ошибки
    Graph graph;
    QVector<QPointF> nodePositions;

    int startNode = -1;
    int endNode = -1;

    void drawMap();
    void drawNodes();
    void drawPath(const std::vector<int>& path);
    int findNearestNode(const QPointF& pos);
    double mapScaleFactor = 1.0;
    QPixmap mapPixmap;
    void setupScene();
 };

#endif // MAINWINDOW_H
