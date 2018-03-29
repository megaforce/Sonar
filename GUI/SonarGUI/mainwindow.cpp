#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setStyleSheet("background-color: black;");
    arduino_is_available = false;
    arduino_port_name = "";

    arduino = new QSerialPort;

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduino_mega_vendor_id){
                if(serialPortInfo.productIdentifier() == arduino_mega_product_id){
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                }
            }
        }
    }

    if(arduino_is_available){

        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::ReadOnly);
        arduino->setBaudRate(QSerialPort::Baud4800);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);

    }
    else{

        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_screen()));
    timer->start(340);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getSerialData()
{
    QByteArray serialDataRecieved;
    serialDataRecieved=arduino->readAll();
    if(serialDataRecieved.size() <5)
    serialDataRecieved.clear();
    else
    {
    QString sDR;
    QStringList data;
    sDR = serialDataRecieved;
    data = sDR.split("|||");
    data.removeAll("|");
        if (data.size() == 2 and data[0].size() < 4 )
        {
        points.append(point{data[0].toInt(),data[1].toInt()});
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPen pen( Qt::green );
    pen.setWidth(5);
    painter.setPen(pen);

}

void MainWindow::update_screen()
{
 getSerialData();
 update();
}
