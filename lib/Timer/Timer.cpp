#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

boolean Timer::minusCounter(byte &counter)
{
    if (wait(sec))
    {
        if (counter > 0)
        {
            counter--;
        }
    }

    if (counter == 0)
    {
        return true;
    }

    return false;
}

byte Timer::plusCounter(byte &counter)
{
    if (wait(sec))
    {
        counter++;
    }

    return counter;
}

byte Timer::counter(byte counter, boolean invert, boolean reset)
{
    static boolean first;
    static byte c;

    if (reset || !first)
    {
        c = counter;
        first = true;
    }

    if (minusCounter(c))
    {
        c = counter;
        first = false;
    }

    if (invert)
    {
        return counter - c;
    }

    else
    {
        return c;
    }
}

boolean Timer::ready(byte &counter, boolean reset)
{
    static boolean first;
    static byte firstCount;

    if (!first)
    {
        firstCount = counter;
        first = true;
    }

    if (reset)
    {
        counter = firstCount;
    }

    if (minusCounter(counter))
    {
        counter = firstCount;
        first = false;
        return true;
    }

    return false;
}

boolean Timer::wait(unsigned long set)
{
    // static boolean first;

    if (!first)
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

boolean Timer::alternation(unsigned long set)
{
    static boolean blink;

    if (wait(set))
    {
        if (!blink)
        {
            blink = true;
        }
        else
        {
            blink = false;
        }
    }

    return blink;

    // if (t[0].wait(set))
    // {
    //     return true;
    // }

    // return false;
}
