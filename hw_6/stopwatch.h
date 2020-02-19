//
//  stopwatch.h
//  
//
//  Created by Hugh Khiyad on 2/19/19.
//

#ifndef stopwatch_h
#define stopwatch_h
#include <chrono>

using namespace std::chrono;


class Stopwatch  {

    public:


        Stopwatch()  {}

        void start();

        void stop();

        void reset();

        double get_minutes();

        double get_seconds();

        double get_milliseconds();

        double get_nanoseconds();




    private:

        high_resolution_clock::time_point start_time,
                                           stop_time;

};

#endif /* stopwatch_h */
