#include "gtest/gtest.h"
#include <iostream>

#include "../include/matrix.h"

int main(int argc, char* argv[])
{

    if (false) // make false to run unit tests
    {
        // debug section
        // Matrix A { { 1, 2, 3 }, { 3, 0, 1 }, { 1, 1, 1 } };
        // A.display();
        // std::cout << "******" << std::endl;
        // std::cout << A[0][2] << std::endl;

        // Matrix B { { 1, 2, 3 }, { 3, 0, 1.2 }, { 1, 1, 4 } };
        // B.display();
        // std::cout << "******" << std::endl;
        // A.append(B, 1);
        // A.display();
        // std::cout << "******" << std::endl;

        // Matrix A { { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } };
        // A.display();
        // Matrix B;
        // B.display();
        // B = A;
        // B.display();
        // std::cout << A;

        // Matrix A { { 1, 2, 3 }, { 3, 0, 1 }, { 1, 1, 1 } };
        // std::cout << A.Determine() << std::endl;
        return 0;
    } else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << RUN_ALL_TESTS() << std::endl;
    }
}