#include <iostream>
#include "math_tools.h"
#include "display_tools.h"
using namespace std;
int main(void){
    Matrix matrix_example, matrix_inversa;
    
    zeroes(matrix_example, 3);
    
    matrix_example.at(0).at(0) = 2; matrix_example.at(0).at(1) = 2; matrix_example.at(0).at(2) = 3;
    matrix_example.at(1).at(0) = 4; matrix_example.at(1).at(1) = 5; matrix_example.at(1).at(2) = 6;
    matrix_example.at(2).at(0) = 7; matrix_example.at(2).at(1) = 8; matrix_example.at(2).at(2) = 9;
    
    cout << "\nMatriz Original" << endl;

    showMatrix(matrix_example);
    
    inverse(matrix_example, matrix_inversa);
    
    cout << "\nMatriz Inversa" << endl;
    
    showMatrix(matrix_inversa);
    
    return 0;
    
}
