#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QShortcut>

#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QElapsedTimer>

#include <QMediaPlaylist>
#include <QMediaPlayer>

#include <QMenu>
#include <QAction>

#include "ufo.h"
#include "ufo_killer.h"
#include "ufo_people.h"
#include "menuclass.h"

#define START_GAME 0
#define STOP_GAME  1

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0/*nullptr*/);// для Qt Creator 4.8.1 вставить nullptr
    ~MainWindow();

    void createMenu();    // 1-й метод формирования меню
    void createActions(); // добавляем 2-й метод для формирования меню

public slots:
    void aboutInfo();      // слот "О программе" (About)
    void Introduction();   // слот "Вступление(Описание)" (Introduction)

private:
    Ui::MainWindow  *ui;
    QGraphicsScene  *scene;       // объявляем графическую сцену
    Ufo             *ufo;         // обьект Ufo

    QAction         *aboutAction; // действие меню "О программе" (About)
    QAction         *introAction; // действие меню "Вступление(Описание)" (Introduction)
    QMenu           *fileMenu;    // Действие "Меню"

    QTimer          *timer;                 // таймер движения обьекта UFO на сцене
    QTimer          *timerUfoPeopleCreator; // таймер периодического создания элементов Ufo_People

    QTime            m_time;   //1х Три таймера для инициализации главного таймера-секундомера в игре
    QTimer           m_timer;  //2x
    QElapsedTimer    m_eTimer; //3x

    QList<QGraphicsItem *> ufo_peoples;     // список всех Ufo_people

    double count;                           // хранит счет обьектов Ufo_People

    Ufo_killer      *ufo_killer;            // обьект Ufo_Killer

    QShortcut       *pauseKey;              // Клавиша паузы в игре
    int gameState;                          // переменная для START/STOP_GAME (0/1)



private slots:

    void slotDeleteUfoPeople(QGraphicsItem *item);// Слот для удалания Ufo_People если Ufo его захватило

    void slotCreateUfoPeople();// Слот для создания Ufo_People по таймеру

    void on_pushButton_clicked(); // Слот для запуска игры с кнопки

    void slotGameOver(); // Слот инициализации GameOver();

    void slotPause(); // Слот инициализации паузы в игре

    void updateTime();// Слотдля инициализации главного таймера в игре
};

#endif // MAINWINDOW_H
