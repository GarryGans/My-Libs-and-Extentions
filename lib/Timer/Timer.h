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

    boolean first= false;

    // boolean first_0 = false;
    // boolean first_1 = false;
    // boolean first_2 = false;
    // boolean first_3 = false;
    // boolean first_4 = false;

    boolean _blink = false;

    byte temp_0;
    byte temp_1;

public:
    Timer();
    ~Timer();

    boolean wait(unsigned long time, boolean reset);

    boolean wait(unsigned long time = 1000);

    byte minusCounter(byte counter);

    byte plusCounter(byte counter);

    byte reduceByCounter(byte time, byte barWidth, double prewBarWidth, double factor);

    byte reduceCounter(byte counter, boolean reset, int time = 1000);

    byte restoreCounter(byte counter, boolean reset, int time = 1000);

    byte counter(byte counter, boolean increase = false, boolean reset = false, int time = 1000);

    boolean blink(unsigned long time = 500);

    boolean ready(byte counter, boolean reset = false);
};

#endif