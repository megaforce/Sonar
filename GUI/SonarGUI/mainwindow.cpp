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
    this->setFixedSize(503,241);
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
    qDebug()<<data;
    ui->label->setText("Angle: "+data[0]);
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
    pen.setWidth(4);
    painter.setPen(pen);

    painter.drawLine(20,240,500,240);
    for (int i = 240; i > 0; i = i - 120)
    painter.drawLine(240,240,i,20);
    for (int i = 240; i > 0; i = i - 120)
    painter.drawLine(240,240,0,i);

    for (int i = 240; i < 480; i = i + 120)
    painter.drawLine(240,240,i,20);
    for (int i = 240; i > 0; i = i - 120)
    painter.drawLine(240,240,500,i);

    QPoint center(240,240);
    for (int i = 0; i < 240; i = i + 40)
    painter.drawEllipse(center,i,i);
}

void MainWindow::update_screen()
{
 getSerialData();
 update();
}
