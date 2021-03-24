#include <Arduino.h>
#include "Buttons.h"
#include "OLED.h" // debug

Buttons::Buttons(int debounceTime)
{
    // time in milliseconds that the button needs to be in a new state to change virtual state
    this->debounceTime = debounceTime;
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
    if (buttonState[negButton] || buttonState[posButton])
    {
        if (buttonState[negButton] && buttonState[posButton])
        {   
            // both buttons pressed
            return both;
        }else if (buttonState[posButton])
        {
            // positive button pressed
            return positive;
        }
        else if (buttonState[negButton])
        {
            // negative button pressed
            return negative;
        }
    }
    // no button pressed
    return none;
}

void Buttons::readButton(byte buttonIndex, unsigned long currentMillis)
{
    // since buttons use pull up resistors it is inverted
    bool currentButtonState = !digitalRead(buttonPin[buttonIndex]);

    // check if the button status is different to last time
    if (currentButtonState != lastButtonState[buttonIndex])
    {
        // reset debounce timer
        lastDebounceTime[buttonIndex] = currentMillis;
        lastButtonState[buttonIndex] = currentButtonState;

    } // check that debounceTime has passed since last change
    else if ((currentMillis - lastDebounceTime[buttonIndex]) > debounceTime)
    {
        // check that the state has changed
        if (buttonState[buttonIndex] != lastButtonState[buttonIndex])
        {
            // update button state
            buttonState[buttonIndex] = lastButtonState[buttonIndex];
        }
    }
}
