cmake_minimum_required(VERSION 3.13)
project(elma)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(elma
    examples/basic.cc
    examples/driving.cc
    examples/feedback.cc
    examples/microwave.cc
    examples/toggle-switch.cc
    test/channel.cc
    test/event.cc
    test/main.cc
    test/state_machine.cc
    channel.h
    elma.h
    event.h
    exceptions.h
    literals.h
    manager.cc
    manager.h
    process.cc
    process.h
    state.cc
    state_machine.cc
    state_machine.h
    transition.h)
