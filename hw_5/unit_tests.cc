#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include "utilities.h"
#include "imaginary.h"
#include "typed_matrix.h"
#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>


namespace {

  using namespace std;

  TEST(Vector,Vector) {
      vector<double> v;
      for (int i=0; i< 50; i++) {
        v.push_back(i);

      }

      for (double &i : v)
        i *= i;
      for (double &i : v)
        std::cout << i << " ";

      std::cout << "\n";

      std::cout << v.capacity() << "\n";

      v.shrink_to_fit();

      std::cout << v.capacity() << "\n";
      v.push_back(1);
      std::cout << v.capacity() << "\n";

  }

  TEST(Vector, Sort) {
      vector<double> v = {-100, 1, 2, -3, 50};
      vector<double> v1 = sort_by_magnitude(v);


      EXPECT_DOUBLE_EQ(v1[0], 1);
      EXPECT_DOUBLE_EQ(v1[1], 2);
      EXPECT_DOUBLE_EQ(v1[2], -3);
      EXPECT_DOUBLE_EQ(v1[3], 50);
      EXPECT_DOUBLE_EQ(v1[4], -100);

  }


  TEST(Read_matrix_cvs, Matrix) {


        TypedMatrix<double> a;
        a = read_matrix_csv("data.csv");
        TypedMatrix<double> b(5,2);
        for(int i=0; i<2; i++){
            for(int j=0; j<5; j++){
                b.set(i,j,j+i*5+1);
            }
        }

        EXPECT_DOUBLE_EQ(a.get(0,0), 1);
        EXPECT_DOUBLE_EQ(a.get(0,2), 3);
        EXPECT_DOUBLE_EQ(a.get(1,2), 8);


        EXPECT_TRUE(a==b);

  }

  TEST(MAP, Occurrence) {
      map<string, int>  a;
      a = occurrence_map("words.txt");

      for(auto i = a.begin(); i != a.end(); i++) {
          std::cout << i->first << ": " << i->second << "\n";
      }

  }

  TEST(Read_matrix, WriteFile){

      TypedMatrix<double> a(5,2);
      for(int i=0; i<2; i++){
          for(int j=0; j<5; j++){
              a.set(i,j,j+i*5+1);
          }
      }
      write_matrix_csv(a,"second.csv");

  }

    TEST(TypedMatrix, Basic){
        //cout <<1<<endl;
        TypedMatrix<int> a;
        //cout <<2<<endl;
        EXPECT_EQ(a.get(0,0), int());
        //cout <<3<<endl;
        EXPECT_ANY_THROW(a.get(0,1));
        //cout <<4<<endl;
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