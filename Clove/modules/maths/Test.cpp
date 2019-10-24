#include <iostream>

#include "Matrix.hpp"
#include "Vector.hpp"

int main(){
    std::cout << "MATRICES" << std::endl;

    clv::mth::Matrix<2, 2, float> matA;
    matA[0][0] = 1;
    matA[0][1] = 2;
    matA[1][0] = 3;
    matA[1][1] = 4;

    clv::mth::Matrix2f matB;
    matB[0][0] = 1;
    matB[0][1] = 1;
    matB[1][0] = 1;
    matB[1][1] = 1;

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
    std::cout << "a.[0]:" << a[0] << " a.[1]:" << a[1] << std::endl;
    std::cout << "a.x:" << a.x << " a.y:" << a.y << std::endl;
    std::cout << "a.r:" << a.r << " a.g:" << a.g << std::endl;
    std::cout << "a.u:" << a.u << " a.v:" << a.v << std::endl;


    clv::mth::Vector2f b{5, -3};
    std::cout << "b.x:" << b[0] << " b.y:" << b[1] << std::endl;

    auto ab = a + b;
    std::cout << "a+b.x:" << ab[0] << " a+b.y:" << ab[1] << std::endl;

    clv::mth::Vector3f ca{34, -6, 200};
    std::cout << "ca.x:" << ca[0] << " ca.y:" << ca[1] << " ca.z" << ca[2] << std::endl;

    clv::mth::Vector3f cb{34, -6, 200};
    std::cout << "cb.x:" << cb[0] << " cb.y:" << cb[1] << " cb.z" << cb[2] << std::endl;

    auto cc = ca - cb;
    std::cout << "cc.x:" << cc[0] << " cc.y:" << cc[1] << " cc.z" << cc[2] << std::endl;

    clv::mth::Vector4f d{345.756f, 100.00002, 89, 1};
    std::cout << "d.x:" << d[0] << " d.y:" << d[1] << " d.z:" << d[2] << " d.w:" << d[3] << std::endl;

    auto d2 = d * 5.0f;
    std::cout << "d2.x:" << d2[0] << " d2.y:" << d2[1] << " d2.z:" << d2[2] << " d.w:" << d2[3] << std::endl;

    return 0;
}