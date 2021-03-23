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
        // fanSensPin needs to be D2, fanPWMPin needs to be D3
        Fan(char fanSensPin, char fanPWMPin, unsigned long fanSensTimeOut);
        
        void start();
        int getFanRPM();
        void setFanSpeed(double percentage);
    };

#endif // __FAN_H__