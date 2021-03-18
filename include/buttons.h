#ifndef __BUTTONS_H__
#define __BUTTONS_H__

class Buttons
{
private:
    unsigned int debounceTime;

    enum button {negButton, posButton};

    // index 0 = negative, 1 = positive
    char buttonPin[2];
    bool buttonState[2];
    bool lastButtonState[2];
    unsigned long lastDebounceTime[2];

    void setupButtons(char negButtonPin, char posButtonPin);
    void readButton(byte buttonIndex, unsigned long currentMillis);
public:
    Buttons(char negButtonPin, char posButtonPin, int debounceTime);
    Buttons(char negButtonPin, char posButtonPin);

    unsigned char getStatus(unsigned long currentMillis);
};

#endif // __BUTTONS_H__