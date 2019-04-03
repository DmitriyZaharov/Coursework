#include "ufo_killer.h"
#include "math.h"

static const double Pi = 3.14159265358979;
static double TwoPi = 2.0*Pi;

static qreal normalizeAngle(qreal angle)
{
 while (angle < 0) angle += TwoPi;
 while (angle > TwoPi) angle -= TwoPi;
 return angle;
}

Ufo_killer::Ufo_killer(QGraphicsItem *target, QObject *parent): QObject(parent), QGraphicsItem()
{
 angle = 0;          // Задаем угол поворота обьекта Ufo_Killer
 move = 0;           // Стартовое положение обьекта
 count_move = 0;     // Счетчик отсчетов при нажатой кнопке
 setRotation(angle); // Угол поворота обьекта Ufo_killer

 this -> target = target; // Устанавливаем цель для Ufo_Killer

 timer = new QTimer();

 // Подключаем сигнал таймера к обьекту Ufo_killer
 connect(timer, &QTimer::timeout, this, &Ufo_killer::slotGameTimer);
 timer -> start(16);
}

Ufo_killer::~Ufo_killer()
{

}

QRectF Ufo_killer::boundingRect() const
{
  return QRectF(-50, -35, 100, 70);// Ограничиваем область, в которой лежит обьект UFO_Killer
}

void Ufo_killer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
// Ufo_killer move
 if(move == 0){
//qDebug() << "-> mov=0";
  painter->setPen(QPen(Qt::black,2));
//"hand"
  painter->drawLine(-45,0,-30,0);
//painter->drawLine(-45,-7,-30,0);
//painter->drawLine(-45,7,-30,0);

//painter->drawEllipse(-48/*x*/, -11/*y*/, 6/*w*/, 6/*h*/);
  painter->setBrush(Qt::red);
  painter->drawEllipse(-50/*x*/, -4/*y*/, 6/*w*/, 6/*h*/);
//painter->drawEllipse(-48/*x*/, 4/*y*/, 6/*w*/, 6/*h*/);

  painter->drawLine(45,0,30,0);
//painter->drawLine(45,-7,30,0);
//painter->drawLine(45,7,30,0);

//painter->drawEllipse(45/*x*/, -11/*y*/, 6/*w*/, 6/*h*/);
  painter->setBrush(Qt::red);
  painter->drawEllipse(45/*x*/, -4/*y*/, 6/*w*/, 6/*h*/);
//painter->drawEllipse(45/*x*/, 4/*y*/, 6/*w*/, 6/*h*/);

//"muhi"
  painter->setBrush(Qt::darkYellow);
  painter->drawEllipse(-1/*x*/, -36/*y*/, 6/*w*/, 6/*h*/);//1
  painter->setBrush(Qt::yellow);
  painter->drawEllipse(-14/*x*/, -35/*y*/, 6/*w*/, 6/*h*/);//2
  painter->setBrush(Qt::red);
  painter->drawEllipse(-27/*x*/, -30/*y*/, 6/*w*/, 6/*h*/);//3
//painter->drawEllipse(-36/*x*/, -20/*y*/, 6/*w*/, 6/*h*/);//4
//painter->drawEllipse(10/*x*/, -35/*y*/, 6/*w*/, 6/*h*/);//15
//painter->drawEllipse(20/*x*/, -30/*y*/, 6/*w*/, 6/*h*/);//14
//painter->drawEllipse(30/*x*/, -20/*y*/, 6/*w*/, 6/*h*/);//13

//painter->drawEllipse(-1/*x*/, 29/*y*/, 6/*w*/, 6/*h*/);//9
//painter->drawEllipse(-14/*x*/, 28/*y*/, 6/*w*/, 6/*h*/);//7
//painter->drawEllipse(-27/*x*/, 24/*y*/, 6/*w*/, 6/*h*/);//6
//painter->drawEllipse(-37/*x*/, 16/*y*/, 6/*w*/, 6/*h*/);//5
//painter->drawEllipse(10/*x*/, 28/*y*/, 6/*w*/, 6/*h*/);//10
//painter->drawEllipse(20/*x*/, 24/*y*/, 6/*w*/, 6/*h*/);//11
//painter->drawEllipse(30/*x*/, 15/*y*/, 6/*w*/, 6/*h*/);//12
 }
 else if(move == 1){
//qDebug() << "-> move=1";
 painter->setPen(QPen(Qt::black,2));
//"hand"
//painter->drawLine(-45,0,-30,0);
  painter->drawLine(-45,-7,-30,0);
//painter->drawLine(-45,7,-30,0);
  painter->setBrush(Qt::yellow);
  painter->drawEllipse(-50/*x*/, -11/*y*/, 6/*w*/, 6/*h*/);
//painter->drawEllipse(-50/*x*/, -4/*y*/, 6/*w*/, 6/*h*/);
//painter->drawEllipse(-50/*x*/, 4/*y*/, 6/*w*/, 6/*h*/);

//painter->drawLine(45,0,30,0);
  painter->drawLine(45,-7,30,0);
//painter->drawLine(45,7,30,0);

  painter->setBrush(Qt::yellow);
  painter->drawEllipse(45/*x*/, -11/*y*/, 6/*w*/, 6/*h*/);
//painter->drawEllipse(45/*x*/, -4/*y*/, 6/*w*/, 6/*h*/);
//painter->drawEllipse(45/*x*/, 4/*y*/, 6/*w*/, 6/*h*/);

//"muhi"

//painter->drawEllipse(-1/*x*/, -36/*y*/, 6/*w*/, 6/*h*/);//1
//painter->drawEllipse(-14/*x*/, -35/*y*/, 6/*w*/, 6/*h*/);//2
//painter->drawEllipse(-27/*x*/, -30/*y*/, 6/*w*/, 6/*h*/);//3

  painter->setBrush(Qt::darkYellow);
  painter->drawEllipse(-36/*x*/, -20/*y*/, 6/*w*/, 6/*h*/);//4

//painter->drawEllipse(10/*x*/, -35/*y*/, 6/*w*/, 6/*h*/);//15
//painter->drawEllipse(20/*x*/, -30/*y*/, 6/*w*/, 6/*h*/);//14
//painter->drawEllipse(30/*x*/, -20/*y*/, 6/*w*/, 6/*h*/);//13

//painter->drawEllipse(-1/*x*/, 29/*y*/, 6/*w*/, 6/*h*/);//9
//painter->drawEllipse(-14/*x*/, 28/*y*/, 6/*w*/, 6/*h*/);//7

  painter->setBrush(Qt::red);
  painter->drawEllipse(-27/*x*/, 24/*y*/, 6/*w*/, 6/*h*/);//6

  painter->setBrush(Qt::yellow);
  painter->drawEllipse(-37/*x*/, 16/*y*/, 6/*w*/, 6/*h*/);//5

//painter->drawEllipse(10/*x*/, 28/*y*/, 6/*w*/, 6/*h*/);//10
//painter->drawEllipse(20/*x*/, 24/*y*/, 6/*w*/, 6/*h*/);//11
//painter->drawEllipse(30/*x*/, 15/*y*/, 6/*w*/, 6/*h*/);//12
 }
 else if(move== 2){
//qDebug() << "-> move=2";
 painter->setPen(QPen(Qt::black,2));
//"hand"
//painter->drawLine(-45,0,-30,0);
//painter->drawLine(-45,-7,-30,0);
  painter->drawLine(-45,7,-30,0);

//painter->drawEllipse(-50/*x*/, -11/*y*/, 6/*w*/, 6/*h*/);
//painter->drawEllipse(-50/*x*/, -4/*y*/, 6/*w*/, 6/*h*/);
  painter->setBrush(Qt::blue);
  painter->drawEllipse(-50/*x*/, 4/*y*/, 6/*w*/, 6/*h*/);

//painter->drawLine(45,0,30,0);
//painter->drawLine(45,-7,30,0);
  painter->drawLine(45,7,30,0);

// painter->drawEllipse(45/*x*/, -11/*y*/, 6/*w*/, 6/*h*/);
// painter->drawEllipse(45/*x*/, -4/*y*/, 6/*w*/, 6/*h*/);
   painter->setBrush(Qt::blue);
   painter->drawEllipse(45/*x*/, 4/*y*/, 6/*w*/, 6/*h*/);
//"muhi"
//painter->drawEllipse(-1/*x*/, -36/*y*/, 6/*w*/, 6/*h*/);//1
//painter->drawEllipse(-14/*x*/, -35/*y*/, 6/*w*/, 6/*h*/);//2
//painter->drawEllipse(-27/*x*/, -30/*y*/, 6/*w*/, 6/*h*/);//3
//painter->drawEllipse(-36/*x*/, -20/*y*/, 6/*w*/, 6/*h*/);//4
//painter->drawEllipse(10/*x*/, -35/*y*/, 6/*w*/, 6/*h*/);//14
//painter->drawEllipse(20/*x*/, -30/*y*/, 6/*w*/, 6/*h*/);//13
//painter->drawEllipse(30/*x*/, -20/*y*/, 6/*w*/, 6/*h*/);//12

  painter->setBrush(Qt::yellow);
  painter->drawEllipse(-1/*x*/, 29/*y*/, 6/*w*/, 6/*h*/);//8
  painter->setBrush(Qt::darkYellow);
  painter->drawEllipse(-14/*x*/, 28/*y*/, 6/*w*/, 6/*h*/);//7

//painter->drawEllipse(-27/*x*/, 24/*y*/, 6/*w*/, 6/*h*/);//6
//painter->drawEllipse(-37/*x*/, 16/*y*/, 6/*w*/, 6/*h*/);//5
  painter->setBrush(Qt::red);
  painter->drawEllipse(10/*x*/, 28/*y*/, 6/*w*/, 6/*h*/);//9

//painter->drawEllipse(20/*x*/, 24/*y*/, 6/*w*/, 6/*h*/);//10
//painter->drawEllipse(30/*x*/, 15/*y*/, 6/*w*/, 6/*h*/);//11
 }
  else if(move == 3){
//qDebug() << "-> move=3";
  painter->setPen(QPen(Qt::black,2));
//"hand"
  painter->drawLine(-45,0,-30,0);
//painter->drawLine(-45,-7,-30,0);
//painter->drawLine(-45,7,-30,0);

//painter->drawEllipse(-50/*x*/, -11/*y*/, 6/*w*/, 6/*h*/);
  painter->setBrush(Qt::blue);
  painter->drawEllipse(-50/*x*/, -4/*y*/, 6/*w*/, 6/*h*/);
//painter->drawEllipse(-50/*x*/, 4/*y*/, 6/*w*/, 6/*h*/);

  painter->drawLine(45,0,30,0);
//painter->drawLine(45,-7,30,0);
//painter->drawLine(45,7,30,0);

//painter->drawEllipse(45/*x*/, -11/*y*/, 6/*w*/, 6/*h*/);
  painter->setBrush(Qt::blue);
  painter->drawEllipse(45/*x*/, -4/*y*/, 6/*w*/, 6/*h*/);
//painter->drawEllipse(45/*x*/, 4/*y*/, 6/*w*/, 6/*h*/);

//"muhi"

//painter->drawEllipse(-1/*x*/, -36/*y*/, 6/*w*/, 6/*h*/);//1
//painter->drawEllipse(-14/*x*/, -35/*y*/, 6/*w*/, 6/*h*/);//2
//painter->drawEllipse(-27/*x*/, -30/*y*/, 6/*w*/, 6/*h*/);//3
//painter->drawEllipse(-36/*x*/, -20/*y*/, 6/*w*/, 6/*h*/);//4
//painter->drawEllipse(10/*x*/, -35/*y*/, 6/*w*/, 6/*h*/);//14
//painter->drawEllipse(20/*x*/, -30/*y*/, 6/*w*/, 6/*h*/);//13

  painter->setBrush(Qt::red);
  painter->drawEllipse(30/*x*/, -20/*y*/, 6/*w*/, 6/*h*/);//12

//painter->drawEllipse(-1/*x*/, 29/*y*/, 6/*w*/, 6/*h*/);//8
//painter->drawEllipse(-14/*x*/, 28/*y*/, 6/*w*/, 6/*h*/);//7
//painter->drawEllipse(-27/*x*/, 24/*y*/, 6/*w*/, 6/*h*/);//6
//painter->drawEllipse(-37/*x*/, 16/*y*/, 6/*w*/, 6/*h*/);//5

//painter->drawEllipse(10/*x*/, 28/*y*/, 6/*w*/, 6/*h*/);//9

 painter->setBrush(Qt::darkYellow);
 painter->drawEllipse(20/*x*/, 24/*y*/, 6/*w*/, 6/*h*/);//10

 painter->setBrush(Qt::yellow);
 painter->drawEllipse(30/*x*/, 15/*y*/, 6/*w*/, 6/*h*/);//11
 }

 else if(move == 4){
//qDebug() << "-> move=4";
 painter->setPen(QPen(Qt::black,2));
//"hand"
//painter->drawLine(-45,0,-30,0);
  painter->drawLine(-45,-7,-30,0);
//painter->drawLine(-45,7,-30,0);

  painter->setBrush(Qt::blue);
  painter->drawEllipse(-50/*x*/, -11/*y*/, 6/*w*/, 6/*h*/);
//painter->drawEllipse(-50/*x*/, -4/*y*/, 6/*w*/, 6/*h*/);
//painter->drawEllipse(-50/*x*/, 4/*y*/, 6/*w*/, 6/*h*/);

//painter->drawLine(45,0,30,0);
  painter->drawLine(45,-7,30,0);
//painter->drawLine(45,7,30,0);

  painter->setBrush(Qt::blue);
  painter->drawEllipse(45/*x*/, -11/*y*/, 6/*w*/, 6/*h*/);
//painter->drawEllipse(45/*x*/, -4/*y*/, 6/*w*/, 6/*h*/);
//painter->drawEllipse(45/*x*/, 4/*y*/, 6/*w*/, 6/*h*/);

//"muhi"
  painter->setBrush(Qt::red);
  painter->drawEllipse(-1/*x*/, -36/*y*/, 6/*w*/, 6/*h*/);//1

//painter->drawEllipse(-14/*x*/, -35/*y*/, 6/*w*/, 6/*h*/);//2
//painter->drawEllipse(-27/*x*/, -30/*y*/, 6/*w*/, 6/*h*/);//3
//painter->drawEllipse(-36/*x*/, -20/*y*/, 6/*w*/, 6/*h*/);//4

 painter->setBrush(Qt::darkYellow);
 painter->drawEllipse(10/*x*/, -35/*y*/, 6/*w*/, 6/*h*/);//14
 painter->setBrush(Qt::yellow);
 painter->drawEllipse(20/*x*/, -30/*y*/, 6/*w*/, 6/*h*/);//13

//painter->drawEllipse(30/*x*/, -20/*y*/, 6/*w*/, 6/*h*/);//12
//painter->drawEllipse(-1/*x*/, 29/*y*/, 6/*w*/, 6/*h*/);//8
//painter->drawEllipse(-14/*x*/, 28/*y*/, 6/*w*/, 6/*h*/);//7
//painter->drawEllipse(-27/*x*/, 24/*y*/, 6/*w*/, 6/*h*/);//6
//painter->drawEllipse(-37/*x*/, 16/*y*/, 6/*w*/, 6/*h*/);//5
//painter->drawEllipse(10/*x*/, 28/*y*/, 6/*w*/, 6/*h*/);//9
//painter->drawEllipse(20/*x*/, 24/*y*/, 6/*w*/, 6/*h*/);//10
//painter->drawEllipse(30/*x*/, 15/*y*/, 6/*w*/, 6/*h*/);//11
 }
//Ufo_killer body
  painter->setPen(QPen(Qt::black,2));
  painter->setBrush(Qt::lightGray);
  painter->drawEllipse(-30/*-15*/, -25/*-20*/, 60/*30*вправо*/, 50/*50 вниз*/);

  painter->setBrush(Qt::black);
  painter->drawEllipse(-23/*-15*/, -4/*-20*/, 45/*30*вправо*/, 20/*50 вниз*/);

  painter->setBrush(Qt::red);
  painter->drawEllipse(9/*-15*/, -20, 9/*30*вправо*/, 14/*50 вниз*/);
  painter->drawEllipse(-15/*-15*/,-20, 9/*30*вправо*/, 14/*50 вниз*/);

  painter->setBrush(Qt::white);
  painter->drawEllipse(-11/*-15*/, -17, 6/*30*вправо*/, 6/*50 вниз*/);
  painter->drawEllipse(8/*-15*/, -17, 6/*30*вправо*/, 6/*50 вниз*/);

  QPolygon polygon;
  polygon << QPoint(5, -4) << QPoint(-4, -4) << QPoint(-4, 5);
  painter->setBrush(Qt::white);
  painter->drawPolygon(polygon);

  polygon << QPoint(5, -4) << QPoint(6, 15) << QPoint(-3, 15);
  painter->setBrush(Qt::white);
  painter->drawPolygon(polygon);

  Q_UNUSED(option);
  Q_UNUSED(widget);
}

void Ufo_killer::slotGameTimer()
{
  // Определяем расстояние до обьекта Ufo
  QLineF lineToTarget(QPointF(0,0), mapFromItem(target, 0, 0));
  // Угол поворота в направлении к Ufo
  qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());

  if (lineToTarget.dy() < 0) angleToTarget = TwoPi - angleToTarget;
  angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi/2);

  if (angleToTarget > 0 && angleToTarget < Pi)
  {  // UFO находится слева от UFO_KILLER
     // поворачиваемся влево
      if(angleToTarget > Pi/5)
      {
          angle = -15;
      }
      else if(angleToTarget > Pi/10)
      {
          angle = -5;
      }
      else
      {
          angle = -1;
      }
  }
  else if (angleToTarget <= TwoPi && angleToTarget > (TwoPi - Pi))
  { // UFO находится справа от UFO_KILLER
    // поворачиваемся вправо
      if (angleToTarget < (TwoPi - Pi/5))
      {
          angle = 15;
      }
      else if (angleToTarget < (TwoPi - Pi/10))
      {
          angle = 5;
      }
      else
      {
          angle = 1;
      }
  }
  else if(angleToTarget == 0.0)
  {
   angle = 0;
  }

  setRotation(rotation() + angle);

  if(lineToTarget.length() >= 40)
  {
    setPos(mapToParent(0, -(qrand() % ((4+1) - 1) + 1)));

    count_move++;

    if(count_move == 4){
       move = 0;
       update(QRectF(-50,-35,100,70));// Прорисовываем область, в которой лежит UFO
    }
    else if(count_move == 8){
       move = 1;
       update(QRectF(-50,-35,100,70));
    }
    else if(count_move == 12){
       move = 2;
       update(QRectF(-50,-35,100,70));
    }
    else if(count_move == 16){
       move = 3;
       update(QRectF(-50,-35,100,70));
    }
    else if(count_move == 20){
       move = 4;
       update(QRectF(-50,-35,100,70));
       count_move = 0;
    }
  }

//Выделяем область перед Ufo_killer где будем искать элементы Ufo
 QList<QGraphicsItem *> foundItems = scene( )-> items(QPolygonF()
                                                    << mapToScene(0, 0)
                                                    << mapToScene(-8, -8)
                                                    << mapToScene(8, -8));

//Проверяем все элементы
 foreach (QGraphicsItem *item, foundItems)
 {
  if(item == this) continue;
  if(item == target) emit signalGameOver();//Если в область обьекта Ufo_Killer попался Ufo - Конец игре
 }

 //Проверка выхода за границы поля обьекта Ufo_Killer
 if(this -> x() -10 < -250)
 {
    this -> setX(-240);
 }
 if(this -> x() +10 > 250)
 {
    this -> setX(240);
 }
 if(this -> y() - 10 < -250)
 {
     this -> setY(-240);
 }
 if(this -> y() + 10 < -250)
 {
     this -> setY(-240);
 }
}

void Ufo_killer::pause()
{
  if(timer -> isActive()) {timer -> stop();}
  else {timer -> start(15);}
}


































