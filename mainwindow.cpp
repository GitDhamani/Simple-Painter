//mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <QMenu>
#include <QMimeData>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Set the Background colour of our window to white
    QPalette pal;
    pal.setColor(QPalette::Window, Qt::white);
    setPalette(pal);

    //Set up the Image format, size, and colour.
    QImage newImage(size(), QImage::Format_RGB32);
    newImage.fill(qRgb(255,255,255));
    image = newImage;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawLineTo(QPoint currentpos)
{
    QPainter painter(&image);
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawLine(startpos, currentpos);
    startpos = currentpos;
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
      if(event->button()==Qt::LeftButton)
      drawon = true;
      startpos = event->pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    drawon = false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (drawon)
    {
       endpos = event->pos();
       drawLineTo(endpos);
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rectToUpdate = event->rect();
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawImage(rectToUpdate, image, rectToUpdate);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu* menu = new QMenu(this);

    QAction* actionpopup1 = new QAction("Copy");
    actionpopup1->setIcon(QIcon(":/Icons/copy.png"));
    menu->addAction(actionpopup1);

    QAction* actionpopup2 = new QAction("Paste");
    actionpopup2->setIcon(QIcon(":/Icons/paste.png"));
    menu->addAction(actionpopup2);

    QAction* actionpopup3 = new QAction("Clear");
    actionpopup3->setIcon(QIcon(":/Icons/clear.png"));
    menu->addAction(actionpopup3);


    connect(actionpopup1, &QAction::triggered,[=](){
    QClipboard* clipboard = QApplication::clipboard();
    QMimeData* mimeDataMine = new QMimeData();
    mimeDataMine->setImageData(image);
    clipboard->setMimeData(mimeDataMine);
    });

    connect(actionpopup2, &QAction::triggered,[=](){
    QClipboard* clipboard = QApplication::clipboard();
    image = clipboard->image();
    update();
    });

    connect(actionpopup3, &QAction::triggered,[=](){
    image.fill(Qt::white);
    update();
    });

    menu->popup(mapToGlobal(event->pos()));
}

