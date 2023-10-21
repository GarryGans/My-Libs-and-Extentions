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

public:
    Timer();
    ~Timer();

    boolean wait(unsigned long set = 500, boolean reset = false);

    byte minusCounter(byte &counter);

    byte plusCounter(byte &counter);

    byte reduceCounter(byte counter, boolean reset);

    byte restoreCounter(byte counter, boolean reset = false);

    boolean blink(unsigned long set = 500);

    byte counter(byte counter = 5, boolean increase = false, boolean reset = false);

    boolean ready(byte counter, boolean reset = false);
};

#endif