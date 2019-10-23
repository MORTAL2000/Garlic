#include <iostream>

#include "Matrix.hpp"
#include "Vector.hpp"

int main(){
    std::cout << "MATRICES" << std::endl;

    clv::mth::Matrix<2, 2, float> matA;
    matA[0][0] = 2;
    matA[0][1] = 31;
    matA[1][0] = 29;
    matA[1][1] = -5;

    clv::mth::Matrix2f matB;
    matB[0][0] = -8;
    matB[0][1] = 100;
    matB[1][0] = 3;
    matB[1][1] = 9;

    std::cout << "matA[0][0]:" << matA[0][0] << " matA[0][1]:" << matA[0][1] << std::endl;
    std::cout << "matA[1][0]:" << matA[1][0] << " matA[1][1]:" << matA[1][1] << std::endl;

    std::cout << "matB[0][0]:" << matB[0][0] << " matB[0][1]:" << matB[0][1] << std::endl;
    std::cout << "matB[1][0]:" << matB[1][0] << " matB[1][1]:" << matB[1][1] << std::endl;

    //Matrix<3, 2, float> matB;

    auto resultMul = matA * matB;

    std::cout << "resultMul[0][0]:" << resultMul[0][0] << " resultMul[0][1]:" << resultMul[0][1] << std::endl;
    std::cout << "resultMul[1][0]:" << resultMul[1][0] << " resultMul[1][1]:" << resultMul[1][1] << std::endl;

    auto resultAdd = matA + matB;

    std::cout << "resultAdd[0][0]:" << resultAdd[0][0] << " resultAdd[0][1]:" << resultAdd[0][1] << std::endl;
    std::cout << "resultAdd[1][0]:" << resultAdd[1][0] << " resultAdd[1][1]:" << resultAdd[1][1] << std::endl;




    std::cout << "VECTORS" << std::endl;

    clv::mth::Vector2f a{5, 4};
    std::cout << "a.x:" << a[0] << " a.y:" << a[1] << std::endl;

    clv::mth::Vector2f b{5, -3};
    std::cout << "b.x:" << b[0] << " b.y:" << b[1] << std::endl;

    clv::mth::Vector2f ab = a + b;
    std::cout << "a+b.x:" << ab[0] << " a+b.y:" << ab[1] << std::endl;

    clv::mth::Vector3f c{34, -6, 200};
    std::cout << "c.x:" << c[0] << " c.y:" << c[1] << " c.z" << c[2] << std::endl;

    clv::mth::Vector4f d{345.756f, 100.00002, 89, 1};
    std::cout << "d.x:" << d[0] << " d.y:" << d[1] << " d.z:" << d[2] << " d.w:" << d[3] << std::endl;

    return 0;
}