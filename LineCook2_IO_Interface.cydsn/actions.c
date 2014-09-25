#include <main.h>
#include <actions.h>
#include <buttons.h>

// params is an array with a length of 10 bytes. 
action_t waitForInstruction(char (*params)[10])
{
    // Listen to UART
    // Fill in params array with bytes
    // return action;
}

// Parses a short at a given params index.
// ex:
//    [0, 128] => 128
//    [1, 0]   => 256
unsigned short shortAtParamsIndex(int i, char (*params)[10])
{
    unsigned short value;
    value = ((unsigned short) (*params)[i]) << 8;
    value = value | ((unsigned short) (*params)[i + 1]);
    return value;
}

void executeAction(action_t action, char (*params)[10])
{
    unsigned short shortValue;
    
    switch (action)
    {
        case SET_CLOCK:
            shortValue = shortAtParamsIndex(0, params);
            setClock(shortValue);
            break;
        
        case SET_MODE:
            setMode((*params)[0]);
            break;
        
        case SET_HEAT:
            shortValue = shortAtParamsIndex(0, params);
            setHeat(shortValue);
            break;
        
        case SET_TIME:
            shortValue = shortAtParamsIndex(0, params);
            setTime(shortValue);
            break;
        
        case PUSH_BUTTON:
            // Button index should be first parameter
            pushButton((button_t) (*params)[0]);
            break;
        
    }   
}


void setClock(unsigned short seconds)
{
    // Set hour
    // Set minute
    // Set AM / PM
}

void setMode(char mode)
{
    switch (mode)
    {
        case 0:
            pushButton(BTN_COOK_CONVECTION);
            break;
        case 1:
            pushButton(BTN_COOK_MICROWAVE);
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
    pushButton(BTN_ENCODER_UP);
    
    if (heat == 350) {
        return;
    } else if (heat > 350) {
        encoderBtn = BTN_ENCODER_UP;
        diff = heat - 350;
    } else {
        encoderBtn = BTN_ENCODER_DOWN;
        diff = 350 - heat;
    }
   
    for (i = 0; i < diff; i++) {
        pushButton(encoderBtn);
    }
}

void setTime(unsigned short seconds)
{
    
}
