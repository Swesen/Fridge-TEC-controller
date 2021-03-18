#include <Arduino.h>
#include "Buttons.h"

Buttons::Buttons(char negButtonPin, char posButtonPin, int debounceTime)
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

byte Buttons::getStatus(unsigned long currentMillis)
{   
    // reset timer if counter has reset
    for (byte i = 0; i < 2; i++)
    {
        if (currentMillis < lastDebounceTime[i])
        {
                lastDebounceTime[i] = currentMillis;
        }
        
    }
    
    readButton(negButton, currentMillis);
    readButton(posButton, currentMillis);

    // check to see if any button is pressed
    if (!lastButtonState[negButton] || !lastButtonState[posButton])
    {
        if (!lastButtonState[negButton] && !lastButtonState[posButton])
        {   
            // both buttons pressed
            return 3;
        }else if (!lastButtonState[posButton])
        {
            // positive button pressed
            return 2;
        }
        else if (!lastButtonState[negButton])
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
