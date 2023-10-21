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
        // Serial.println("first");
    }

    if (millis() - prew >= set)
    {
        // Serial.print(millis() - prew);
        // Serial.println("   millis() - prew");

        // Serial.print("set: ");
        // Serial.println(set);

        first = false;
        return true;
    }

    // Serial.println("reset");

    return false;
}

boolean Timer::minusReady(byte &counter)
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

    if (minusReady(c))
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

boolean Timer::ready(byte counter, boolean reset)
{
    return wait(counter * sec, reset);
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
