#include "ufo.h"

Ufo::Ufo(QObject *parent) : QObject(parent), QGraphicsItem()
{
  angle = 0;             // Задаём угол поворота графического объекта
  move = 1;              // Стартовое положение UFO в начале игры
  count_move = 0;        // счетчик нажатия кнопок
  setRotation(angle);    // Устанавилваем угол поворота графического объекта

  m_player = new QMediaPlayer(this);         // Инициализация плеера
  m_playlist = new QMediaPlaylist(m_player); // Создаем плейлист

  m_player -> setPlaylist(m_playlist);
  m_playlist -> addMedia(QUrl("qrc:/sound/polyot_korablya.wav")); // Добавляем аудио в плейер
  m_playlist -> setPlaybackMode(QMediaPlaylist::CurrentItemOnce); // Проигрываем 1 раз
}

Ufo::~Ufo()
{

}

QRectF Ufo::boundingRect() const
{
  // Ограничиваем область, в которой лежит обьект UFO
  return QRectF(-40/*x*/,-50/*y*/,100/*width*/,70/*height*/);
}

void Ufo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

// UFO move
 if(move == 0){
  painter->setPen(QPen(Qt::white,1));
  painter->setBrush(Qt::magenta);
  painter->drawEllipse(-25, 1, 50, 20);
}
 else if(move == 1){
 painter->setPen(QPen(Qt::black,1));
 painter->setBrush(Qt::blue);
 painter->drawEllipse(-25, 1, 50, 20);
}
 else if(move == 2){
 painter->setBrush(Qt::darkBlue);
 painter->drawEllipse(-25, 1, 50, 20);
}

// UFO body
 painter->setBrush(Qt::yellow);
 painter->drawEllipse(-35/*X*/, -15/*Y*/, 70/*width*/, 30/*height*/);
 painter->setBrush(Qt::green);
 painter->drawEllipse(-25, -19, 50, 20);
 painter->setBrush(Qt::red);
 painter->drawEllipse(-29, -3, 6, 5);
 painter->drawEllipse(25, -3, 6, 5);

 painter->drawEllipse(12, 3, 6, 6);
 painter->drawEllipse(-3, 5, 6, 6);
 painter->drawEllipse(-18, 3, 6, 6);


 Q_UNUSED(option);// Макрос позволяет избежать предупреждений
 Q_UNUSED(widget);// по поводу неиспользования какой-то переменной

}

void Ufo::slotGameTimer()
{
  if (GetAsyncKeyState(VK_LEFT) ||      // Проверяем, нажата ли была какая-либо из кнопок
        GetAsyncKeyState(VK_RIGHT) ||   // перед тем как считать инкрементировать счетчик mov
        GetAsyncKeyState(VK_UP) ||
        GetAsyncKeyState(VK_DOWN))
{

  m_player -> play();

  if(GetAsyncKeyState(VK_LEFT)){
  angle -= 5;         // Задаём поворот на 5 градусов влево
  setRotation(angle); // Поворачиваем объект
 }
  if(GetAsyncKeyState(VK_RIGHT)){
  angle += 5;         // Задаём поворот на 5 градусов вправо
  setRotation(angle); // Поворачиваем объект
 }
  if(GetAsyncKeyState(VK_UP)){
  setPos(mapToParent(0, -2));    // Продвигаем объект на 2 пискселя вперёд
 }
   if(GetAsyncKeyState(VK_DOWN)){
   setPos(mapToParent(0, 2));     // Продвигаем объект на 2 пискселя назад
 }

 //else  { m_player -> stop();}

 count_move++;

  if(count_move == 4){
    move = 2;
    update(QRectF(-40,-50,100,70)); // Прорисовываем область, в которой лежит обьект UFO
  }
  else if(count_move == 8){
    move = 1;
    update(QRectF(-40,-50,100,70));
  }
  else if(count_move == 12){
    move = 0;
    update(QRectF(-40,-50,100,70));
  }
  else if(count_move == 16){
    move = 1;
    update(QRectF(-40,-50,100,70));
    count_move = 0;
  }
 }

 // Проверка расположения обьекта Ufo_people перед Ufo в специально выделенном полигоне
 QList<QGraphicsItem *> foundItems = scene() -> items(QPolygonF()
                                                  << mapToScene(0, 0)
                                                  << mapToScene(-20, -20)
                                                  << mapToScene(20, -20));

 // Проверяем все элементы в полигоне, если это не Ufo высылаем сигнал в ядро игры
 foreach (QGraphicsItem *item, foundItems)
 {
  if (item == this) continue;
  emit signalCheckItem(item);
 }

 // Проверка выхода за границы поля:
 if(this->x() - 10 < -250){
    this->setX(-240);       // слева
 }
  if(this->x() + 10 > 250){
     this->setX(240);        // справа
 }
  if(this->y() - 10 < -250){
     this->setY(-240);       // сверху
 }
  if(this->y() + 10 > 250){
     this->setY(240);        // снизу
 }
}




