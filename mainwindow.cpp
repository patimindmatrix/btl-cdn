#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <stdlib.h>
#include <iostream>
#include <QString>
#include "library.h"


int generateChoice(QString cb){
    if (cb.toStdString() == "Cộng"){
        return 1;
    } else if (cb.toStdString() == "Trừ") {
        return 2;
    } else if (cb.toStdString() == "Nhân"){
        return 3;
    }else {
        return 4;
    }
}

BigInteger solve(int choice, QString a, QString b) {
    BigInteger answer = BigInteger("0");
    switch (choice) {
    case 1:{
        answer = BigInteger(a.toStdString()) + BigInteger(b.toStdString());
        break;
    }
    case 2:{
        answer = BigInteger(a.toStdString()) - BigInteger(b.toStdString());
        break;
    }
    case 3:{
        answer = BigInteger(a.toStdString()) * BigInteger(b.toStdString());
        break;
    }
    case 4:{
        answer = BigInteger(a.toStdString()) / BigInteger(b.toStdString());
        break;
    }
    default:
        break;
    }
    return answer;
}

class TestCaseModel {
private:
    QString a;
    QString b;
    QString c;
    QString d;
    QString e;
    QString f;

public:
    TestCaseModel() {}

    TestCaseModel(QString a, QString b, QString c, QString d, QString e, QString f) {
        this->a = a; //th1
        this->b = b; //th2
        this->c = c; //pt
        this->d = d; //-----
        this->e = e; //answer
        this->f = f; //realans
    }

    QString getA(){
        return a;
    }
    QString getB(){
        return b;
    }
    QString getC(){
        return c;
    }
    QString getD(){
        return d;
    }
    QString getE(){
        return e;
    }
    QString getF(){
        return f;
    }

    BigInteger answer(){
        int choice = generateChoice(this->c);
        BigInteger ans = solve(choice, this->a, this->b);
        this->f = ans.toQString();
        return ans;
    }
};
std::vector<TestCaseModel> current(0);




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


void MainWindow::on_pushButton_clicked()
{
    QString a = ui->lineEdit->text();
    QString b = ui->lineEdit_2->text();
    QMessageBox temp;
    if (a == "" || b == ""){
        temp.setText("Không được để trống toán hạng");
        temp.exec();
    }else {
        BigInteger answer = BigInteger("0");
        QString cb = ui->comboBox->currentText();
        if (cb == "Chia" && b == "0"){
            QMessageBox temp;
            temp.setText("Ai cho chia với số 0");
            temp.exec();
        } else {
            int choice = generateChoice(cb);
            answer = solve(choice, a, b);
            ui->label_5->setText(answer.toQString());
        }
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->label_5->setText("");
}


void MainWindow::on_pushButton_3_clicked()
{
    QString a = ui->lineEdit_3->text();
    QString b = ui->lineEdit_4->text();
    QString c = ui->lineEdit_5->text();
    QString cb = ui->comboBox_2->currentText();
    if (a.isEmpty() || b.isEmpty() || c.isEmpty() || cb.isEmpty()){
        QMessageBox temp;
        temp.setText("Vui lòng điền đầy đủ thông tin");
        temp.exec();
    }else {
        current.push_back(TestCaseModel(a, b, cb, QString("------------------------------------------------"), c, QString("")));
        QString item1 = QString("Toán hạng 1: ") + a;
                        QString item2 = QString("Toán hạng 2: ") + b;
              QString item4 = QString("Phép toán: ") + cb;
                  QString item3 = QString("Đáp án: ") + c;
              QString item5 = QString("------------------------------------------------");
        ui->listWidget->addItems({ item1, item2, item4, item3, item5 });
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->listWidget->clear();
    for (auto i: current){
        TestCaseModel t = i;
        t.answer();
        QString item1 = QString("Toán hạng 1: ") + t.getA();
        QString item2 = QString("Toán hạng 2: ") + t.getB();
        QString item4 = QString("Phép toán: ") + t.getC();
        QString item3 = QString("Đáp án mong muốn: ") + t.getE();
        QString item6 = QString("Đáp án đầu ra: ") + t.getF();
        QString item5 = QString("-----------------------------------------------------------");
        ui->listWidget->addItems({ item1, item2, item4, item3, item6, item5 });
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->listWidget->clear();
    current.clear();
}

