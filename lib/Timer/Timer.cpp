#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

boolean Timer::wait(unsigned long set, boolean reset)
{
    if (!first_2 || reset)
    {
        prew = millis();
        first_2 = true;
    }

    if (millis() - prew >= set)
    {
        first_2 = false;

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
    if (!first_0 || reset)
    {
        first_0 = true;
        temp_0 = counter;
    }

    if (wait(sec, reset) && temp_0 > 0)
    {
        temp_0--;

        if (temp_0 == 0)
        {
            first_0 = false;
        }
    }

    return temp_0;
}

byte Timer::restoreCounter(byte counter, boolean reset, int sec)
{
    if (!first_1 || reset)
    {
        first_1 = true;
        temp_1 = 0;
    }

    if (wait(sec, reset) && temp_1 < counter)
    {
        temp_1++;

        if (temp_1 == counter)
        {
            first_1 = false;
        }
    }

    return temp_1;
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
        !a ? a = true : a = false;
    }

    return a;
}
