#include "gtest/gtest.h"
//#include "robot.h"
#include "rover.h"
#include "stopwatch.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <tuple>
#include <map>

#define DAY_MOVE_STEP 70
#define X_WATER 154
#define Y_WATER 100
using nlohmann::json;
using namespace std::chrono;
using namespace elma;
using namespace std;

double tolerance = 0.01;
/*!!
 * Here we use your StopWatch class to time something.
 */
//TEST(Question1, StopWatch) {
//    Manager m;
//
//    Stopwatch watch = Stopwatch();
//
//    m.schedule(watch, 10_ms)
//    .init()
//    .start();
//
//    std::cout << watch.seconds() << std::endl;
//
//    m.emit(Event("start"));
//
//    std::this_thread::sleep_for(std::chrono::milliseconds(500));
//
//    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);
//
//    std::cout << watch.seconds() << std::endl;
//
//    std::this_thread::sleep_for(std::chrono::milliseconds(500));
//
//    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);
//
//    std::cout << watch.seconds() << std::endl;
//
//    m.emit(Event("stop"));
//
//}


/*!!
 * Here we use your Rover class to give the robot
 * a little trial and see what state its in.
 *
 * Variants of tests will include more than one robot,
 * non-sense events, and varying event sequences.
 */


//TEST(Question2, RobotEnvironment1) {
//
//    // create a new robot
//    Robot robot = Robot("What a very nice robot");
//    // Robot robot = Robot(); // << this should also work
//
//    // init manager
//    Manager m;
//    m.schedule(robot, 10_ms)
//    .init()
//    .start()
//    .emit(Event("start"));
//
//
//    string wander = "Wander";
//    string noise = "Make Noise";
//    string evade = "Evade";
//
//    /*
//     * Send signals to robot and test
//     */
//    std::cout << robot.current().name() << std::endl;
//    EXPECT_EQ(robot.current().name(), wander.c_str());
//
//    m.emit(Event("intruder detected"));
//    std::cout << robot.current().name() << std::endl;
//    EXPECT_EQ(robot.current().name(), noise.c_str());
//
//    m.emit(Event("proximity warning"));
//    std::cout << robot.current().name() << std::endl;
//    EXPECT_EQ(robot.current().name(), evade.c_str());
//
//    m.emit(Event("battery full"));
//    std::cout << robot.current().name() << std::endl;
//    EXPECT_EQ(robot.current().name(), evade.c_str());
//
//    json t = robot.to_json();
//    std::cout<< t << std::endl;
//}

TEST(Question, Final) {
    bool foundwater = false;
    string foundwater_tf;
    string camerastatus;
    map<int, tuple <int, int, bool>> data;
    tuple <int, int, bool> subdata;
    static int x = 0;
    static int y = 0;
    static int location_point = 0;

    // create a new robot
    Rover rover = Rover("mission impossible");
    // Robot robot = Robot(); // << this should also work
    Camera camera;

    // init manager
    Manager m;
    //Process p("Mission Impossible"), q("Terminator");m.schedule(p, 10_ms)
    m.schedule(camera, 10_ms);
    m.schedule(rover, 10_ms)
    .init()
    .start()
    .emit(Event("start"));


    string wander = "Wander";
    string findwater = "Find Water";
    string collectwater = "Collect Water";
    string opencamera = "Open Camera";
    string closecamera = "Close Camera";
    //string sendvideoback = "Send "


/*!!
* rover arrives in this planet, start
*/

    subdata = make_tuple(x,y, false);
    data[location_point] = subdata;





/*!!
* alien detected, turn on the camera
*/

    m.emit(Event("alien detected"));

    x++;
    location_point++;

    m.emit(Event("camera set up"));
    ASSERT_EQ(true, camera.running);
    subdata = make_tuple(x,y, false);
    data[location_point] = subdata;


/*!!
* record video
*/
    m.emit(Event("record video"));

    x++;
    location_point++;
    m.emit(Event("camera set up"));
    ASSERT_EQ(false, camera.running);
    subdata = make_tuple(x,y, false);
    data[location_point] = subdata;


/*!!
* send video back
*/
m.emit(Event("send video back"));
    ASSERT_EQ(false, camera.running);

    //m.emit(Event("mission start"));
    x++;
    location_point++;
    subdata = make_tuple(x,y, false);
    data[location_point] = subdata;


    for(int j = 0; j<DAY_MOVE_STEP; j++) {

        if(x!=X_WATER && y !=Y_WATER) {

            /*!!
            * sandstorm detected
            */
            m.emit(Event("sandstorm detected"));

                location_point++;
                y++;
                subdata = make_tuple(x, y, false);
                data[location_point] =
                subdata;
            /*!!
            * reset
            */

            m.emit(Event("reset"));

                location_point++;
                x++;
                subdata = make_tuple(x, y, false);
                data[location_point] =
                subdata;


            /*!!
            * sandstorm detected
            */

            m.emit(Event("sandstorm detected"));

                location_point++;
                y++;
                subdata = make_tuple(x, y, false);
                data[location_point] =
                subdata;
            /*!!
            * wind get stronger
            */

            m.emit(Event("wind get stronger"));

                location_point++;
                x++;
                subdata = make_tuple(x, y, false);
                data[location_point] =
                subdata;

            /*!!
            * reset
            */

            m.emit(Event("reset"));

                location_point++;
                x++;
                subdata = make_tuple(x, y, false);
                data[location_point] =
                subdata;

        } else {
            /*!!
            *
            * mission start, to find water
            */
            m.emit(Event("found water"));

            location_point++;
            x++;
            subdata = make_tuple(x,y, true);
            data[location_point] = subdata;
            break;


        }
}
///*!!
// *
//* mission start, to find water
//*/
//    m.emit(Event("found water"));
//
//    location_point++;
//    x++;
//    subdata = make_tuple(x,y, true);
//    data[location_point] = subdata;
//
//    //m.emit(Event("mission complete"));




    std::cout<<"========"<<std::endl;
    for(int i = 0; i<data.size(); i++) {
        if(get<2>(data[i]) ==true) {
            foundwater_tf = "true";
        } else {
            foundwater_tf = "false";
        }

        std::cout<<"index: "<< i<<", position("<< get<0>(data[i])<<", " <<get<1>(data[i])<<"),"<< " find water: "<<foundwater_tf <<std::endl;

    }

}

///*!!
// * Here we will create various StateMachines and validate the JSON from the to_json method.
// */
//TEST(Question3, to_json) {
//    /*
//     * coming soon... but this is straight-forward to test. At this point, you shouldn't
//     * need help writing tests for this one.
//     */
//}

/*!!
 * Here we will test priority of watching events. Events with higher priority should always be
 * executed before events of lower priority.
 *
 * Test variants will include testing various events of lower and higher priority.
 */


//class TestPriority : public Process {
//    public:
//    TestPriority(std::string name) : Process(name) {}
//    void init() {
//        std::cout<<"why"<<std::endl;
//        watch("hello", [this](const Event& e){
//            prior_Name = "priority 2";
//        }, 2);
//
//        watch("I am here", [this](const Event& e) {
//            prior_Name = "priority 5";
//        }, 5);
//
//        watch("today is Sunday", [this](const Event& e){
//            prior_Name = "priority 12";
//        }, 12);
//
//        watch("A sunny day", [this](const Event& e){
//            num = 7;
//        }, 7);
//
//        watch("I like him", [this](const Event& e){
//            num = 24;
//        }, 24);
//
//
//    }
//    void start() {}
//    void update() {
//        emit(Event("hello"));
//        std::cout<<prior_Name<<std::endl;
//        ASSERT_EQ("priority 2", prior_Name);
//
//        emit(Event("today is Sunday"));
//        std::cout<<prior_Name<<std::endl;
//        ASSERT_EQ("priority 12", prior_Name);
//
//        emit(Event("A sunny day"));
//        std::cout<<num<<std::endl;
//        ASSERT_EQ(7, num);
//
//        emit(Event("I like him"));
//        std::cout<<num<<std::endl;
//        ASSERT_EQ(24, num);
//
//    }
//    void stop() {}
//
//    private:
//       string prior_Name;
//       int num;
//
//};
//
//TEST(Question4, WatchPriority) {
//    /*
//     * coming soon...
//     */
//    TestPriority p("WatchPriority");
//    //
//    Manager m;
//    m.schedule(p, 10_ms)
//     .init();
//    std::cout<<"here"<<std::endl;
//
//     //p.init();
//     //p.start();
//     std::cout<<"here again"<<std::endl;
//    p.update();
//    std::cout<<"here again 2"<<std::endl;
//}



