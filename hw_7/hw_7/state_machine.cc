#include <iostream>
#include "elma.h"
#include <vector>

using namespace std;

namespace elma {

    int State::_id_counter = 0;

    StateMachine& StateMachine::set_initial(State& s) {
        _initial = &s;
        return *this;
    }

    StateMachine& StateMachine::add_transition(string event_name, State& from, State& to) {
        _transitions.push_back(Transition(event_name, from, to));
        to._state_machine_ptr = this;
        from._state_machine_ptr = this;
        return *this;
    }

    void StateMachine::init() {
        for (auto transition : _transitions ) {
            watch(transition.event_name(), [this, transition](Event& e) {
                if ( _current->id() == transition.from().id() ) {
                    _current->exit(e);
                    _current = &transition.to();
                    _current->entry(e);
                    if ( !_propagate ) {
                      e.stop_propagation();
                    }
                }
            }, prior_num);
        }
    }

    void StateMachine::start() {
        if ( _initial == NULL ) { 
            throw(Exception("State machine started without an initial state (call set_initial(...) first)"));
        }
        _current = _initial;
        _current->entry(Event("start"));
    }

    void StateMachine::update() {
        _current->during();
    }

    void StateMachine::stop() {}

    json StateMachine::to_json() {
//        for(int i =0; i< _transition.size(); i++) {
//
//            json content = R"(
//                '{
//                    "name": event_name(),
//                    "states": {},
//                    "transitions": [
//                        "from": ,
//                        "to": ,
//                        "when":
//                    ]
//                 }'
//            )"_json;
//        }
//        json value = "hello world";
//        string mt;
//        for (auto transition : _transitions ) {   //  8 transitions
//            mt += " "+ transition.event_name() +" ";
//        }
        string nameofStateMachine = name();   //should return statemachine name;

        //creat vector of State, should be 5 in term of robot
        vector<string> myStates;
        string uniqState;
        for(auto transition : _transitions) {
            uniqState = transition.to().name();
            if (std::find(myStates.begin(), myStates.end(), uniqState) == myStates.end()) {
                // uniqState not in myStates, add it
                myStates.push_back(uniqState);
            }
        }

        vector<map<string, string>> myTransitions;
        map<string, string> eachTransition;
        for(auto transition : _transitions) {
            //mystate += transition.to().name() +" here ";   //should return states name like Find Recharge Station
            eachTransition.insert (pair<string,string>("from",transition.from().name() ) );
            eachTransition.insert (pair<string,string>("to",transition.to().name() ) );
            eachTransition.insert (pair<string,string>("when",transition.event_name()) );
            myTransitions.push_back(eachTransition);
        }



//        for (int i =0; i< _transitions.size(); i++) {
//
//            mt  += " myself ";
//        }
        //value = mystate;
//        value = R"('{ "a": 1, "b": [2,3], "k": { "c": { "d": true } } }')"_json;
        json value = {{"name", nameofStateMachine},{"states", myStates},{"transitions", myTransitions}};

        return value;

    }

};