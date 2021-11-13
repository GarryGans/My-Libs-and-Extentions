#include "Timer.h"

Timer timer[2];

Timer::Timer()
{
}

Timer::~Timer()
{
}

boolean Timer::minusCounter(byte &counter)
{
    if (timer[1].wait(sec))
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

byte Timer::counter(byte counter, boolean invert, boolean reset)
{
    static boolean first;
    static byte c;

    if (reset || !first)
    {
        c = counter;
        first = true;
    }

    if (timer[1].minusCounter(c))
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
    static byte c;

    if (reset || !first)
    {
        c = counter;
        first = true;
    }

    if (timer[0].minusCounter(counter))
    {
        counter = c;
        first = false;
        return true;
    }

    return false;
}

boolean Timer::wait(unsigned long set)
{
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

    if (timer[0].wait(set))
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
}
