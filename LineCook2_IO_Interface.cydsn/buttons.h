#ifndef BUTTONS_HEADER
#define BUTTONS_HEADER
    
#include <main.h>
    
typedef enum 
{
    BTN_POPCORN,
    BTN_BEVERAGE,
    BTN_REHEAT,
    BTN_EXPRESS,
    BTN_COMBINATION,
    BTN_CONVECTION_BAKE,
    BTN_TIME_COOK,
    BTN_POWER,
    BTN_DEFROST,
    BTN_ENTER,
    BTN_START,
    BTN_CLEAR,
    BTN_MENU_COOK,
    BTN_OPTIONS,
    BTN_CLOCK_AMPM,
    BTN_TIMER,
    BTN_INCREMENT,
    BTN_DECREMENT
} button_t;

void pushButton(button_t button);
void setButtonState(button_t button, uint8 value);

#endif
