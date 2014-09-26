#include <main.h>
#include <actions.h>
#include <buttons.h>

// params is an array with a length of 10 bytes. 
action_t waitForInstruction(uint8 (*params)[10])
{
    // Listen for SPI message, 
    // fill params array with bytes
    // return action;
}

// Parses a short at a given params index.
// ex:
//    [0, 128] => 128
//    [1, 0]   => 256
uint16 uint16AtParamsIndex(uint8 i, uint8 (*params)[10])
{
    uint16 value;
    value = ((uint16) (*params)[i]) << 8;
    value = value | ((uint16) (*params)[i + 1]);
    return value;
}

void executeAction(action_t action, uint8 (*params)[10])
{
    uint16 twoByteValue;
    switch (action)
    {
        case SET_CLOCK:
            twoByteValue = uint16AtParamsIndex(0, params);
            setClock(twoByteValue);
            break;
        
        case SET_MODE:
            setMode((*params)[0]);
            break;
        
        case SET_HEAT:
            twoByteValue = uint16AtParamsIndex(0, params);
            setHeat(twoByteValue);
            break;
        
        case SET_TIME:
            twoByteValue = uint16AtParamsIndex(0, params);
            setTime(twoByteValue);
            break;
        
        case PUSH_BUTTON:
            // Button index should be first parameter
            pushButton((button_t) (*params)[0]);
            break;
        
    }   
}

void setClock(uint32 secondsAfterMidnight)
{
    uint8 hours;
    uint8 minutes;
    uint8 pm = 0;
    uint8 i;
 
    if (secondsAfterMidnight > (60 * 60 * 24 - 1)) return;    
    
    hours = secondsAfterMidnight / (60 * 60);
    if (hours >= 13)
    {
        hours -= 12;
        pm = 1;
    }
    minutes = secondsAfterMidnight % (60 * 60);
      
    pushButton(BTN_CLOCK_AMPM);
    pushButton(BTN_INCREMENT);
    
    for (i = 0; i < hours; i++)
    {
        pushButton(BTN_INCREMENT);
    }
    
    pushButton(BTN_ENTER);
    pushButton(BTN_INCREMENT);
    
    for (i = 0; i < minutes; i++)
    {
        pushButton(BTN_INCREMENT);
    }
    
    pushButton(BTN_ENTER);
    pushButton(BTN_INCREMENT);
    
    if (pm == 1)
    {
        pushButton(BTN_INCREMENT);
    }
    
    pushButton(BTN_ENTER);
    pushButton(BTN_ENTER);
}

void setMode(uint8 mode)
{
    switch (mode)
    {
        case 0:
            pushButton(BTN_CONVECTION_BAKE);
            break;
        case 1:
            pushButton(BTN_TIME_COOK);
            break;
    }
}

// Assumes that screen is currently at the "Set Heat" view,
void setHeat(unsigned short heat)
{
    int i;
    int diff;
    button_t encoderBtn;
    
    // Move encoder by one step to set initial heat to 350 (default)
    pushButton(BTN_INCREMENT);
    
    if (heat == 350) {
        return;
    } else if (heat > 350) {
        encoderBtn = BTN_INCREMENT;
        diff = heat - 350;
    } else {
        encoderBtn = BTN_DECREMENT;
        diff = 350 - heat;
    }
   
    for (i = 0; i < diff; i++) {
        pushButton(encoderBtn);
    }
}

void setTime(uint16 seconds)
{
    
}
