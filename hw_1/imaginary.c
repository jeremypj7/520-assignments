
#include "imaginary.h"
#include <math.h>

Imaginary add ( Imaginary a, Imaginary b ) {
    return (Imaginary) { a.real +b.real, a.im +b.im };
}

Imaginary negate (Imaginary a) {
    return (Imaginary) { a.real*(-1), a.im*(-1) };
}

Imaginary conjugate (Imaginary a) {
    return (Imaginary) { a.real, a.im*(-1) };
}

Imaginary multiply (Imaginary a, Imaginary b) {
    return (Imaginary) {a.real * b.real - a.im * b.im, a.real * b.im + a.im * b.real};
}

double magnitude ( Imaginary a) {
    return (double) { sqrt(a.real * a.real + a.im * a.im)};
}


