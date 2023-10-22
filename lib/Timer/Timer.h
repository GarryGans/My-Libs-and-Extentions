#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>
// #include <ArduinoSTL.h>
// #include <vector>

// using namespace std;

class Timer
{
private:
    unsigned long second = 1000;

    unsigned long prew;

    boolean first;

public:

    Timer();
    ~Timer();

    boolean wait(unsigned long set = 500, boolean reset = false);

    byte minusCounter(byte &counter);

    byte plusCounter(byte &counter);

    byte reduceCounter(byte counter, boolean reset, int sec = 1000);

    byte restoreCounter(byte counter, boolean reset = false, int sec = 1000);

    byte counter(byte counter, boolean increase, boolean reset = false, int sec = 1000);

    boolean blink(unsigned long set = 500);

    boolean ready(byte counter, boolean reset = false);
};

#endif