#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>
// #include <ArduinoSTL.h>
// #include <vector>

// using namespace std;

class Timer
{
private:
    unsigned long sec = 1000;

    unsigned long prew;

    boolean first;
    byte firstCount;

public:
    Timer();
    ~Timer();

    boolean minusCounter(byte &counter);
    byte plusCounter(byte &counter);

    boolean wait(unsigned long set = 500);

    boolean alternation(unsigned long set = 500);

    byte counter(byte counter = 5, boolean invert = false, boolean reset = false);

    boolean ready(byte &counter, boolean reset = false);
};

#endif