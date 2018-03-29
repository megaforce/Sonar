#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <Qserialport>
#include <QSerialPortInfo>
#include <QDebug>
#include <QLinkedList>
#include <QMessageBox>
#include <QTimer>
#include <Qstring>
#include <QList>

struct point
{
    short angle;
    short distance;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QList<point> points;
    Ui::MainWindow *ui;
    QSerialPort *arduino;
    static const quint16 arduino_mega_vendor_id = 9025;
    static const quint16 arduino_mega_product_id = 66;
    QString arduino_port_name;
    bool arduino_is_available;
    QTimer *timer;
    void getSerialData();

protected:
  void paintEvent(QPaintEvent *e);

private slots:
  void update_screen();

};

#endif // MAINWINDOW_H
