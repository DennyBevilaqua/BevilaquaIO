#include <Arduino.h>

class Blink
{
private:
    unsigned short pin;
    unsigned short timeHigh;
    unsigned short timeLow;
    bool isHigh;
    unsigned long time;

public:
    Blink(unsigned short pin, short timeHigh, short timeLow)
    {
        this->pin = pin;
        this->timeHigh = timeHigh;
        this->timeLow = timeLow;
    }

    Blink(unsigned short pin, short timeHigh)
    {
        this->pin = pin;
        this->timeHigh = timeHigh;
        this->timeLow = timeHigh;
    }

    ~Blink()
    {
    }

    void seed()
    {
        unsigned long cTime = millis();
        if (this->isHigh)
        {
            if (cTime >= this->time)
            {
                digitalWrite(pin, LOW);
                this->isHigh = false;
                this->time += this->timeLow;
            }
        }
        else
        {
            if (cTime >= this->time)
            {
                digitalWrite(pin, HIGH);
                this->time += this->timeHigh;
                this->isHigh = true;
            }
        }
    }

    unsigned short getStatus()
    {
        if (this->isHigh)
            return HIGH;
        else
            return LOW;
    }
};