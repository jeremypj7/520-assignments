#include "imaginary.h"
#include <math.h>

Imaginary::Imaginary(){
    real =0;
    imag = 0;
}

//constructor
Imaginary::Imaginary(double a, double b) {
    real = a; 
    imag = b;
}


double Imaginary::re() {
    return real;
}

double Imaginary::im() {
    return imag;
}

Imaginary Imaginary::conjugate() {
    Imaginary cj(real, -imag);
    return cj;
}

double Imaginary::magnitude() {
    return sqrt(real*real+imag*imag);
}

Imaginary& Imaginary::operator+=(const Imaginary& other){

    real = real+other.real;
    imag = imag+other.imag;

    return *this;
}

Imaginary& Imaginary::operator*=(const Imaginary& other){
    double temp1 = real* other.real  - imag * other.imag;
    double temp2 = real * other.imag + imag * other.real;
    real = temp1;
    imag = temp2;

    return *this;
}

bool Imaginary::operator==(const Imaginary& other) const{
    return (real==other.real && imag==other.imag);
}

bool Imaginary::operator!=(const Imaginary& other) const{
    return (real!=other.real || imag!=other.imag);
}


Imaginary Imaginary::operator*(const Imaginary& other) const{
    Imaginary a;
    double temp1 = real* other.real  - imag * other.imag;
    double temp2 = real * other.imag + imag * other.real;
    a.real= temp1;
    a.imag = temp2;
    return a;

}

Imaginary Imaginary::operator+(const Imaginary& other) const{
    Imaginary a;
    a.real= real+other.real;
    a.imag = imag+other.imag;
    return a;
}





