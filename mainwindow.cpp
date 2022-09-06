#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QByteArray>
#include <QTextStream>
#include <QTextCodec>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    subPath = QFileDialog::getOpenFileName(this,"Open Your Sub","C:/Users/MSI/Desktop/","subtitle File (*.srt)");
}

void MainWindow::on_pushButton_2_clicked()
{
    QFile Sub (subPath);
      QFile output("C:/Users/MSI/Desktop/output.srt");
    if(!Sub.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox msgBox;
            msgBox.setText("when open  File occure a Error !");
            msgBox.exec();

       QApplication::quit();
    }
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    output.open(QIODevice::WriteOnly | QFile::Text);

    QTextStream stream(&Sub);

    QTextStream out(&output);

    QByteArray byte;
    stream.setCodec("Windows-1256");
   out.setCodec("UTF-8");
   out.setGenerateByteOrderMark(false);
   QString line ;
   //stream.setCodec("UTF-8");

    while(!stream.atEnd())
    {
        QString temp =stream.readLine();
       byte=temp.toUtf8();
        QString line =byte.constData() ;
            qDebug()<<line<<endl;
      out<<line<<endl;
      out.flush();
    }


output.close();
Sub.close();



}


