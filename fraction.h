#ifndef FRACTION_H
#define FRACTION_H

/*! @file */

/*! \breif Fraction object and method definitions
 *
 *  A fraction object is a struct with a numerator, denoted num, and
 *  a denominator, denoted den. Varions Methods that take fractions and return 
 *  fractions do arithmetical operations on them.
 */
typedef struct {
    int num;
    int den;
} Fraction;

/*! \fn add 
 *  Add two fractions together
 *  \param a The first summand
 *  \param b The second summand
 */
Fraction add ( Fraction a, Fraction b );

/*! \fn multiply
 *  Multiply two fractions together (does not reduce)
 *  \param a The first term
 *  \param b The second term
 */
Fraction multiply ( Fraction a, Fraction b );

/*! \fn reduce
 * find greatest common dividor gcd
 * divide num with gcd
 * divide den with gcd
 *param a the term
 */
Fraction reduce ( Fraction a );

#endif