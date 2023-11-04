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
    unsigned long prew = 0;

    boolean first = false;
    boolean a = false;
    boolean firstCount = false;

    byte tempCounter = 0;
    byte tempCounter_2 = 0;

public:
    Timer();
    ~Timer();

    boolean wait(unsigned long set, boolean reset);
    boolean wait(unsigned long set);

    byte minusCounter(byte counter);

    byte plusCounter(byte counter);

    byte reduceCounter(byte counter, boolean reset, int sec = 1000);

    byte restoreCounter(byte counter, boolean reset = false, int sec = 1000);

    byte counter(byte counter, boolean increase = false, boolean reset = false, int sec = 1000);

    boolean blink(unsigned long set = 500);

    boolean ready(byte counter, boolean reset = false);
};

#endif