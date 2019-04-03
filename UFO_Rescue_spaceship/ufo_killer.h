#ifndef UFO_KILLER_H
#define UFO_KILLER_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QObject>

#include <QTimer>
#include <QDebug>
#include <QPainter>

class Ufo_killer : public QObject, public QGraphicsItem
{
   Q_OBJECT
   Q_INTERFACES(QGraphicsItem)

public:
    explicit Ufo_killer(QGraphicsItem *target, QObject *parent = 0/*nullptr*/);// для Qt Creator 4.8.1 вставить nullpt
    ~Ufo_killer();

    void pause(); // Сигнал для паузы в игре

signals:
    void signalGameOver(); // Сигнал для события конца игры

public slots:

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal angle;           // угол поворота графического обьекта
    int move;              // позиции при анимации графического обьекта
    int count_move;        // счетчик позиций для анимации графического обьекта Ufo_kiler
    QTimer *timer;         // Счетчик  тайминга движения графического обьекта
    QGraphicsItem *target; // цель Ufo_killer


private slots:
    void slotGameTimer(); // Слот таймера для обьекта UFO_Killer
};

#endif // UFO_KILLER_H
