#ifndef ACTIONS_HEADER
#define ACTIONS_HEADER

#include <main.h>

typedef enum
{
    CMD_SET_CLOCK,
    CMD_SET_MODE,
    CMD_SET_COOKING_TIME,
    CMD_SET_CONVECTION_HEAT,
    CMD_SET_MICROWAVE_POWER,
    CMD_PUSH_BUTTON
} command_t;

typedef enum
{
    MODE_CONVECTION_BAKE,
    MODE_MICROWAVE
} mode_t;

void executeCommand(command_t command, uint8 (*params)[2]);

void setClock(uint8 hours, uint8 minutes);
void setMode(mode_t mode);
void setConvectionHeat(uint16 heat);
void setCookingTime(uint16 seconds);
void setMicrowavePower(uint8 power);

#endif
