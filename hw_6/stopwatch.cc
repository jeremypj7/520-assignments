//
//  stopwatch.cpp
//  
//
//  Created by Hugh Khiyad on 2/19/19.
//

#include "stopwatch.h"
#include <iostream>


typedef std::chrono::duration<int,std::milli> milliseconds_type;
static duration<double, std::milli> total_time = milliseconds_type::zero();

void Stopwatch::start(){

    start_time = high_resolution_clock::now();

}

void Stopwatch::stop(){
    stop_time = high_resolution_clock::now();
    total_time += stop_time -start_time;
}

void Stopwatch::reset(){
    total_time = milliseconds_type::zero();

}

double Stopwatch::get_minutes(){

    typedef std::chrono::duration<double,std::ratio<60,1>> minutes_type;
    auto x = minutes_type(total_time);
    return x.count();


}

double Stopwatch::get_seconds(){
    typedef std::chrono::duration<double,std::ratio<1,1>> seconds_type;
    auto y = seconds_type(total_time);
    return y.count();

}

double Stopwatch::get_milliseconds(){
    return total_time.count();

}

double Stopwatch::get_nanoseconds(){
    typedef std::chrono::duration<double,std::ratio<1,1000000000>> nanoseconds_type;
    auto z = nanoseconds_type(total_time);
    return z.count();

}
