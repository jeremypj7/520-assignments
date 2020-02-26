#include "stopwatch.h"
#include <iostream>

/*
 * Code for Question 1 goes here
 */


typedef std::chrono::duration<double,std::ratio<1,1>> seconds_type;

void Stopwatch::init() {
    watch("start", [this](Event& e) {

        start();
    },prior);

    watch("stop", [this](Event& e) {

        stop();
    },prior);


    watch("reset", [this](Event& e) {
        reset();
    },prior);

}

void Stopwatch::start(){
    start_time = high_resolution_clock::now();
}

void Stopwatch::stop(){}

void Stopwatch::reset(){

    duration<double, std::ratio<1,1>> second_time = seconds_type::zero();
}

double Stopwatch::seconds(){
    high_resolution_clock::time_point current_time = high_resolution_clock::now();
    auto millsecond_time = current_time-start_time;
    auto second_time = seconds_type(millsecond_time);

    return second_time.count();

}





