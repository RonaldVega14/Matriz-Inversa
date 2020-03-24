#include <vector>
#include "math.h"
#include "stdlib.h"

using namespace std;

typedef vector<float> Vector;
typedef vector<Vector> Matrix;

//La funcion crea una matriz cuadrada nxn llena de ceros
//La funcion recibe: Una matriz y la dimension de la matriz

void zeroes(Matrix &M,int n){
    //Se crean n filas
    for(int i=0;i<n;i++){
        //Se crea una fila de n ceros
        vector<float> row(n,0.0);
        //Se ingresa la fila en la matriz
        M.push_back(row);
    }
}
     
//La funcion crea una matriz cuadrada nx1 llena de ceros
//La funcion recibe: Un vector columna y la dimension del vector

void zeroes(Vector &v,int n){
    //Se itera n veces
    for(int i=0;i<n;i++){
        //En cada iteracion se agrega un cero al vector
        v.push_back(0.0);
    }
}

void copyVector(Vector v, Vector &copy){
    zeroes(copy,v.size());
    for(int i=0;i<v.size();i++)
        copy.at(i) = v.at(i);
}

//La funcion copiara el contenido de la primera matriz en la segunda, respetando las posiiones.
//La funcion recibe: Una matriz y una matriz que sera la copia de la primera.

void copyMatrix(Matrix A, Matrix &copy){
    //Se inicializa la copia con ceroes
    //asegurandose de sus dimensiones
    zeroes(copy,A.size());
    //Se recorre la matriz original
    for(int i=0;i<A.size();i++)
        for(int j=0;j<A.at(0).size();j++)
            //Se coloca la celda actual de la matriz original
            //en la misma posicion dentro de la copia
            copy.at(i).at(j) = A.at(i).at(j);
}

//La funcion asume que las dimensiones de la matriz y los vectores son las adecuadas para que la multiplicacion
//sea posible.
//La funcion recibe: Una matriz, Un vector, Un vector y un vector para la respuesta.

void productMatrixVector(Matrix A, Vector v, Vector &R){
    //Se itera una cantidad de veces igual al numero de filas de la matriz
    for(int f=0;f<A.size();f++){
        //Se inicia un acumulador
        float cell = 0.0;
        //Se calcula el valor de la celda de acuerdo a la formulacion
        for(int c=0;c<v.size();c++){
            cell += A.at(f).at(c)*v.at(c);
        }
        //Se coloca el valor calculado en su celda correspondiente en la respuesta
        R.at(f) += cell;
    }
}

//La funcion multiplica cada uno de los elementos de la matriz por el escalar, ubicando los resultados 
//en la matriz de respuesta.
//La funcion recibe: Un escalar(Valor Real), una matriz y una matriz para la respuesta.

void productRealMatrix(float real,Matrix M,Matrix &R){
    //Se prepara la matriz de respuesta con las mismas dimensiones de la
    //matriz
    zeroes(R,M.size());
    //Se recorre la matriz original
    for(int i=0;i<M.size();i++)
        for(int j=0;j<M.at(0).size();j++)
            //La celda actual se multiplica por el real, y se almacena
            //el resultado en la matriz de respuesta
            R.at(i).at(j) = real*M.at(i).at(j);
}

//La funcion elimina en la matriz la fila i, y la columna j
//La funcion recibe: Una matriz, un indice de fila i y un indice de fila j.

void getMinor(Matrix &M,int i, int j){
    //Se elimina la fila i
    M.erase(M.begin()+i); //Uso de begin para obtener un iterator a la posicion de interes
    //Se recorren las filas restantes
    for(int i=0;i<M.size();i++)
        //En cada fila se elimina la columna j
        M.at(i).erase(M.at(i).begin()+j);
}

//La funcion calcula el determinante de la matriz de forma recursiva
//La funcion recibe: Una natriz
    
float determinant(Matrix M){
    //Caso trivial: si la matriz solo tiene una celda, ese valor es el determinante
    if(M.size() == 1) return M.at(0).at(0);
    else{
        //Se inicia un acumulador
        float det=0.0;
        //Se recorre la primera fila
        for(int i=0; i<M.at(0).size(); i++){
            //Se obtiene el menor de la posicion actual
            Matrix minor;
            copyMatrix(M,minor);
            getMinor(minor,0,i);

            //Se calculala contribucion de la celda actual al determinante
            //(valor alternante * celda actual * determinante de menor actual)
            det += pow(-1,i)*M.at(0).at(i)*determinant(minor);
        }
        return det;
    }
}

//La funcion recibe saca el cofactor de una matriz.
//La funcion recibe: Una matriz y la matriz que contendra los cofactores de la primera.

void cofactors(Matrix M, Matrix &Cof){
    //Se prepara la matriz de cofactores para que sea de las mismas
    //dimensiones de la matriz original
    zeroes(Cof,M.size());
    //Se recorre la matriz original
    for(int i=0;i<M.size();i++){
        for(int j=0;j<M.at(0).size();j++){
            //Se obtiene el menor de la posicion actual
            Matrix minor;
            copyMatrix(M,minor);
            getMinor(minor,i,j);
            //Se calcula el cofactor de la posicion actual
            //      alternante * determinante del menor de la posicion actual
            Cof.at(i).at(j) = pow(-1,i+j)*determinant(minor);
        }
    }
}

//La funcion transpone la primera matriz y almacena el resultado en la segunda
//La funcion recibe: Una matriz y la matriz que contendra a la primera transpuesta

void transpose(Matrix M, Matrix &T){
    //Se prepara la matriz resultante con las mismas dimensiones
    //de la matriz original
    zeroes(T,M.size());
    //Se recorre la matriz original
    for(int i=0;i<M.size();i++)
        for(int j=0;j<M.at(0).size();j++)
            //La posicion actual se almacena en la posicion con indices
            //invertidos de la matriz resultante
            T.at(j).at(i) = M.at(i).at(j);
}

void inverse(Matrix M, Matrix &R){
     float det = determinant(M);
     cout << "\nDeterminante: " << det << endl;
     Matrix Cof, CofTrans;
     if(det == 0){
            exit(EXIT_FAILURE);
     }else{
           cofactors(M, Cof);
           transpose(Cof, CofTrans);
           productRealMatrix(1/det, CofTrans, R);
           return;
     }
}
