/*
#include <math.h>
#include <float.h> 
#include <assert.h>
#include "double_array.h"
#include "typed_array.h"
#include "imaginary.h"
#include "gtest/gtest.h"

namespace {

    class Point {
        public:
        Point(double x, double y, double z) : x(x), y(y), z(z) {};
        Point() : x(0), y(0), z(0) {};

        double magnitude(const Point &p) {
            return sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
        }

        double x, y, z;
    };

    double magnitude(const Point &p) {
        return sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
    }

    bool operator< (const Point& lhs, const Point& rhs) {
        double m1 = magnitude(lhs),
                m2 = magnitude(rhs);
        if ( m1 < m2 ) {
            return 1;
        } else if ( m1 > m2 ) {
            return -1;
        } else {
            return 0;
        }
    }    

    Point &smaller(Point &p, Point &q) {
        if ( magnitude(p) <= magnitude(q) ) {
            return p;
        } else {
            return q;
        }
    }

    Point &f() {
        Point p = {1,2,3};
        Point &q = p;
        return q;
    }

    std::ostream &operator<<(std::ostream &os, const Point &p)
    {
        os << '{' << p.x << "," << p.y << "," << p.z << '}';
        return os;
    }

    double invert(int x, int y) {
        if ( x == 0 ) {
            throw std::invalid_argument("First argument cannot be zero");
        } else {
            return y/x;
        }
    }    

    class Imaginary {
        public:
        Imaginary(double x, double y) : re(x), im(y) {}
        private:
        double re, im;
    }; 

    template<typename T>
    int compare(const T& x, const T& y) {
        if ( x < y ) {
            return -1;
        } else if ( y < x ) {
            return 1;
        } else {
            return 0;
        }
    }

    TEST(Templates,Functions) {
        compare<int>(1,2);
        compare<double>(3.0, 4.0);
        compare<Point>((Point){1,2,3}, (Point) {3,-4,2});
    }

    TEST(Im,Im) {
        Imaginary x();
    }

    TEST(References,References) {
        Point p = { 0,3,4 }, q;
        Point &r = smaller(p, q);
        ASSERT_DOUBLE_EQ(magnitude(p), 5);
        ASSERT_EQ(r.x, 0);
        ASSERT_EQ(r.y, 0);
        ASSERT_EQ(r.z, 0);
        r.x = -1;
        ASSERT_DOUBLE_EQ(r.x, q.x);
    }

    TEST(Except,Except) {
        try {
            invert(0,1);
            ASSERT_EQ(true,false);
        } catch (std::invalid_argument e ) {
            ASSERT_STREQ(e.what(), "First argument cannot be zero");
        }
    }

    TEST(Memory,NewDelete) {
        int * x = new int;
        double * p = new double[10];
        delete x;
        delete[] p;        
    }

    TEST(DoubleArray, ConstructSetGet) {       
        DoubleArray a, b(0,1,0.1);
        auto c = new DoubleArray();
        a.set(4, 1);
        ASSERT_EQ(a.get(4), 1); 
        double x = 0;
        for ( int i=0; i<b.size(); i++ ) {
            ASSERT_EQ(b.get(i),x);
            x+=0.1;
        }
        delete c;
    }

    TEST(DoubleArray, Assignment) {
        DoubleArray a, b;  
        a.set(4, 1);
        b = a;
        ASSERT_EQ(a.get(4), 1);
        ASSERT_EQ(b.get(4), 1);                
    }    

    TEST(DoubleArray, CopyConstructor) {
        DoubleArray a;
        a.set(4, 1);        
        DoubleArray b(a);
        ASSERT_EQ(a.get(4), 1);
        ASSERT_EQ(b.get(4), 1);            
    }

    TEST(DoubleArray, Exceptions) {
        DoubleArray a;
        ASSERT_THROW(a.set(-1,0), std::range_error);
        ASSERT_THROW(a.get(-1), std::range_error);
        try {
            a.get(-1);
            ASSERT_EQ(0,1); // Should not reach this code
        } catch ( std::range_error e ) {
            ASSERT_STREQ(e.what(), "Negative index in array");
        }
    }

    TEST(TypedArray, Construction) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(20, Point(3,4,5));
        ASSERT_EQ(b.get(0).x, 1);
        ASSERT_EQ(b.get(1).y, 3);
        ASSERT_EQ(b.get(20).z, 5);
    }

    TEST(Assert,Assert) {
        // assert(0);
        ASSERT_DEATH(int x = 1+1,"");
        // try {
        //     assert(0);
        //     ASSERT_EQ(0,1);
        // } catch (...) {
        //     ASSERT_EQ(1,1);
        // }
    }

    TEST(TypedArray, Matrix) {

        TypedArray<TypedArray<double>> m;

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                m.get(i).set(j,0.5*i*j);
            }
        }

        std::cout << m << "\n"; 

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                ASSERT_DOUBLE_EQ(m.get(i).get(j),0.5*i*j);
            }
        }

    }

    TEST(TypeArray, pushPop) {
        TypedArray<double> a;
        a.set(0,0.0);

        a.set(1,1.0);

        a.push(2);

        ASSERT_EQ(a.get(2), 2.0);
 
        a.push_front(100.0);

        ASSERT_EQ(a.get(0), 100.0);   // 100, 0, 1, 2

        double t = a.pop();
        ASSERT_EQ(t,2.0);
        
        double m = a.pop_front();
        ASSERT_EQ(m,100);   


    }

    TEST(TypedArray, Concat) {
        TypedArray<int> a;
        a.set(0, 0);
        a.set(1, 1);

        TypedArray<int> b = a.concat(a).concat(a);  //yields [0,1,0,1,0,1]

        ASSERT_EQ(b.get(2), 0);
    }

    TEST(Imaginary, Assignment) {
        Imaginary a; 
        a.(3.0, 4.0);
        //double real = a.re();
        ASSERT_EQ(a.re(), 3.0);

    }

}
*/

#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "imaginary.h"
#include "typed_matrix.h"
#include "gtest/gtest.h"
#include <iostream>
using std::cout;
using std::endl;

namespace {
    class Point {
        public:
        Point(double x, double y, double z) : x(x), y(y), z(z) {};
        Point() : x(0), y(0), z(0) {};

        double magnitude(const Point &p) {
            return sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
        }

        double x, y, z;
    };
    /*
    TEST(TypeArray, pushPop) {
    TypedArray<double> a;
    a.set(0,0.0);

    a.set(1,1.0);

    a.push(2);

    ASSERT_EQ(a.get(2), 2.0);

    a.push_front(100.0);

    ASSERT_EQ(a.get(0), 100.0);   // 100, 0, 1, 2

    double t = a.pop();
    ASSERT_EQ(t,2.0);
    
    double m = a.pop_front();
    ASSERT_EQ(m,100);   


    }

    */


    TEST(TypedArray, Push) {
        TypedArray<int> a;
        a.push(1);
        a.push(3);
        a.push(5);
        a.push(7);
        a.push(9);
        EXPECT_EQ(a.get(0), 1);
        EXPECT_EQ(a.get(1), 3);
        EXPECT_EQ(a.get(2), 5);
        EXPECT_EQ(a.get(3), 7);
        EXPECT_EQ(a.get(4), 9);
    }
    TEST(TypedArray, Push_front){
        TypedArray<double> a;
        a.push_front(2.0);
        a.push_front(4.0);
        a.push_front(6.0);
        a.push_front(8.0);
        a.push_front(10.0);
        EXPECT_DOUBLE_EQ(a.get(0), 10.0);
        EXPECT_DOUBLE_EQ(a.get(1), 8.0);
        EXPECT_DOUBLE_EQ(a.get(2), 6.0);
        EXPECT_DOUBLE_EQ(a.get(3), 4.0);
        EXPECT_DOUBLE_EQ(a.get(4), 2.0);
    }

    TEST(TypeArray, Pop){
        TypedArray<double> a;
        a.push(2.0);
        a.push(4.0);
        a.push(6.0);
        EXPECT_DOUBLE_EQ(a.get(2), 6.0);
        a.pop();
        a.push(12.0);
        EXPECT_DOUBLE_EQ(a.get(2), 12.0);

    }

    TEST(TypeArray, Pop_front){
        TypedArray<int> a;
        a.push_front(7);
        a.push_front(5);
        EXPECT_EQ(a.get(0), 5);
        a.pop_front();
        a.push_front(11);
        EXPECT_EQ(a.get(0), 11);
    }

    TEST(TypedArray, Concat){
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        TypedArray<int> b;
        b.set(0,22);
        b.set(1,11);
        TypedArray<int> c = a.concat(b).concat(a); // yields [0,1,22,11,0,1]
        EXPECT_EQ(c.get(0), 0);
        EXPECT_EQ(c.get(1), 1);
        EXPECT_EQ(c.get(2), 22);
        EXPECT_EQ(c.get(3), 11);
        EXPECT_EQ(c.get(4), 0);
        EXPECT_EQ(c.get(5), 1);
    }

    TEST(Imaginary, Basic){
        Imaginary a(3.0, 4.0);
        EXPECT_DOUBLE_EQ(a.im(), 4.0);
        EXPECT_DOUBLE_EQ(a.re(), 3.0);
        Imaginary b = a.conjugate();
        EXPECT_DOUBLE_EQ(b.im(), -4.0);
        EXPECT_DOUBLE_EQ(b.re(), 3.0);
        EXPECT_DOUBLE_EQ(a.magnitude(), 5.0);
    }

    TEST(Imaginary, Add_assign){
        Imaginary a(3.0, 4.0);
        Imaginary b(1.0, -1.0);
        a+=b;
        EXPECT_DOUBLE_EQ(a.im(), 3.0);
        EXPECT_DOUBLE_EQ(a.re(), 4.0);
        EXPECT_DOUBLE_EQ(b.im(), -1.0);
        EXPECT_DOUBLE_EQ(b.re(), 1.0);
    }

    TEST(Imaginary, Mult_assign){
        Imaginary a(1.0, 2.0);
        Imaginary b(3.0, -1.0);

        //std::cout<<a.re()<<","<<a.im()<<"   here"<<std::endl;
        //std::cout<<b.re()<<","<<b.im()<<"   here"<<std::endl;
        //std::cout<<a.re() * b.im()+ a.im() * b.re()<<"   here"<<std::endl;
        a*=b;
        //std::cout<<a.re()<<","<<a.im()<<"   here"<<std::endl;
        EXPECT_DOUBLE_EQ(a.im(), 5.0);
        EXPECT_DOUBLE_EQ(a.re(), 5.0);
        EXPECT_DOUBLE_EQ(b.im(), -1.0);
        EXPECT_DOUBLE_EQ(b.re(), 3.0);
    }

    TEST(Imaginary, Equalilty){
        Imaginary a(1.0, 2.0);
        Imaginary b(3.0, -1.0);
        EXPECT_TRUE(a==Imaginary(1.0, 2.0));
        EXPECT_FALSE(a==b);
    }

    TEST(Imaginary, Add){
        Imaginary a(4.0, 3.0);
        Imaginary b(3.0, 11.0);
        Imaginary c = a + b;
        EXPECT_DOUBLE_EQ(c.im(), 14.0);
        EXPECT_DOUBLE_EQ(c.re(), 7.0);
    }

    TEST(Imaginary, Mult){
        Imaginary a(4.0, 3.0);
        Imaginary b(3.0, 11.0);
        Imaginary c = a * b;
        EXPECT_DOUBLE_EQ(c.im(), 53.0);
        EXPECT_DOUBLE_EQ(c.re(), -21.0);
    }

    TEST(TypedMatrix, Basic){
        cout <<1<<endl;
        TypedMatrix<int> a;
        cout <<2<<endl;
        EXPECT_EQ(a.get(0,0), int());
        cout <<3<<endl;
        EXPECT_ANY_THROW(a.get(0,1));
        cout <<4<<endl;
    }

    TEST(TypedMatrix, Mult_dimension){
        TypedMatrix<double> a(3,5);
        EXPECT_DOUBLE_EQ(a.get(4,2), double());
        EXPECT_ANY_THROW(a.get(5,3));
        a.set(1, 1, 110.0 );
        //std::cout<<a<<std::endl;
        EXPECT_DOUBLE_EQ(a.get(1,1), 110.0);
    }

    TEST(TypeMatrix, Copy){
        TypedMatrix<double> a(2,3);
        a.set(1,1,3.5);
        TypedMatrix<double> b;
        b = a;
        b.set(1,1,555);
        //std::cout<<a<<std::endl;
        //std::cout<<b<<std::endl;
        EXPECT_DOUBLE_EQ(a.get(1,1), 3.5);
        //TypedMatrix<double> c = b;
    }

    TEST(TypedMatrix, Add_assign){
        TypedMatrix<Imaginary> a(2, 1);
        TypedMatrix<Imaginary> b(2, 1);

        a.set(0, 0, Imaginary(2.0, -3.0));
        a.set(0, 1, Imaginary(1.0, 5.0));
        b.set(0, 0, Imaginary(-2.0, 3.0));
        b.set(0, 1, Imaginary(4.0, 0.0));
        a+=b;
        EXPECT_EQ(a.get(0,0), Imaginary(0.0, 0.0));
        EXPECT_EQ(a.get(0,1), Imaginary(5.0, 5.0));
        EXPECT_EQ(b.get(0,0), Imaginary(-2.0, 3.0));
        EXPECT_EQ(b.get(0,1), Imaginary(4.0, 0.0));
        TypedMatrix<Imaginary> c(2,4);
        EXPECT_ANY_THROW(a+=c);

    }

    TEST(TypedMatrix, Mult_assign){
        TypedMatrix<int> a(2,3);
        TypedMatrix<int> b(2,3);
        for(int i=0; i<3; i++){
            for(int j=0; j<2; j++){
                a.set(i,j,i*2+j);
                b.set(i,j,2);
            }
        }
        a*=b;
        for(int i=0; i<3; i++){
            for(int j=0; j<2; j++){
                EXPECT_EQ(a.get(i,j),2*(i*2+j));
            }
        }
        TypedMatrix<int> c(2,4);
        EXPECT_ANY_THROW(a*=c);
    }

    TEST(TypedMatrix, Euquality){
        TypedMatrix<Imaginary> a(2, 1);
        TypedMatrix<Imaginary> b(2, 1);
        TypedMatrix<Imaginary> c(2, 2);

        a.set(0, 0, Imaginary(2.0, -3.0));
        a.set(0, 1, Imaginary(1.0, 5.0));
        b.set(0, 0, Imaginary(2.0, -3.0));
        b.set(0, 1, Imaginary(1.0, 5.0));
        EXPECT_TRUE(a==b);
        EXPECT_FALSE(a==c);
    }

    TEST(TypedMatrix, add){
        TypedMatrix<int> a(2, 2);
        TypedMatrix<int> b(2, 2);
        for(int i=0; i<2; i++){
            for(int j=0; j<2; j++){
                a.set(i,j,i*2+j+1);
                b.set(i,j,4-(i*2+j+1));
            }
        }
        TypedMatrix<int> c;
        c = a+b;

        EXPECT_EQ(c.get(0,0), 4);


        EXPECT_EQ(c.get(0,1), 4);

        EXPECT_EQ(c.get(1,0), 4);

        EXPECT_EQ(c.get(1,1), 4);

        TypedMatrix<int> d(3,2);

        EXPECT_ANY_THROW(c=a+d);
    }

    TEST(TypedMatrix, Mult1){
        TypedMatrix<int> a(2, 1);
        TypedMatrix<int> b(1, 2);
        a.set(0, 0, 3.0);
        a.set(0, 1, 4.0);
        b.set(0, 0, 3.0);
        b.set(1, 0, 4.0);
        TypedMatrix<int> c;
        c = a*b;
        std::cout<<c<<std::endl;
        EXPECT_DOUBLE_EQ(c.get(0,0), 25.0);
        EXPECT_ANY_THROW(c.get(0,1));
        TypedMatrix<int> d(1,3);
        EXPECT_ANY_THROW(a*d);
    }

    TEST(TypedMatrix, Mult2){
        TypedMatrix<Imaginary> a(2, 1);
        TypedMatrix<Imaginary> b(1, 2);
        a.set(0, 0, Imaginary(2.0, 1.0));
        a.set(0, 1, Imaginary(1.0,-1.0));
        b.set(0, 0, Imaginary(2.0, -1.0 ));
        b.set(1, 0, Imaginary(1.0, 0.0));
        TypedMatrix<Imaginary> c;
        c = a*b;
        //std::cout<<c<<std::endl;
        EXPECT_TRUE(c.get(0,0)==Imaginary(6, -1));
        EXPECT_ANY_THROW(c.get(0,1));
        TypedMatrix<Imaginary> d(1,3);
        EXPECT_ANY_THROW(a*d);
    }

}
