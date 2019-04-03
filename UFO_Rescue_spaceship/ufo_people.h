#ifndef UFO_PEOPLE_H
#define UFO_PEOPLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QDebug>

class Ufo_people : public QObject, public QGraphicsItem
    {
        Q_OBJECT
        Q_INTERFACES(QGraphicsItem)

    public:
        explicit Ufo_people(QObject *parent = 0/*nullptr*/);// для Qt Creator 4.8.1 вставить nullpt

    signals:

    public slots:

    private slots:
        void nextFrame();   // Слот для пролистывания изображения в QPixmap

    private:
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        QRectF boundingRect() const;

    private:
        QTimer *timer;          // Таймер для пролистывания изображения в QPixmap
        QPixmap *spriteImage;   // В данный объект QPixamp будет помещён спрайт
        int currentFrame;       // Координата X, с которой начинает очередной кадр спрайта

    };

#endif // UFO_PEOPLE_H
