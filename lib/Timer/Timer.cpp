#include "Timer.h"

// Timer timer[2];

Timer::Timer()
{
}

Timer::~Timer()
{
}

boolean Timer::wait(unsigned long time)
{
    if (!first_0)
    {
        prew_0 = millis();
        first_0 = true;
    }

    if (millis() - prew_0 >= time)
    {
        first_0 = false;

        return true;
    }

    return false;
}

boolean Timer::wait(unsigned long time, boolean reset)
{
    if (reset)
    {
        prew = millis();

        // Serial.println("reset");
    }

    if (millis() - prew >= time)
    {
        prew = millis();
        return true;
    }

    return false;
}

boolean Timer::ready(byte counter, boolean reset)
{
    if (!first_1 || reset)
    {
        prew_1 = millis();
        first_1 = true;

        // Serial.println("ready");
    }

    if (millis() - prew_1 >= counter * defSec)
    {
        first_1 = false;
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
    if (reset || !first_2)
    {
        reset = first_2 = true;
        temp_0 = counter;

        Serial.print("start: ");
        Serial.println(temp_0);
    }

    if (wait(time, reset) && temp_0 > 0)
    {
        temp_0--;

        if (temp_0 == 0)
        {
            first_2 = false;
        }
        

        // Serial.print("begin: ");
        // Serial.println(temp_0);
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

// boolean Timer::ready(byte counter, boolean reset)
// {
//     return wait(counter * defSec, reset);
// }

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