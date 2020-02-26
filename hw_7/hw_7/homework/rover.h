#include <iostream>
#include <chrono>
#include "elma.h"

using namespace elma;



class Camera : public Process {

public:
    Camera() : Process("camera") {}
    void init() {
            watch("on", [this](Event& e) {
                running = true;
            }, prior);
            watch("off", [this](Event &e) {
                running = false;
            },prior);
//            watch("camera level set", [this](Event &e) {
//                running = false;
//            },prior);

    }
    void start() {
            running = false;
            camera_level = 0;
    }
    void update() {}
    void stop() {}

    bool running;
    double camera_level;

private:
    int prior;

};


class RoverState : public State {
public:

};

class Wander : public State {
public:
    Wander() : State("Wander") {}

    void entry(const Event& e) {}
    void during() {}
    void exit(const Event& e) {}


};

class FindWater : public State {
public:
    FindWater() : State("Find Water") {}
    void entry(const Event& e) {}
    void during() {}
    void exit(const Event& e) {}
};

class CollectWater : public State {
public:
    CollectWater() : State("Collect Water") {}
    void entry(const Event& e) {}
    void during() {}
    void exit(const Event& e) {}
};

class CloseSolarPanels : public State {
public:
    CloseSolarPanels() : State("Close Solar Panels") {}
    void entry(const Event& e) {}
    void during() {}
    void exit(const Event& e) {}
};

class Sleep : public State {
public:
    Sleep() : State("Sleep") {}
    void entry(const Event& e) {}
    void during() {}
    void exit(const Event& e) {}
};

class OpenCamera : public State {
public:
    OpenCamera() : State("Open Camera") {}
    void entry(const Event& e) {

    }
    void during() {}
    void exit(const Event& e) {
            if( e.name() == "camera set up" ) {
                    emit(Event("on"));
            }
    }
};

class CloseCamera : public State {
public:
    CloseCamera() : State("Close Camera") {}
    void entry(const Event& e) {

    }
    void during() {}
    void exit(const Event& e) {
            if ( e.name() == "camera set up" ) {
                    emit(Event("off"));
            }
    }
};



class Rover : public StateMachine {
public:

    Rover(std::string name):StateMachine(name) {
        set_initial(wander_);
        add_transition("mission start", wander_, find_water_);
        add_transition("found water", find_water_, collect_water_);
        add_transition("mission complete", collect_water_, wander_);

        add_transition("sandstorm detected", wander_, close_solar_panels_);
        add_transition("wind get stronger", close_solar_panels_, sleep_);
        add_transition("reset", sleep_, close_solar_panels_);
        add_transition("reset", close_solar_panels_, wander_);

        add_transition("start mission", sleep_, find_water_);


        add_transition("alien detected", wander_, open_camera_);
        add_transition("record video", open_camera_, close_camera_);
        add_transition("send video back", close_camera_, wander_);

        add_transition("camera set up", open_camera_, open_camera_);
        add_transition("camera set up", close_camera_, close_camera_);
    }




private:

    Wander wander_;
    FindWater find_water_;
    CollectWater collect_water_;
    CloseSolarPanels close_solar_panels_;
    Sleep sleep_;
    OpenCamera open_camera_;
    CloseCamera close_camera_;


};




