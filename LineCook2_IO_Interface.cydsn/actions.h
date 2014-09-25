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

action_t waitForInstruction(char (*params)[10]);
unsigned short shortAtParamsIndex(int i, char (*params)[10]);

void executeAction(action_t action, char (*params)[10]);

void setClock(unsigned short seconds);
void setMode(char mode);
void setHeat(unsigned short heat);
void setTime(unsigned short seconds);

#endif
