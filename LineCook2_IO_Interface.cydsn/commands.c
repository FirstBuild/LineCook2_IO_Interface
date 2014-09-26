#include <commands.h>
#include <buttons.h>
#include <i2c_constants.h>

uint8 executeCommand(command_t command, uint8 (*params)[2])
{
    switch (command)
    {
        case CMD_SET_CLOCK:
            setClock((*params)[0], (*params)[1]);
            break;
        
        case CMD_SET_MODE:
            setMode((mode_t) (*params)[0]);
            break;
            
        case CMD_SET_COOKING_TIME:
            setCookingTime(*((uint16 *) params));
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
    
    return STS_CMD_DONE;
}

// Hours are in 24hour time, where 0 == 12am
void setClock(uint8 hours, uint8 minutes)
{
    uint8 i,
          pm = 0;
 
    if (hours >= 24 || minutes >= 60) return;
    
    if (hours == 0)
    {
        hours = 12;
    } 
    else if (hours == 12)
    {
        pm = 1;
    } 
    else if (hours >= 13)
    {
        hours -= 12;
        pm = 1;
    }

    pushButton(BTN_CLOCK_AMPM);
    encoderIncrement();
    
    // Initial time is 1:00
    for (i = 1; i < hours; i++)
    {
        encoderIncrement();
    }
    
    pushButton(BTN_ENTER);
    
    for (i = 0; i < minutes; i++)
    {
        encoderIncrement();
    }
    
    pushButton(BTN_ENTER);
    encoderIncrement();
    
    if (pm == 1)
    {
        encoderIncrement();
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
    
    // Move encoder by one step, which initializes values for heat/time
    encoderIncrement();
}

// Assumes that screen is currently at the "Set Heat" stage
void setConvectionHeat(uint16 heat)
{
    int i, diff, direction;
    
    if (heat == 350) {
        return;
    } else if (heat > 350) {
        direction = 1;
        diff = heat - 350;
    } else {
        direction = 0;
        diff = 350 - heat;
    }
   
    for (i = 0; i < diff; i++) {
		if (direction == 1) {
			encoderIncrement();
		} else {
			encoderDecrement();
		}
    }
    
    pushButton(BTN_ENTER);
}

// Assumes that screen is currently at the "Set Time" stage.
// Minimum time is 15 seconds, and can only step in 15 second intervals.
// Times will be rounded to the nearest 15 seconds.
void setCookingTime(uint16 seconds)
{
    int i, steps;
    steps = (seconds / 15) - 1;
    if (seconds % 15 > 7) steps += 1;
 
    for (i = 0; i < steps; i++)
    {
        encoderIncrement();
    }
    
    pushButton(BTN_ENTER);
}

// Power level starts at 10, minimum of 1
void setMicrowavePower(uint8 power)
{
    uint8 i;
    if (power > 10) return;
    
    pushButton(BTN_POWER);
    
    for (i = 10; i > power; i--)
    {
        encoderDecrement();
    }
    pushButton(BTN_ENTER);
}
