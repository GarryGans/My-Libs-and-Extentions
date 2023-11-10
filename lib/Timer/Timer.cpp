#include "Timer.h"

// Timer timer[2];

Timer::Timer()
{
}

Timer::~Timer()
{
}

boolean Timer::wait(unsigned long time, boolean reset)
{
    if (reset)
    {
        prew = millis();
        Serial.println("reset");
    }

    if (millis() - prew >= time)
    {
        prew = millis();

        return true;
    }

    return false;
}

boolean Timer::wait(unsigned long time)
{
    if (!first)
    {
        first = true;
        prew = millis();
    }

    if (millis() - prew >= time)
    {
        // prew = millis();
        first = false;

        return true;
    }

    return false;
}

byte Timer::minusCounter(byte counter)
{
    if (wait(defSec))
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
    if (wait(defSec))
    {
        counter++;
    }

    return counter;
}

byte Timer::reduceByCounter(byte time, byte barWidth, double prewBarWidth, double factor)
{
    // if (reset)
    // {
    //     prewBarWidth = barWidth = screenWidth;
    //     // tempAmount = time ;

    //     // factor = (double)screenWidth / (double)time;
    // }

    if (barWidth == byte(prewBarWidth - factor))
    {
        if (time > 0)
        {
            time--;

            prewBarWidth = (prewBarWidth - factor);
            // prewBarWidth = barWidth;

            if (prewBarWidth < factor)
            {
                factor = prewBarWidth;
            }
        }
    }

    return time;
}

byte Timer::reduceCounter(byte counter, boolean reset, int time)
{
    if (reset)
    {
        temp_0 = counter;
    }

    if (wait(time, reset) && temp_0 > 0)
    {
        temp_0--;
    }

    return temp_0;
}

byte Timer::restoreCounter(byte counter, boolean reset, int time)
{
    if (reset)
    {
        temp_1 = 0;
    }

    if (wait(time, reset) && temp_1 < counter)
    {
        temp_1++;
    }

    return temp_1;
}

byte Timer::counter(byte counter, boolean increase, boolean reset, int time)
{
    if (increase)
    {
        return restoreCounter(counter, reset, time);
    }
    else
    {
        return reduceCounter(counter, reset, time);
    }
}

boolean Timer::ready(byte counter, boolean reset)
{
    // return reduceCounter(counter, reset, defSec) == 0;

    return wait(counter * defSec, reset);
}

boolean Timer::blink(unsigned long time, boolean reset)
{
    if (wait(time, reset))
    {
        !_blink ? _blink = true : _blink = false;
    }

    if (reset)
        _blink = false;

    return _blink;
}