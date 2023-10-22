#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

boolean Timer::wait(unsigned long set, boolean reset)
{
    // static boolean first;  ////// DON'T WORK STATIC

    if (!first || reset)
    {
        first = true;
        prew = millis();
    }

    if (millis() - prew >= set)
    {
        first = false;
        return true;
    }

    return false;
}

byte Timer::minusCounter(byte &counter)
{
    if (wait(second))
    {
        if (counter > 0)
        {
            counter--;
        }
    }

    return counter;
}

byte Timer::plusCounter(byte &counter)
{
    if (wait(second))
    {
        counter++;
    }

    return counter;
}

byte Timer::reduceCounter(byte counter, boolean reset, int sec)
{
    static byte tempCounter;

    // static boolean first;

    // if (!first || reset)
    // {
    //     first = true;
    //     tempCounter = counter;
    // }

    if ((tempCounter == 0 && wait(sec)) || reset)
    {
        tempCounter = counter;
    }

    if (wait(sec) && tempCounter > 0)
    {
        tempCounter--;
    }

    // if (tempCounter == 0 )
    // {
    //     first = false;
    //     tempCounter = counter;
    // }

    return tempCounter;
}

byte Timer::restoreCounter(byte counter, boolean reset, int sec)
{
    static byte tempCounter;

    if ((tempCounter == counter && wait(sec)) || reset)
    {
        tempCounter = 0;
    }

    if (wait(sec) && tempCounter < counter)
    {
        tempCounter++;
    }

    return tempCounter;
}

byte Timer::counter(byte counter, boolean increase, boolean reset, int sec)
{
    if (increase)
    {
        return restoreCounter(counter, reset, sec);
    }
    else
    {
        return reduceCounter(counter, reset, sec);
    }
}

boolean Timer::ready(byte counter, boolean reset)
{
    return wait(counter * second, reset);
}

boolean Timer::blink(unsigned long set)
{
    static boolean blink;

    if (wait(set))
    {
        !blink ? blink = true : blink = false;
    }

    return blink;
}
