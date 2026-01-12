#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QString>
#include<QChar>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
static double number=-1.1;

void MainWindow::SetNumber(int num){
    QString text = ui->textBrowser->toPlainText();
    if(num==0){
        if(text.isEmpty()){
            ui->textBrowser->setText(ui->textBrowser->toPlainText()+"0");
        }
        else if(number!=0&&number!=-1.1){
            ui->textBrowser->setText(ui->textBrowser->toPlainText()+"0");
            number=number*10;
            qDebug()<<number;
        }
    }
    else{
        if(number==0){
            text.chop(1);
            ui->textBrowser->setText(text+QString::number(num));
            number=num;
        }
        else if(number==-1.1){
            number=0;
            ui->textBrowser->setText(ui->textBrowser->toPlainText()+QString::number(num));
        }
        else{
            ui->textBrowser->setText(ui->textBrowser->toPlainText()+QString::number(num));
        }

        number=number*10+num;
    }
    qDebug()<<"number:"<<number;
}
QVector<int> arr;
QString op;

template <typename T>
void PrintArr(QVector<T>& a){
    qDebug()<<"---------------------------";
    for(typename QVector<T>::iterator it = a.begin();it!=a.end();it++){
        if constexpr (std::is_same_v<T, std::string>) {
            qDebug() << "arr元素: " << QString::fromStdString(*it);
        } else {
            qDebug() << "arr元素: " << *it;
        }
    }
}
void  MainWindow::SetOp(char sop,char sop1,char sop2){
    if(number!=-1.1)
        arr.push_back(number);
    number=-1.1;
    QString text = ui->textBrowser->toPlainText();
    if(!text.isEmpty()){
        if(text.back()==sop1||text.back()==sop2){
            text.chop(1);
            ui->textBrowser->setText(text+sop);
            op.back()=sop;
        }
        else if(text.back()==sop){}
        else{
            ui->textBrowser->setText(ui->textBrowser->toPlainText()+sop);
            op+=sop;
        }
    }
    PrintArr(arr);
    qDebug()<<op;
}
bool Isop(char c){
    return  c == '+' || c == '-' || c == '*';
}
bool Isop(QChar c){
    return c == QChar('+') || c == QChar('-') || c == QChar('*');
};
void MainWindow::on_pushButton_1_clicked()
{
    SetNumber(1);
}

void MainWindow::on_pushButton_2_clicked()
{
    SetNumber(2);
}

void MainWindow::on_pushButton_3_clicked()
{
    SetNumber(3);
}


void MainWindow::on_pushButton_4_clicked()
{
   SetNumber(4);
}


void MainWindow::on_pushButton_5_clicked()
{
    SetNumber(5);
}



void MainWindow::on_pushButton_6_clicked()
{
   SetNumber(6);
}


void MainWindow::on_pushButton_7_clicked()
{
    SetNumber(7);
}

void MainWindow::on_pushButton_8_clicked()
{
    SetNumber(8);
}

void MainWindow::on_pushButton_9_clicked()
{
    SetNumber(9);
}


void MainWindow::on_pushButton_0_clicked()
{
    SetNumber(0);
}

void MainWindow::on_pushButton_plus_clicked()
{
    SetOp('+','-','*');
}


void MainWindow::on_pushButton_minus_clicked()
{
    SetOp('-','+','*');
}


void MainWindow::on_pushButton_muti_clicked()
{
    SetOp('*','-','+');
}


void MainWindow::on_pushButton_equal_clicked()
{
    QString text = ui->textBrowser->toPlainText();
    if(Isop(text.back())){
        op.erase(op.end()-1);
    }
    else{
        arr.push_back(number);
        PrintArr(arr);
        qDebug()<<"arrSixe:"<<arr.size();
        int i=0;
        QString tmp=op;
        for( auto it = arr.begin(); it != arr.end() - 1; ++it){
            if (tmp!=nullptr){
                QChar tmpop = tmp[0];
                tmp.remove(0,1);
                if(tmpop=='*'){
                    arr[i]=arr[i]*arr[i+1];
                    it = arr.erase(++it);
                }
            }
            else{
                qDebug()<<"tmp is null";
                break;
            }
            i++;
        }
        while(1){
            if(op.indexOf('*')==-1)break;
            int pos = op.indexOf('*');
            op.remove(pos, 1);
        }
        //qDebug()<<"arrSixe:"<<arr.size();
        for(int i=0;i<arr.size()-1;i++){
            qDebug()<<"arr[i+1] "<<arr[i+1]<<"  arr[i]: "<<arr[i];
            if(op[i]=='+')arr[i+1]=arr[i+1]+arr[i];
            if(op[i]=='-')arr[i+1]=arr[i]-arr[i+1];
            qDebug()<<"arr[i+1] "<<arr[i+1]<<"  arr[i]: "<<arr[i];
        }
    }
    qDebug()<<"arrlast "<<arr.last();
    text = QString::number( arr.last());
    ui->textBrowser->setText(text);
    number=arr.last();
    arr.erase(arr.begin(),arr.end());
    op=QString();
}


void MainWindow::on_pushButton_exit_clicked()
{
    this->close();
}


void MainWindow::on_pushButton_undo_clicked()
{
    QString text = ui->textBrowser->toPlainText();
    if(text.isEmpty()){}
    else if(Isop(text.back())){
        op.erase(op.end()-1);
        number=arr.back();
        arr.pop_back();
        text.chop(1);
        ui->textBrowser->setText(text);

    }
    else{
        number=number/10;
        text.chop(1);
        ui->textBrowser->setText(text);
    }
    if(!text.isEmpty()){

    }
    PrintArr(arr);
}
