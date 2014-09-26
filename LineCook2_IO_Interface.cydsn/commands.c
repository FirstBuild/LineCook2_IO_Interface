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
        
        case CMD_SET_HEAT:
            setHeat(*((uint16 *) params));
            break;
        
        case CMD_SET_TIME:
            setTime(*((uint32 *) params));
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
}

// Assumes that screen is currently at the "Set Heat" view,
void setHeat(uint16 heat)
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
