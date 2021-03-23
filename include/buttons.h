#ifndef __BUTTONS_H__
#define __BUTTONS_H__

enum buttonPressed {none, negative, positive, both};

// this class handles reading the buttons and
// removes any noise and debounces the button presses
class Buttons
{
private:
    unsigned int debounceTime;

    enum button {negButton, posButton};

    // index 0 = negative, 1 = positive
    char buttonPin[2] = {0};
    bool buttonState[2] = {0};
    bool lastButtonState[2] = {0};
    unsigned long lastDebounceTime[2] = {0};

    void setupButtons(char negButtonPin, char posButtonPin);
    void readButton(byte buttonIndex, unsigned long currentMillis);
public:
    Buttons(char negButtonPin, char posButtonPin, int debounceTime);
    Buttons(char negButtonPin, char posButtonPin);

    byte getStatus(unsigned long currentMillis);
};

#endif // __BUTTONS_H__