
#ifndef TYPED_MATRIX
#define TYPED_MATRIX

#include <assert.h>
#include <iostream>
#include <stdexcept>
//#include "typed_array.h"
#include <vector>

#include <math.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
using std::ifstream;

/*
using std::cout;
using std::endl;

using std::vector;
 */

template<typename ElementType>
class TypedMatrix {

public:

    //defalut constructor
    TypedMatrix();

    //constructor that makes an mxn matrix of all default values of ElementType
    TypedMatrix(int n, int m);

    int row_size() const;

    int column_size() const;

    int rows() const;

    int cols() const;

    const ElementType &get(int i, int j) const;

    void set(int i, int j, ElementType value);

    TypedMatrix &operator=(const TypedMatrix &other);

    TypedMatrix &operator+=(const TypedMatrix &other);

    TypedMatrix &operator*=(const TypedMatrix &other);

    bool operator==(const TypedMatrix &other) const;

    TypedMatrix operator+(const TypedMatrix &other);

    TypedMatrix operator*(const TypedMatrix &other);

    vector <ElementType> operator[](int n);

    //TypedMatrix<double> read_matrix_csv(const string path);

    //void write_matrix_csv(const TypedMatrix<double> &matrix);

    TypedMatrix& operator<<(const TypedMatrix&);

private:

    //TypedArray<TypedArray<ElementType>> matrix;
    vector <vector<ElementType>> matrix;   //matrix[[]]

    int row,
            column;


};

template<typename ElementType>
int TypedMatrix<ElementType>::row_size() const {
    return row;
}

template<typename ElementType>
int TypedMatrix<ElementType>::column_size() const {
    return column;
}

template<typename ElementType>
int TypedMatrix<ElementType>::rows() const{
    return row;
}

template<typename ElementType>
int TypedMatrix<ElementType>::cols() const{
    return column;
}

template<typename ElementType>
//TypedArray<TypedArray<double>> m
TypedMatrix<ElementType>::TypedMatrix() {
    ElementType x = ElementType();
    row = 1;
    column = 1;
    // matrx == []
    matrix.push_back(vector<ElementType>());  // matrx =[[]]

    matrix[0].push_back(x);// matrix == [[x]]
}

template<typename ElementType>
TypedMatrix<ElementType>::TypedMatrix(int n, int m) {    // m rows and n columns
    row = m;
    column = n;
    ElementType x = ElementType();
    for (int i = 0; i < row; i++) {
        matrix.push_back(vector<ElementType>());
        for (int j = 0; j < column; j++) {
            matrix[i].push_back(x);
        }
    }
}

template<typename ElementType>
const ElementType &TypedMatrix<ElementType>::get(int i, int j) const {
    //check dimension

    if (row <= i || column <= j) {
        throw std::range_error("outrange index in matrix");
    } else if (i < 0 || j < 0) {
        throw std::range_error("negative index in matrix");
    }
    return matrix[i][j];
    /*ElementType value = matrix[i][j];
    return value;*/
    //return matrix[i][j];

}

template<typename ElementType>
void TypedMatrix<ElementType>::set(int i, int j, ElementType value) {
    if (row < i || column < j) {
        throw std::range_error("outrange index in matrix");
    } else if (i < 0 || j < 0) {
        throw std::range_error("negative index in matrix");
    }
    matrix[i][j] = value;
}

template<typename ElementType>
TypedMatrix<ElementType> &TypedMatrix<ElementType>::operator=(const TypedMatrix<ElementType> &other) {
    if (this != &other) {
        this->row = other.row_size();
        this->column = other.column_size();
        this->matrix = other.matrix;
    }
    return *this;
}

template<typename ElementType>
TypedMatrix<ElementType> &TypedMatrix<ElementType>::operator+=(const TypedMatrix<ElementType> &other) {
    //check dimension
    if (row != other.row || column != other.column) {
        throw std::range_error("wrong dimension in matrix");
    }
    for (int i = 0; i < this->row_size(); ++i) {
        for (int j = 0; j < this->column_size(); ++j) {
            ElementType value = get(i, j) + other.get(i, j);
            set(i, j, value);
        }
    }
    return *this;
}

template<typename ElementType>
TypedMatrix<ElementType> &TypedMatrix<ElementType>::operator*=(const TypedMatrix<ElementType> &other) {
    //check dimension
    if (row != other.row) {
        throw std::range_error("wrong dimension in matrix");
    }
    if (column != other.column) {
        throw std::range_error("wrong dimension in matrix");
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < other.column; ++j) {
            ElementType value = matrix[i][j] * other.get(i, j);

            set(i, j, value);
        }
    }
    return *this;
}

template<typename ElementType>
bool TypedMatrix<ElementType>::operator==(const TypedMatrix<ElementType> &other) const {
    //check dimension
    for (int i = 0; i < this->row_size(); ++i) {
        for (int j = 0; j < this->column_size(); ++j) {
            return this->get(i, j) == other.get(i, j);
        }
    }
}

template<typename ElementType>
TypedMatrix<ElementType> TypedMatrix<ElementType>::operator+(const TypedMatrix<ElementType> &other) {
    //check dimension

    if (row != other.row || column != other.column) {
        throw std::range_error("wrong dimension in matrix");
    }
    TypedMatrix<ElementType> m(column, row);

    for (int i = 0; i < m.row_size(); ++i) {
        for (int j = 0; j < m.column_size(); ++j) {
            //ElementType value = ElementType();
            ElementType value = get(i, j) + other.get(i, j);
            m.set(i, j, value);
        }
    }
    return m;
}

template<typename ElementType>
TypedMatrix<ElementType> TypedMatrix<ElementType>::operator*(const TypedMatrix<ElementType> &other) {
    //check dimension
    /*if(column != other.column) {
        throw std::range_error("wrong dimension in matrix");
    }*/
    if (column != other.row) {
        throw std::range_error("wrong dimension of matrix multiplication");
    }
    TypedMatrix<ElementType> m;
    for (int i = 0; i < this->row_size(); ++i) {
        for (int j = 0; j < other.column; ++j) {
            ElementType value = ElementType();
            for (int k = 0; k < this->column_size(); ++k) {
                value += this->get(i, k) * other.get(k, j);
                //m.set(i,j,this->get(i,k)*other.get(k,j));
            }
            m.set(i, j, value);
            //m.set(i,j,this->get(i,j)*other.get(i,j));
        }
    }
    return m;
}

template<typename ElementType>
std::ostream &operator<<(std::ostream &os, TypedMatrix<ElementType> &matrix) {
    os << '[';
    for (int i = 0; i < matrix.row_size(); i++) {
        for (int j = 0; j < matrix.column_size(); j++) {
            os << matrix.get(i, j);
            if (i < matrix.row_size() - 1) {
                os << ",";
            }

        }
    }
    os << ']';
    return os;
}

template<typename ElementType>
vector <ElementType> TypedMatrix<ElementType>::operator[](int n) {
    return matrix[n];
}


//question 3
//template <typename ElementType>
/*
TypedMatrix<double> read_matrix_csv(const string path) {
    //throw exception
    // ....
    std::ifstream file;
    file.open(path, std::ifstream::in);

    vector <vector<double>> dataList;
    int row = 0;
    int column = 0;
    string line = "";
    while (getline(file, line)) {
        dataList.push_back(vector < double > );
        char *token;
        token = strtok(line, " ,.-");
        while (toekn != NULL) {
            dataList.push_back(token);
            token = strok(NULL, " ,.-");
        }

    }
    row = dataList.size();
    column = dataList[0].size();

    TypedMatrix<double> m(column, row);

    for (int i = 0; i< row; i++) {
        for (int j = 0; j< column; j++) {

            double value = dataList[i][j];
            m.set(i, j, value);
        }
    }


}
 */

//question 4
/*
void write_matrix_csv(const TypedMatrix<double> &matrix) {
    string mystr;
    for (int i = 0; i < matrix.row; i++) {
        for (int j = 0; j < matrix.column; j++) {
            double value = matrix.get(i, j);
            string str = to_string(value);
            mystr += str;
            if (i != matrix.column_size() - 1) {
                mystr += ', ';
            }
            //mystr.push_back(str);
            //mystr.push_back(', ');
        }
        mystr += endl;
    }
    return;
}
 */

#endif
