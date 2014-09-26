#ifndef ACTIONS_HEADER
#define ACTIONS_HEADER
    
#include <main.h>
   
typedef enum 
{
    SET_CLOCK,
    SET_MODE,
    SET_HEAT,
    SET_TIME,
    PUSH_BUTTON
} action_t;

action_t waitForInstruction(uint8 (*params)[10]);
uint16 uint16AtParamsIndex(uint8 i, uint8 (*params)[10]);

void executeAction(action_t action, uint8 (*params)[10]);

void setClock(uint32 seconds);
void setMode(uint8 mode);
void setHeat(uint16 heat);
void setTime(uint16 seconds);

#endif
