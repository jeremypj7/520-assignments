#include <stdexcept>
#include <iostream>
#include "elma.h"

namespace elma {

    //! Add a Process to the manager, to be run at a certain frequency.
    //! \param process The process to be scheduled, usually derived from the Process abstract base class
    //! \param period The desired duration of time between updates
    //! \return A reference to the manager, for chaining
    Manager& Manager::schedule(
        Process& process, 
        high_resolution_clock::duration period) {

        process._period = period;
        _processes.push_back(&process); 
        process._manager_ptr = this;            

        return *this;

    }

    //! Add a channel to the manager
    //! \param The channel to be added
    //! \return A reference to the manager, for chaining
    Manager& Manager::add_channel(Channel& channel) {
        _channels[channel.name()] = &channel;
        return *this;
    }

    //! Retrieve a reference to an existing channel. Throws an error if no such channel exists.
    //! \return The channel requested.
    Channel& Manager::channel(string name) {
        if ( _channels.find(name) != _channels.end() ) {
          return *(_channels[name]);
        } else {
            throw Exception("Tried to access an unregistered or non-existant channel.");
        }
    }
    //
//    void swap(auto a, auto b) {
//        auto temp = a;
//        a = b;
//        b= temp;
//    }
    void swap(auto *a, auto *b) {
        auto temp = *a;
        *a = *b;
        *b = temp;
    }
    //! Watch for an event associated with the given name.
    //! For watching events, you would typically register event handlers in your process'
    //! init() method. For example,
    //! @code
    //!     watch("velocity", [this](Event& e) {
    //!         std::cout << "got velocity " << e.value() << std::endl;
    //!     })
    //! @endcode
    //! \param event_name The name of the event
    //! \handler A function or lambda that takes an event and returns nothing.
    // Manager& Manager::watch(std::string event_name, std::function<void(Event&)> handler ) {
    //     event_handlers[event_name].push_back(handler);
    //     return *this;
    // }
    //vector<int> prior;
    Manager& Manager::watch(string event_name, std::function<void(Event&)> handler, int priority) {
        event_handlers[event_name].push_back(handler);
        // prior.push_back(priority);
        //std::cout<<"prior.size()<<std::endl;
        //event_handlers[order(match(event_handlers,prior))];
        //event_handlers[order(prior)];
//        int smallest;
//        //std::cout<<prior.size()<<std::endl;
//        for(int i =0; i< prior.size(); i++) {
//            smallest = prior[i];
//            for(int j = i+1; j<prior.size()-1; j++) {
//                if(smallest >prior[j]) {
//                    smallest = prior[j];
//
//                    std::swap(prior[i],prior[j]);
//                    std::swap(event_handlers[event_name][i], event_handlers[event_name][j]);
//                }
//            }
//        }
        map_prior[event_name].push_back(priority);

        int small;
        //int max;
        //std::cout<<prior.size()<<std::endl;
        for (int i = 0; i < map_prior[event_name].size(); i++) {
            small= map_prior[event_name][i];
            for (int j = i + 1; j < map_prior[event_name].size(); j++) {
                if (small > map_prior[event_name][j]) {
                    small= map_prior[event_name][j];
                    //switch the position
                    swap(&map_prior[event_name][i], &map_prior[event_name][j]);
                    swap(&event_handlers[event_name][i], &event_handlers[event_name][j]);
                }
            }

        }

//        int max;
//        //int max;
//        //std::cout<<prior.size()<<std::endl;
//        for (int i = 0; i < map_prior[event_name].size(); i++) {
//            max = map_prior[event_name][i];
//            for (int j = i + 1; j < map_prior[event_name].size(); j++) {
//                if (max < map_prior[event_name][j]) {
//                    max= map_prior[event_name][j];
//                    //switch the position
//                    swap(&map_prior[event_name][i], &map_prior[event_name][j]);
//                    swap(&event_handlers[event_name][i], &event_handlers[event_name][j]);
//                }
//            }
//
//        }

        return *this;
    }
    
    //! Emit an event associated with a name.
    //! Typically, a process would emit events in its update() method using something like
    //! the following code"
    //! @code
    //!     emit(Event("name", value));
    //! @endcode
    //! where value is any jsonable value. For example, you can write
    //! @code
    //!     emit(Event("velocity", 3.41));
    //! @endcode
    //! \param event The Event to be emitted
    //! \return A reference to the manager for chaining.
    Manager& Manager::emit(const Event& event) {
        Event e = event; // make a copy so we can change propagation
        if ( event_handlers.find(event.name()) != event_handlers.end() ) {
            for ( auto handler : event_handlers[event.name()] ) {
                if ( e.propagate() ) {
                  handler(e);
                }
            }
        }
        return *this;
    }

    //! Apply a function to all processes.
    //! \param f The function to apply. It should take a reference to a process and return void.
    //! \return A reference to the manager, for chaining
    Manager& Manager::all(std::function< void(Process&) > f) {
        for(auto process_ptr : _processes) {
            f(*process_ptr);
        }
        return *this;
    }

    //! Initialize all processes. Usually called before run()
    //! \return A reference to the manager, for chaining
    Manager& Manager::init() {
        return all([](Process& p) { p._init();});
    }

    //! Start all processes. Usually not called directly.
    //! \return A reference to the manager, for chaining
    Manager& Manager::start() {
        return all([this](Process& p) { p._start(_elapsed) ;});
    }    

    //! Stop all processes. Usually not called directly.
    //! \return A reference to the manager, for chaining
    Manager& Manager::stop() {
        return all([](Process& p) { p._stop(); });
    }    

    //! Update all processes if enough time has passed. Usually not called directly.
    //! \return A reference to the manager, for chaining
    Manager& Manager::update() { 
        return all([this](Process& p) {
            if ( _elapsed > p.last_update() + p.period() ) {
                p._update(_elapsed);
            }
        });
    }

    //! Run the manager for the specified amount of time.
    //! \param The desired amount of time to run
    //! \return A reference to the manager, for chaining
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

}