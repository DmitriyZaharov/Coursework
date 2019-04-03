#include "menuclass.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QWidget(parent)
{
  qDebug() << "-> ABOUT_WINDOW";
  this->setWindowTitle("About «UFO Rescue spaceship»");
  aboutWindowLabel = new QLabel("© UFO Rescue spaceship (Version: 1.0.0)\n"
                                "© 2019 All rights reserved. Все права защищены :)\n"
                                "Creator: Zaharov Dmitriy\n\n"
                                "Данная программа создана в\n"
                                "QT Creator 3.0.1, основан на Qt 5.2.1 (MSVC 2010, 32 бита).\n"
                                "Кроме этого, она собиралась и тестировалась в\n"
                                "QT Creator 4.8.1, основан на Qt 5.12.0 (MSVC 2015, 32 бита).");
  aboutWindowPix = new QPixmap();
  aboutWindowPix->load(":qt2.jpg");
  aboutWindowPixLabel = new QLabel();
  aboutWindowPixLabel->setPixmap(*aboutWindowPix);
  QVBoxLayout *aboutWindowLayout = new QVBoxLayout();
  aboutWindowLayout->addWidget(aboutWindowPixLabel);
  aboutWindowLayout->addWidget(aboutWindowLabel);
  this->setLayout(aboutWindowLayout);
  this->resize(300,200);
}

IntroductionWindow::IntroductionWindow(QWidget *parent) :
    QWidget(parent)
{
  qDebug() << "-> INTRODUCTION_WINDOW";
  this->setWindowTitle("Introductions. Help Contents");
  introductionWindowLabel = new QLabel("© UFO Rescue spaceship (Version: 1.0.0)\n\n"
                                       "1. Введение.\n"
                                       "В «UFO Rescue spaceship» вы играете роль командира группы «Феникс» -\n"
                                       "злитного военного подразделения. В тактическом задании вы занимаетесь\n"
                                       "сбором инопланетных существ для дальнейшего исследования.\n\n"
                                       "2. «Биомасса».\n"
                                       "«Биомасса» - это запутанная, переплетенная масса ложноножек, отростков\n"
                                       "и ветвлений, определенно неземного происхождения и вида. Биомасса очень\n"
                                       "опасна. Её постоянное передвижение трудно сдержать, она уничтожает все\n"
                                       "космические корабли на своем пути.\n\n"
                                       "3. Как играть.\n"
                                       "Для начала игры необходимо нажать кнопку «START». Управлять космическим\n"
                                       "кораблем можно клавишами со стрелками на клавиатуре. При нажатии кнопки\n"
                                       "«вперед» или «назад» космический корабль будет двигаться вперед или назад.\n"
                                       "При нажатии кнопки «влево» или «вправо» - будет разворачиваться по часовой\n"
                                       "или против часовой стрелки.Для инициализации паузы в игре необходимо\n"
                                       "нажать на клавиатуре кнопку «пробел».\n"
                                       "При сближении космического корабля с движущимся инопланетным существом -\n"
                                       "оно исчезает, и счетчик «ALIENS SAVED» увеличивается на еденицу. При\n"
                                       "сближении «Биомассы» с космическим кораблем - игра завершается и счетчик\n"
                                       "«ALIENS SAVED» обнуляется.\n"
                                       "Задача игры: собрать как можно больше инопланетных существ и при этом\n"
                                       "не угодить в лапы «Биомассе».");
  introductionWindowPix = new QPixmap();
  introductionWindowPix->load(":ufo_people.jpg");
  introductionWindowPixLabel = new QLabel();
  introductionWindowPixLabel->setPixmap(*introductionWindowPix);
  QVBoxLayout *introductionWindowLayout = new QVBoxLayout();
  introductionWindowLayout->addWidget(introductionWindowPixLabel);
  introductionWindowLayout->addWidget(introductionWindowLabel);
  this->setLayout(introductionWindowLayout);
  this->resize(300,200); // Задаем размеры виджета (окна)
//  this->setFixedSize(440, 600);

  QMediaPlayer *m_player = new QMediaPlayer(this);                // Инициализация плеера
  QMediaPlaylist *m_playlist = new QMediaPlaylist(m_player);      // Создаем плейлист

  m_player -> setPlaylist(m_playlist);                            // Устанавливем плейлист в плейер
  m_playlist -> addMedia(QUrl("qrc:/sound/zvukovoj-effekt.wav")); // Добавляем аудио в плейер
  m_playlist -> setPlaybackMode(QMediaPlaylist::CurrentItemOnce); // Проигрываем 1 раз
  m_player -> play();                                             // Запускаем плейер
}
