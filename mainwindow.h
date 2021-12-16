#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trem.h"

#include <QSemaphore>

static QSemaphore regiao[7];//semaforos das regioes criticas
static std::array<int, 5> estado{0, 0, 0, 0, 0};//array que guarda os estados de cada trem
static QSemaphore mutex;//mutex para controlar a mudanca de estado
#include <QSlider>
#include <QAbstractSlider>


namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void updateInterface(int,int,int);

private slots:
    void on_horizontalSlider_1_sliderReleased();

    void on_horizontalSlider_2_sliderReleased();

    void on_horizontalSlider_3_sliderReleased();

    void on_horizontalSlider_4_sliderReleased();

    void on_horizontalSlider_5_sliderReleased();

private:
    Ui::MainWindow *ui;



    Trem *trem1;
    Trem *trem2;
    Trem *trem3;
    Trem *trem4;
    Trem *trem5;

};

#endif // MAINWINDOW_H
