#ifndef ACTIONS_HEADER
#define ACTIONS_HEADER
    
#include <main.h>

typedef enum 
{
    CMD_SET_CLOCK,
    CMD_SET_MODE,
    CMD_SET_HEAT,
    CMD_SET_TIME,
    CMD_PUSH_BUTTON
} command_t;

uint16 uint16AtParamsIndex(uint8 i, uint8 (*params)[4]);

void executeCommand(command_t command, uint8 (*params)[4]);

void setClock(uint32 seconds);
void setMode(uint8 mode);
void setHeat(uint16 heat);
void setTime(uint16 seconds);

#endif
