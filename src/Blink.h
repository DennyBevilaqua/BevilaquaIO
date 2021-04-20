class Blink
{
     private:
        unsigned short pin;
        unsigned short timeHigh;
        unsigned short timeLow;
        bool isHigh;
        unsigned long time;
    public:
        Blink(unsigned short pin, short timeHigh, short timeLow);
        Blink(unsigned short pin, short timeHigh);
        ~Blink();
        void seed();
        unsigned short getStatus();
};