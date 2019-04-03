#include "ufo_people.h"

Ufo_people::Ufo_people(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    qDebug() << "-> Image Ufo_people";
    currentFrame = 0;   // Устанавливаем координату текущего кадра спрайта
    spriteImage = new QPixmap(":gargant-move-wounded.png"); // Загружаем изображение спрайта в QPixmap

    timer = new QTimer();   // Создаём таймер для анимации спрайта

    // Подключаем сигнал от таймера к слоту перелистывания кадров спрайта
    connect(timer, &QTimer::timeout, this, &Ufo_people::nextFrame);

    timer->start(100);   // Запускаем спрайт на генерацию сигнала с периодичность 100 мс
}

QRectF Ufo_people::boundingRect() const
{
    return QRectF(-32, -32, 64, 64);
}

void Ufo_people::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /* В отрисовщике графического объекта отрисовываем спрайт
     * Первых два аргумента - это координат X и Y куда помещается QPixmap
     * Третий аргумент - это указатель на QPixmap
     * 4 и 5 аргументы - Координаты в В изображении QPixmap, откуда будет отображаться изображение
     * Задавая координату X с помощью перемнной currentFrame мы будем как бы передвигать камеру
     * по спрайту
     * и последние два аргумента - это ширина и высота отображаем части изображение, то есть кадра
     * */
    painter->drawPixmap(-32, -32, *spriteImage, currentFrame, 0, 64, 64);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Ufo_people::nextFrame()
{
    /* По сигналу от таймера передвигаем на 64 пикселя точку отрисовки
     * Если currentFrame = 512 то обнуляем его, поскольку размер sprite sheet 512 пикселей на 64
     * */
    currentFrame += 64;
    if (currentFrame >= 512 ) currentFrame = 0;
    this->update(-32, -32, 64, 64); // и перерисовываем графический объект с новым кадром спрайта
}














