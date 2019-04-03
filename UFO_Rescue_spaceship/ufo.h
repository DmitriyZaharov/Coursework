#ifndef UFO_H
#define UFO_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>

#include <QMediaPlaylist>
#include <QMediaPlayer>

#include <windows.h> //для проверки состояния клавиш

// QGraphicsItem не наследует QObject, соотв. не может участвовать
// в системе сигналов-слотов, нужно сделать его наследником QObject
class Ufo : public QObject, public QGraphicsItem
{
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)

public:
  explicit Ufo(QObject *parent = 0 /*nullptr*/);// для Qt Creator 4.8.1 вставить nullpt
  ~Ufo();

signals:
   void signalCheckItem(QGraphicsItem *item); //Момент, когда обьект Ufo достигнет Ufo_people

public slots:
  void slotGameTimer(); // Слот - таймер, который отвечает за обработку перемещения Ufo

protected:
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
   qreal angle;     // Угол поворота графического объекта (Ufo)
   int move;        // номер анимации при движении обьекта
   int count_move;  // счетчик нажатия кнопок

   QMediaPlayer      *m_player;
   QMediaPlaylist    *m_playlist;
};

#endif //UFO_H
