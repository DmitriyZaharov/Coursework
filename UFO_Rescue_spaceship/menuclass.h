#ifndef MENUCLASS_H
#define MENUCLASS_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QMediaPlaylist>
#include <QMediaPlayer>

class AboutWindow : public QWidget // Класс для окна About
{
    Q_OBJECT
public:
    explicit AboutWindow(QWidget *parent = 0/*nullptr*/);// для Qt Creator 4.8.1 вставить nullptr

signals:
    void activated(int i);

public slots:

private:
    QPixmap *aboutWindowPix;
    QLabel *aboutWindowLabel; // 2 Обьекта класса QLable для текста и картинки
    QLabel *aboutWindowPixLabel;
};

class IntroductionWindow : public QWidget // Класс для окна Introduction
{
    Q_OBJECT
public:
    explicit IntroductionWindow(QWidget *parent = 0/*nullptr*/);// для Qt Creator 4.8.1 вставить nullptr

signals:
    void activated(int i);

public slots:

private:
    QPixmap *introductionWindowPix;
    QLabel *introductionWindowLabel; // 2 Обьекта класса QLable для текста и картинки
    QLabel *introductionWindowPixLabel;
};
#endif // MENUCLASS_H
