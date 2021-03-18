#include <Arduino.h>
#include "Buttons.h"

Buttons::Buttons(char negButtonPin, char posButtonPin, int debounceTime, int holdThreashold)
{
    // time in milliseconds that the button needs to be in a new state to change virtual state
    this->debounceTime = debounceTime;

    setupButtons(negButtonPin, posButtonPin);
}

Buttons::Buttons(char negButtonPin, char posButtonPin)
{
    debounceTime = 50;

    setupButtons(negButtonPin, posButtonPin);
}

void Buttons::setupButtons(char negButtonPin, char posButtonPin)
{
    buttonPin[negButton] = negButtonPin;
    buttonPin[posButton] = posButtonPin;

    pinMode(buttonPin[negButton], INPUT_PULLUP);
    pinMode(buttonPin[posButton], INPUT_PULLUP);
}

unsigned char Buttons::getStatus(unsigned long currentMillis)
{
    readButton(negButton, currentMillis);
    readButton(posButton, currentMillis);

    // check to see if any button is pressed
    if (!buttonState[negButton] || !buttonState[posButton])
    {
        if (!buttonState[negButton] && !buttonState[posButton])
        {   
            // both buttons pressed
            return 3;
        }else if (!buttonState[posButton])
        {
            // positive button pressed
            return 2;
        }
        else if (!buttonState[negButton])
        {
            // negative button pressed
            return 1;
        }
    }
    // no button pressed
    return 0;
}

void Buttons::readButton(byte buttonIndex, unsigned long currentMillis)
{
    buttonState[buttonIndex] = bool(digitalRead(buttonPin[buttonIndex]));

    // check if the button status is different to last time
    if (buttonState[buttonIndex] != lastButtonState[buttonIndex])
    {
        // reset debounce timer
        lastButtonState[buttonIndex] = currentMillis;

    } // check that debounceTime has passed since last change
    else if (((currentMillis - lastButtonState[buttonIndex]) > debounceTime))
    {
        // check that the state has changed
        if (buttonState[buttonIndex] != lastButtonState[buttonIndex])
        {
            // update button state
            lastButtonState[buttonIndex] = buttonState[buttonIndex];
        }
    }
}
