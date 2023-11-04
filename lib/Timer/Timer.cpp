#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

boolean Timer::wait(unsigned long set, boolean reset)
{
    if (!first || reset)
    {
        prew = millis();
        first = true;
    }

    if (millis() - prew >= set)
    {
        first = false;

        return true;
    }

    return false;
}

byte Timer::minusCounter(byte counter)
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

byte Timer::plusCounter(byte counter)
{
    if (wait(second))
    {
        counter++;
    }

    return counter;
}

byte Timer::reduceCounter(byte counter, boolean reset, int sec)
{
    if (!firstCount || reset)
    {
        firstCount = true;
        tempCounter = counter;
    }

    if (wait(sec, reset) && tempCounter > 0)
    {
        tempCounter--;

        if (tempCounter == 0)
        {
            firstCount = false;
        }
    }

    return tempCounter;
}

byte Timer::restoreCounter(byte counter, boolean reset, int sec)
{
    if (!firstCount_2 || reset)
    {
        firstCount_2 = true;
        tempCounter_2 = 0;
    }

    if (wait(sec, reset) && tempCounter_2 < counter)
    {
        tempCounter_2++;

        if (tempCounter_2 == counter)
        {
            firstCount_2 = false;
        }
    }

    return tempCounter_2;
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
    return reduceCounter(counter, reset) == 0;
}

boolean Timer::blink(unsigned long set)
{
    if (wait(set))
    {
        return !a ? a = true : a = false;
    }
}
