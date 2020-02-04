#ifndef IMAGINARY_H
#define IMAGINARY_H

#include <iostream>

class Imaginary {
    public: 
        Imaginary();

        Imaginary(double a, double b);

        double re();

        double im();

        Imaginary conjugate();

        double magnitude();

        Imaginary& operator+=(const Imaginary& other);

        Imaginary& operator*=(const Imaginary& other);

        bool operator==(const Imaginary& other) const;

        bool operator!=(const Imaginary& other) const;

        Imaginary operator*(const Imaginary& other) const;

        Imaginary operator+(const Imaginary& other) const;




    private:
        double real,imag;
};



#endif
