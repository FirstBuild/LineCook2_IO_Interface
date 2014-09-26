#include <commands.h>
#include <buttons.h>

void executeCommand(command_t command, uint8 (*params)[4])
{
    switch (command)
    {
       
        case CMD_SET_CLOCK:
            setClock(*((uint16 *) params));
            break;
        
        case CMD_SET_MODE:
            setMode((mode_t) (*params)[0]);
            break;
            
        case CMD_SET_TIME:
            setTime(*((uint32 *) params));
            break;
            
        case CMD_SET_CONVECTION_HEAT:
            setConvectionHeat(*((uint16 *) params));
            break;
        
        case CMD_SET_MICROWAVE_POWER:
            setMicrowavePower((*params)[0]);
            break;
        
        case CMD_PUSH_BUTTON:
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

void setMode(mode_t mode)
{
    switch (mode)
    {
        case MODE_CONVECTION_BAKE:
            pushButton(BTN_CONVECTION_BAKE);
            break;
        case MODE_MICROWAVE:
            pushButton(BTN_TIME_COOK);
            break;
    }
    
    // Always move encoder by one step to set initial values for heat/time
    pushButton(BTN_INCREMENT);
}

// Assumes that screen is currently at the "Set Heat" view,
void setConvectionHeat(uint16 heat)
{
    int i;
    int diff;
    button_t encoderBtn;
    
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
    
    pushButton(BTN_ENTER);
}

// Minimum time is 15 seconds.
// <= 22 will be rounded down to 15,
// > 22 will be rounded up to 30.
void setTime(uint16 seconds)
{
    int steps, i;
    steps = (seconds / 15) - 1;
    if (seconds % 15 > 7) steps += 1;
 
    for (i = 0; i < steps; i++) 
    {
        pushButton(BTN_INCREMENT);
    }
    
    pushButton(BTN_ENTER);
}

void setMicrowavePower(uint8 power)
{
    uint8 i;
    if (power > 10) return;
    
    pushButton(BTN_POWER);
    
    for (i = 10; i > power; i--)
    {
        pushButton(BTN_DECREMENT);
    }
    pushButton(BTN_ENTER);
}
