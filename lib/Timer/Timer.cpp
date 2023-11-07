#include "Timer.h"

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
        // reset = false;
        prew = millis();
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
    if (!first_2)
    {
        first_2 = true;
        prew = millis();
    }

    if (millis() - prew >= time)
    {
        // prew = millis();
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

byte Timer::reduceByCounter(byte time, byte barWidth, double prewBarWidth, double factor)
{
    if (barWidth == byte(prewBarWidth - factor))
    {
        if (time > 0)
        {
            time--;

            prewBarWidth = (prewBarWidth - factor);

            if (prewBarWidth < factor)
            {
                factor = prewBarWidth;
            }

            // Serial.print("time: ");
            // Serial.println(time);
        }
    }

    return time;
}

byte Timer::reduceCounter(byte counter, boolean reset, int time)
{
    if (reset)
    {
        // reset = false;
        temp_0 = counter;

        
    }

    if (wait(time, reset) && temp_0 > 0)
    {
        temp_0--;

        // Serial.print("time: ");
        // Serial.println(temp_0);
    }

    // reset = false;

    return temp_0;

    // if (!first_0 || reset)
    // {
    //     first_0 = true;
    //     temp_0 = counter;
    // }

    // if (wait(time, reset) && temp_0 > 0)
    // {
    //     temp_0--;

    //     if (temp_0 == 0)
    //     {
    //         first_0 = false;
    //     }
    // }

    // return temp_0;
}

byte Timer::restoreCounter(byte counter, boolean reset, int time)
{
    if (reset)
    {
        // reset = false;
        temp_1 = 0;
    }

    if (wait(time, reset) && temp_1 < counter)
    {
        temp_1++;
        reset = false;
    }

    return temp_1;

    // if (!first_1 || reset)
    // {
    //     first_1 = true;
    //     temp_1 = 0;
    // }

    // if (wait(time, reset) && temp_1 < counter)
    // {
    //     temp_1++;

    //     if (temp_1 == counter)
    //     {
    //         first_1 = false;
    //     }
    // }

    // return temp_1;
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
    return reduceCounter(counter, reset) == 0;
}

boolean Timer::blink(unsigned long time)
{
    if (wait(time))
    {
        !_blink ? _blink = true : _blink = false;
    }

    return _blink;
}
