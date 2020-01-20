#include "fraction.h"

Fraction add ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.den + a.den * b.num, a.den * b.den };
}

Fraction multiply ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.num, a.den * b.den };
}
/*
Fraction reduce (Fraction a) {
    int gcd, remainder;
    int num = a.num;
    int den = a.den;
    while(num != 0){
        remainder = den % num;
        den = num;
        num = remainder;
    }
    gcd = den;
    return (Fraction) {a.num/gcd, a.den/gcd};
}  */

Fraction reduce (Fraction a) {
    if(a.num == 0 && a.den != 0) {
        a.den = 1;
    }else if (a.den == 0 && a.num != 0) {
        a.num = 1;
    } else if (a.num == 0 && a.den == 0 ) {
        a.num = 0;
        a.den = 0;
    } else {
        int num = a.num;
        int den = a.den;
        int gcd, remainder;
        while(num != 0){
            remainder = den % num;
            den = num;
            num = remainder;
        }
        gcd = den;
        a.num = a.num/gcd;
        a.den = a.den/gcd;
    }
    return (Fraction) { a.num, a.den };
}
