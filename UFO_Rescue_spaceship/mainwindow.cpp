#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
 ui -> setupUi(this);
 this -> resize(600, 640);              // Задаем размеры виджета (окна)
 this -> setFixedSize(600, 640);        // Фиксируем размеры виджета

 createActions();
 createMenu(); // Создаем основное меню с вкладками

// count = 0;

 scene = new QGraphicsScene();          // Инициализируем графическую сцену

// ufo = new Ufo();                      // Инициализируем обьект Ufo

 ui -> graphicsView -> setScene(scene);  // Устанавливаем графическую сцену в graphicsView
 ui -> graphicsView -> setRenderHint(QPainter::Antialiasing);    // Устанавливаем сглаживание
 ui -> graphicsView -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по вертикали
 ui -> graphicsView -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали

 scene -> setSceneRect(-250, -250, 500, 500); // Устанавливаем область графической сцены

// scene -> addItem(ufo); // Добавляем на сцену обьект Ufo
// ufo -> setPos(0,0);

 timer = new QTimer();
 timerUfoPeopleCreator = new QTimer();

 gameState = STOP_GAME;

 pauseKey = new QShortcut(this);
 pauseKey -> setKey(Qt::Key_Space);
 connect(pauseKey, &QShortcut::activated, this, &MainWindow::slotPause);

/*
 // Инициализируем таймер - изменяем скорость обновления сцены обьекта Ufo 
 connect(timer, &QTimer::timeout, ufo, &Ufo::slotGameTimer);
 timer -> start(1000/100);

 // Раз в секунду добавляем персонаж Ufo_people на сцену
 timerUfoPeopleCreator = new QTimer();
 connect(timerUfoPeopleCreator, &QTimer::timeout, this, &MainWindow::slotCreateUfoPeople);
 timerUfoPeopleCreator -> start(1000);

 // Сигнал от UFO в котором передаются обьекты (Ufo_people) на которые мы наткнулись
 connect(ufo, &Ufo::signalCheckItem, this, &MainWindow::slotDeleteUfoPeople);
*/

}

MainWindow::~MainWindow()
{
 delete ui;
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&Help"));
    fileMenu -> addAction(aboutAction);
    fileMenu -> addAction(introAction);
}

void MainWindow::createActions()
{
    aboutAction = new QAction(tr("&About «UFO Rescue spaceship»"), this);
    connect(aboutAction, SIGNAL(triggered()/*clicked()*//*activated()*/), this, SLOT( aboutInfo() ));

    introAction = new QAction(tr("&Introductions. Help Contents"), this);
    connect(introAction, SIGNAL(triggered()/*clicked()*//*activated()*/), this, SLOT( Introduction() ));
}

void MainWindow::aboutInfo()
{
    AboutWindow *info = new AboutWindow();
    info -> setVisible(true);
}

void MainWindow::Introduction()
{
    IntroductionWindow *info = new IntroductionWindow();
    info -> setVisible(true);
}

// Слот главного таймера-секундомера в игре
void MainWindow::updateTime()
{
  m_time=m_time.addMSecs(m_eTimer.restart());
  ui->label_2->setText(m_time.toString("mm:ss"));
}

// Получаем сигнал от  Ufo перебираем список Ufo_people и удаляем экземпляр Ufo_people.
void MainWindow::slotDeleteUfoPeople(QGraphicsItem *item)
{
   foreach(QGraphicsItem *ufopeople, ufo_peoples)
   {
     if(ufopeople == item)
      {
         scene -> removeItem(ufopeople);     // удаляем со сцены
         ufo_peoples.removeOne(ufopeople);   // удаляем из списка
         delete ufopeople;                   // вообще удаляем
         ui -> lcdNumber -> display(count++);// увеличиваем счетчик на единицу

         QMediaPlayer *m_player = new QMediaPlayer(this);                // Инициализация плеера
         QMediaPlaylist *m_playlist = new QMediaPlaylist(m_player);      // Создаем плейлист

         m_player -> setPlaylist(m_playlist);                            // Устанавливем плейлист в плейер
         m_playlist -> addMedia(QUrl("qrc:/sound/schpok.wav"));          // Добавляем аудио в плейер
         m_playlist -> setPlaybackMode(QMediaPlaylist::CurrentItemOnce); // Проигрываем 1 раз
         m_player -> play();                                             // Запускаем плейер
      }
   }
}

void MainWindow::slotCreateUfoPeople()
{
  qDebug() << "-> ufo create";
  Ufo_people *ufopeople = new Ufo_people(); // создаем обьект Ufo_people
  scene -> addItem(ufopeople);              // добавляем его на сцену в случайном порядке
  ufopeople -> setPos((qrand() % (251))*((qrand()%2 == 1)?1 : -1),
                      (qrand() % (251))*((qrand()%2 == 1)?1 : -1));
  ufopeople -> setZValue(-1);               // Помещаем Ufo_people ниже Ufo
  ufo_peoples.append(ufopeople);            // и добавляем UfoPeople в список
}


void MainWindow::on_pushButton_clicked()
{
  qDebug() << "-> Start the Game...";

  count = 0;
  ui -> lcdNumber -> display(count);

  ufo = new Ufo();                 // инициализируем обьект Ufo
  scene -> addItem(ufo);           // добавляем Ufo на сцену
  ufo -> setPos(0,0);              // устанавливаем Ufo в центр сцены

// запускаем основной таймер-секундомер
  m_time = QTime(0,0);
  connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateTime()));
  m_timer.start(1000);
  m_eTimer.start();

  // инициализируем обьект Ufo_killer
  ufo_killer = new Ufo_killer(ufo);

  // добавляем Ufo_killer на сцену
  scene -> addItem(ufo_killer);
  ufo_killer -> setPos(240, 240);

  // Подключаем сигнал от Ufo_killer на проверку состояния Game_Over
  connect(ufo_killer, &Ufo_killer::signalGameOver, this, &MainWindow::slotGameOver);

  // Вызываем слот обработки таймера Ufo
  connect(timer, &QTimer::timeout, ufo, &Ufo::slotGameTimer);
  timer -> start(1000 / 100);

  // Подключаем сигнал на создание Ufo_people в игре
  connect(timerUfoPeopleCreator, &QTimer::timeout, this, &MainWindow::slotCreateUfoPeople);
  timerUfoPeopleCreator -> start(1000);

  // Подключаем сигнал от Ufo, в котором передаются обьекты, на которые наткнулось Ufo
  connect(ufo, &Ufo::signalCheckItem, this, &MainWindow::slotDeleteUfoPeople);
  ui -> pushButton -> setEnabled(false);

  gameState = START_GAME;
}

void MainWindow::slotGameOver()
{
 qDebug() << "-> Game Over!...";

 timer -> stop();
 timerUfoPeopleCreator -> stop();// Отключаем все таймеры если игра окончена
 m_timer.stop();

 QMediaPlayer *m_player = new QMediaPlayer(this);                // Инициализация плеера
 QMediaPlaylist *m_playlist = new QMediaPlaylist(m_player);      // Создаем плейлист

 m_player -> setPlaylist(m_playlist);                            // Устанавливем плейлист в плейер
 m_playlist -> addMedia(QUrl("qrc:/sound/razgovor_marsian.wav")); // Добавляем аудио в плейер
 m_playlist -> setPlaybackMode(QMediaPlaylist::CurrentItemOnce); // Проигрываем 1 раз
 m_player -> play();                                             // Запускаем плейер

 QMessageBox::warning(this, "Game Over!!!", "Тебя сожрали, чувак! YOU're DEAD!!!");

 // Отключаем сигналы от слотов
 disconnect(timerUfoPeopleCreator, &QTimer::timeout, this, &MainWindow::slotCreateUfoPeople);
 disconnect(ufo, &Ufo::signalCheckItem, this, &MainWindow::slotDeleteUfoPeople);
 disconnect(ufo_killer, &Ufo_killer::signalGameOver, this, &MainWindow::slotGameOver);

 // Удаляем все обьекты со сцены
 ufo_killer -> deleteLater();
 ufo -> deleteLater();
 m_player -> stop();

 foreach (QGraphicsItem *ufopeople, ufo_peoples)
 {
  scene -> removeItem(ufopeople);     // удаляем со сцены
  ufo_peoples.removeOne(ufopeople);   // удаляем из списка
  delete ufopeople;                   // вообще удаляем
 }

 // Активируем кнопку старта игры
 ui -> pushButton -> setEnabled(true);

 gameState = STOP_GAME;
}

void MainWindow::slotPause()
{
  qDebug() << "-> Pause...";

  if(gameState == START_GAME)
  {
    if(timer -> isActive())
    {
      timer -> stop();
      m_timer.stop();
      timerUfoPeopleCreator -> stop();
      ufo_killer -> pause();
    }
    else
    {
      timer -> start(1000/100);
      m_timer.start(1000);
      m_eTimer.start();
      timerUfoPeopleCreator -> start(1000);
      ufo_killer -> pause();
    }
  }
}











