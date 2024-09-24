#include "Robot.h"


double pi = 3.14159265358979;


Matrix::Matrix(): T(4, std::vector<double>(4, 0.0)){}
Matrix::Matrix(std::vector <std::vector<double>>& T_) : T(T_) {}
Matrix::Matrix(const std::vector <std::vector<double>>& T_) : T(T_) {}

std::vector<std::vector<double>> Matrix::MulMatrix(const std::vector<std::vector<double>>& T1, const std::vector<std::vector<double>>& T2) {
    std::vector<std::vector<double>> resultMul(T1.size(), std::vector<double>(T2[0].size()));
    double sum_ij;
    for (int i = 0; i < resultMul.size(); i++) {
        for (int j = 0; j < resultMul[0].size(); j++) {
            sum_ij = 0;
            for (int k = 0; k < T1[0].size(); k++) {
                sum_ij += T1[i][k] * T2[k][j];
            }
            resultMul[i][j] = sum_ij;
        }
    }
    return resultMul;
}

Matrix Matrix::operator*(const Matrix& other) {
    return Matrix(MulMatrix(T, other.T));
}
std::vector<double>& Matrix::operator[](int i) {
    return T[i];
}




Robot::Robot(std::vector <std::vector<double>>& parameters_) : parameters(parameters_) {
    position();
}

double Robot::degInRad(double deg) {
    return deg * pi / 180.0;
}

Matrix Robot::matrixTransformation(double theta, double a, double d, double alpha) {
    Matrix Joint;
    Joint[0][0] = cos(theta);
    Joint[0][1] = -sin(theta) * cos(alpha);
    Joint[0][2] = sin(theta) * sin(alpha);
    Joint[0][3] = a * cos(theta);

    Joint[1][0] = sin(theta);
    Joint[1][1] = cos(theta) * cos(alpha);
    Joint[1][2] = -cos(theta) * sin(alpha);
    Joint[1][3] = a * sin(theta);

    Joint[2][0] = 0.0;
    Joint[2][1] = sin(alpha);
    Joint[2][2] = cos(alpha);
    Joint[2][3] = d;

    Joint[3][0] = 0.0;
    Joint[3][1] = 0.0;
    Joint[3][2] = 0.0;
    Joint[3][3] = 1.0;

    return Joint;
}


Matrix Robot::ResultMatrixTransformation() {
    Matrix resultMatrix = matrixTransformation(degInRad(parameters[0][0]), parameters[0][1], parameters[0][2], parameters[0][3]);

    for (int i = 1; i < parameters.size(); i++) {
        resultMatrix = resultMatrix * matrixTransformation(degInRad(parameters[i][0]), parameters[i][1], parameters[i][2], parameters[i][3]);
    }

    return resultMatrix;
}

void Robot::position() {
    Matrix resultMatrix = ResultMatrixTransformation();
    x = resultMatrix[0][3];
    y = resultMatrix[1][3];
    z = resultMatrix[2][3];
//        std::cout << '(' << x << ',' << y << ',' << z << ')' << '\n';
}

double Robot::GetX (){
    return x;
}

double Robot::GetY (){
    return y;
}

double Robot::GetZ (){
    return z;
}



////int main() {
////    std::vector <std::vector<double>> parameters_ = { { 15.0, 0, 0.213, pi / 2},
////        {-50, -0.8, 0.193, 0},
////        {-60, -0.59, -0.16, 0},
////        { 95, 0, 0.25, pi / 2},
////        { 50, 0, 0.28, - pi / 2},
////        {0, 0, 0.25, 0}
////    };
////    Robot New(parameters_);
////    return 0;
////}

