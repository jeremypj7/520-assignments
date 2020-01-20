#ifndef IMAGINARY_H
#define IMAGINARY_H

/*! @file */

/*! \breif complex number object and method definitions
 *
 *  A complex number object is a struct with a real number, denoted real, and
 *  a imaginary number, denoted im. Varions Methods that take complex number and return 
 *  complex number do arithmetical operations on them.
 */

typedef struct {
    double real;
    double im;
} Imaginary;

/*! \complex add 
 *  Add two complex number together
 *  \param a The first summand
 *  \param b The second summand
 */
Imaginary add ( Imaginary a, Imaginary b );

/*! \complex negate
 *  negate complex number 
 *  \param a The  term
 */
Imaginary negate ( Imaginary a );

/*! \complex conjugate
 *  conjugate complex number 
 *  \param a The term
 */
Imaginary conjugate( Imaginary a );

/*! \complex multiply
 *  Multiply two complex number together 
 *  \param a The first term
 *  \param b The second term
 */
Imaginary multiply( Imaginary a, Imaginary b );

/*! \complex magnitude
 *  calculate the magnitude of complex number 
 *  \param a The  term
 */
double magnitude( Imaginary a );

#endif
