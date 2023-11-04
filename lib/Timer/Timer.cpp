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
        prew = millis();

        return true;
    }

    return false;
}

boolean Timer::wait(unsigned long set)
{
    if (!first)
    {
        prew = millis();
        first = true;

        Serial.print("!first: ");
        Serial.println(first);
    }

    if (millis() - prew >= set)
    {
        // first = false;
        prew = millis();

        Serial.print("millis() - prew: ");
        Serial.println(first);

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
    if (!firstCount)
    {
        firstCount = true;
        tempCounter = counter;
    }

    if (reset)
    {
        firstCount = false;
        tempCounter = counter;
    }

    if (firstCount)
    {
        if (wait(sec) && tempCounter > 0)
        {
            tempCounter--;
        }
    }

    if (tempCounter == 0)
    {
        firstCount = false;
    }

    return tempCounter;
}

byte Timer::restoreCounter(byte counter, boolean reset, int sec)
{
    if (tempCounter == counter && wait(sec))
    {
        tempCounter_2 = 0;
    }

    if (wait(sec) && tempCounter_2 < counter)
    {
        tempCounter_2++;
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
    return wait(counter * second, reset);
}

boolean Timer::blink(unsigned long set)
{
    if (wait(set))
    {
        !a ? a = true : a = false;
    }

    return a;
}
