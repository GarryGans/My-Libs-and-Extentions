#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer
{
private:
    unsigned long sec = 1024;

public:
    Timer();
    ~Timer();

    boolean minusCounter(byte &counter);

    boolean wait(unsigned long set);

    boolean alternation(unsigned long set = 500);

    byte counter(byte counter = 5, boolean invert = false, boolean reset = false);

    boolean ready(byte counter = 5, boolean reset = false);
};

#endif