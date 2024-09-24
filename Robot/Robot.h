#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <vector>
#include <cmath>


class Matrix {
private:
    std::vector <std::vector<double>> T;
public:
    Matrix();
    Matrix(std::vector <std::vector<double>>& T_);
    Matrix(const std::vector <std::vector<double>>& T_);
    std::vector<std::vector<double>> MulMatrix(const std::vector<std::vector<double>>& T1, const std::vector<std::vector<double>>& T2);
    Matrix operator*(const Matrix& other);
    std::vector<double>& operator[](int i);
};


class Robot {
private:
    std::vector <std::vector<double>> parameters;
    double x, y, z;
public:
    Robot(std::vector <std::vector<double>>& parameters_);
    double degInRad(double deg);
    Matrix matrixTransformation(double theta, double a, double d, double alpha);
    Matrix ResultMatrixTransformation();
    void position();
    double GetX ();
    double GetY ();
    double GetZ ();

};

#endif // ROBOT_H
