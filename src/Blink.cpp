#include "Blink.h"
#include <Arduino.h>

Blink::Blink(unsigned short pin, short timeHigh, short timeLow)
{
    this->pin = pin;
    this->timeHigh = timeHigh;
    this->timeLow = timeLow;
}

Blink::Blink(unsigned short pin, short timeHigh)
{
    this->pin = pin;
    this->timeHigh = timeHigh;
    this->timeLow = timeHigh;
}

Blink::~Blink()
{

}

unsigned short Blink::getStatus()
{
    if(this->isHigh)
        return HIGH;
    else
        return LOW;
}

void Blink::seed()
{
    unsigned long cTime = millis();
    if(this->isHigh)
    {
        if(cTime >= this->time)
        {
            digitalWrite(pin, LOW);
            this->isHigh = false;
            this->time += this->timeLow;
        }
    }
    else
    {
        if(cTime >= this->time)
        {
            digitalWrite(pin, HIGH);
            this->time += this->timeHigh;
            this->isHigh = true;
        }
    }
}