#ifndef __TECCONTROLLER_H__
#define __TECCONTROLLER_H__

class TECController
{
private:
    char mosFetPin;
public:
    // mosFetPin needs to be D9
    TECController(char mosFetPin);

    void start();
    void setPWM(float percentage);
};

#endif // __TECCONTROLLER_H__