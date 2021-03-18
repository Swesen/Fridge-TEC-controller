#ifndef __FAN_H__
#define __FAN_H__

    class Fan
    {
    private:
        char fanSensPin;
        char fanPWMPin;
        unsigned long fanSensTimeOut;
        
        void setupTimer2();
    public:
        Fan(char fanSensPin, char fanPWMPin, unsigned long fanSensTimeOut);

        int getFanRPM();
        void setFanSpeed(unsigned char percent);
    };

#endif // __FAN_H__