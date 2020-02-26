#ifndef stopwatch_h
#define stopwatch_h

#include <iostream>
#include <chrono>
#include "elma.h"
#include <chrono>

using namespace elma;
using namespace std::chrono;
//typedef std::chrono::duration<double,std::ratio<1,1>> seconds_type;

class Stopwatch : public Process {
/*
 * Code for Question 1 goes here
 */

    public:

    Stopwatch(){};

    void init();

    void start();

    void stop();

    void reset();

    void update(){};

    double seconds();


    private:
    int prior;
    high_resolution_clock::time_point start_time,
                                      current_time;


};



#endif