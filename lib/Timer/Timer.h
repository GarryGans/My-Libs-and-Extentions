#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

#define defSec 1000

class Timer
{
private:
    unsigned long prew = 0;

    boolean first = false;

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

    boolean wait(unsigned long time = defSec);

    byte minusCounter(byte counter);

    byte plusCounter(byte counter);

    byte reduceByCounter(byte time, byte barWidth, double prewBarWidth, double factor);

    byte reduceCounter(byte counter, boolean reset, int time);

    byte restoreCounter(byte counter, boolean reset, int time = defSec);

    byte counter(byte counter, boolean increase = false, boolean reset = false, int time = defSec);

    boolean ready(byte counter, boolean reset = false);

    boolean blink(unsigned long time = 500, boolean reset = false);
};

#endif