#include <stdexcept>
#include <iostream>
#include "elma.h"

using namespace std;

namespace elma {

    Manager& Manager::schedule(
        Process& process, 
        high_resolution_clock::duration period) {

        process._period = period;
        _processes.push_back(&process); 
        process._manager_ptr = this;            

        return *this;

    }

    Manager& Manager::drop(Process&) {

    }

    Manager& Manager::add_channel(Channel& channel) {
        _channels[channel.name()] = &channel;
        return *this;
    }

    Channel& Manager::channel(string name) {
        if ( _channels.find(name) != _channels.end() ) {
          return *(_channels[name]);
        } else {
            throw std::domain_error("Tried to access an unregistered or non-existant channel.");
        }
    }

    Manager& Manager::all(std::function< void(Process&) > f) {
        for(auto process_ptr : _processes) {
            f(*process_ptr);
        }
        return *this;
    }

    Manager& Manager::init() {
        return all([](Process& p) { p._init();});
    }

    Manager& Manager::start() {
        return all([this](Process& p) { p._start(_elapsed) ;});
    }    

    Manager& Manager::stop() {
        return all([](Process& p) { p._stop(); });
    }    

    Manager& Manager::update() { 
        return all([this](Process& p) {
            if ( _elapsed > p.last_update() + p.period() ) {
                p._update(_elapsed);
            }
        });
    }

    Manager& Manager::run(high_resolution_clock::duration runtime) {

        _start_time = high_resolution_clock::now();
        _elapsed = high_resolution_clock::duration::zero();
        start();        

        while ( _elapsed < runtime ) {
            update();
            _elapsed = high_resolution_clock::now() - _start_time;
        }

        stop();

        return *this;

    }

    map<string, tuple<string, double, double, int>> Manager::ps() {
        map <string, tuple<string, double, double, int>> info;
        // TODO: Question 5
        for(int i =0; i<_processes.size(); i++) {

            string current_status;
            string my_status = to_string(_processes[i]->_status);
            if(my_status=="0") {
                current_status = "UNINITIALIZED";

            }else if(my_status=="1") {
                current_status = "STOPPED";
            } else{
                current_status = "RUNNING";
            }

            info.insert(pair<string, tuple<string, double, double, int>>(_processes[i]->_name,
                                                                 make_tuple(current_status, (_processes[i]->_last_update.count())/1000000,
                                                                                        _processes[i]->delta(),
                                                                                        _processes[i]->_num_updates)));
        }

        return info;
    }
}