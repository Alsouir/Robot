#include "mainwindow.h"
#include "./ui_mainwindow.h"


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


void MainWindow::replacePi(QString& str) {
    QString piValue = QString::number(M_PI);

    int pos = str.indexOf("pi");
    str.replace(pos, 2, piValue);
}

double MainWindow::evaluateExpression (QString str){
//    -pi / 2
//    pi / 2
//    3 * pi / 8
//    0.75 * pi
    auto it = std::find(str.begin(), str.end(), 'p');
    if (it == str.end()){
        return str.toDouble();
    }
    replacePi(str);
    double result;
//    if (str[0] == '-'){
//        result = -1;
//        str.substr(1);
//    }
//    double operand1 = 0.0, operand2 = 0.0;
//    char symb;
//    while (find(str.begin(), str.end(), '/') != str.end() && find(str.begin(), str.end(), '*') != str.end()) {
//        auto mul = find(str.begin(), str.end(), '*');
//        auto div = find(str.begin(), str.end(), '/');
//        if (mul > div) {
//            operand1 = (str.substr(0, mul)).toDouble();
//            str.erase(0, mul + 1);
//            if (find(str.begin(), str.end(), '*') != str.end()) {

//            }
//        }
//    }

    QTextStream stream(&str);

    stream >> result;

    char op;
    double value;

    while (!stream.atEnd()) {
        stream >> op >> value;
        if (op == '*') {
            result *= value;
        } else if (op == '/') {
            result /= value;
        }
    }
    return result;
}

void MainWindow::on_pushButton_clicked()
{
    std::vector<std::vector<double>> params(6, std::vector<double>(4));
    params[0][0] = ui->theta0->text().toDouble();
    params[1][0] = ui->theta1->text().toDouble();
    params[2][0] = ui->theta2->text().toDouble();
    params[3][0] = ui->theta3->text().toDouble();
    params[4][0] = ui->theta4->text().toDouble();
    params[5][0] = ui->theta5->text().toDouble();

    params[0][1] = ui->a0->text().toDouble();
    params[1][1] = ui->a1->text().toDouble();
    params[2][1] = ui->a2->text().toDouble();
    params[3][1] = ui->a3->text().toDouble();
    params[4][1] = ui->a4->text().toDouble();
    params[5][1] = ui->a5->text().toDouble();

    params[0][2] = ui->d0->text().toDouble();
    params[1][2] = ui->d1->text().toDouble();
    params[2][2] = ui->d2->text().toDouble();
    params[3][2] = ui->d3->text().toDouble();
    params[4][2] = ui->d4->text().toDouble();
    params[5][2] = ui->d5->text().toDouble();

    params[0][3] = evaluateExpression(ui->alpha0->text());
    params[1][3] = evaluateExpression(ui->alpha1->text());
    params[2][3] = evaluateExpression(ui->alpha2->text());
    params[3][3] = evaluateExpression(ui->alpha3->text());
    params[4][3] = evaluateExpression(ui->alpha4->text());
    params[5][3] = evaluateExpression(ui->alpha5->text());

    Robot NewCoordinates(params);
    QString resultCoordinates  = "( "
      + QString::number(NewCoordinates.GetX()) + ", "
      + QString::number(NewCoordinates.GetY()) + ", "
      + QString::number(NewCoordinates.GetZ()) + " )";

    ui->lineEdit->setText(resultCoordinates);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->theta0->setText("0.0");
    ui->theta1->setText("0.0");
    ui->theta2->setText("0.0");
    ui->theta3->setText("0.0");
    ui->theta4->setText("0.0");
    ui->theta5->setText("0.0");

    ui->a0->setText("0.0");
    ui->a1->setText("0.0");
    ui->a2->setText("0.0");
    ui->a3->setText("0.0");
    ui->a4->setText("0.0");
    ui->a5->setText("0.0");

    ui->d0->setText("0.0");
    ui->d1->setText("0.0");
    ui->d2->setText("0.0");
    ui->d3->setText("0.0");
    ui->d4->setText("0.0");
    ui->d5->setText("0.0");

    ui->alpha0->setText("0.0");
    ui->alpha1->setText("0.0");
    ui->alpha2->setText("0.0");
    ui->alpha3->setText("0.0");
    ui->alpha4->setText("0.0");
    ui->alpha5->setText("0.0");
}

