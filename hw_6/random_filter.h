// Backbone code for HW6_Question4

#ifndef RANDOM_FILTER_H
#define RANDOM_FILTER_H

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "elma.h"


using std::string;
using std::vector;

using std::cout;
using std::endl;

namespace random_filter {
    class Random : public elma::Process {
      public: 
        // you may initialize other private data in constructor
        Random(string name) : Process(name) {}
        void init() {}
        void start() {}
        void update() {
            // TODO
            double rand_num = (double) rand()/ (double) RAND_MAX;
            channel("link").send(rand_num);
        }
        void stop() {}
      private:
        // add any private variable you need here
    };


    class Filter : public elma::Process {
      public:
        // you may initialize other private data in constructor
        Filter(std::string name, vector<double> weight) :  Process(name) { _weight = weight;}


        void init() {
            // TODO

            if(_weight.size()>channel("link").capacity()){
                channel("link").change_capacity(_weight.size());
            }

        }
        void start() {}
        void update() {
            // TODO
            _value = 0;
            if(channel("link").nonempty()){

                vector<double> vec = channel("link").latest(_weight.size());

                for(int i =0; i<vec.size(); i++) {
                    _value+= vec[i]*_weight[i];

                }

            }
        }
        inline double value() {
            // TODO
            return _value;
        }
        void stop() {}
      private:
        // add any private variable you need here
        double _value;
        vector<double> _weight;
    };
}

#endif