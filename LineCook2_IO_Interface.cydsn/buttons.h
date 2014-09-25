#ifndef BUTTONS_HEADER
#define BUTTONS_HEADER
    
#include <main.h>
    
typedef enum 
{
    BTN_START,
    BTN_STOP,
    BTN_CLEAR,
    BTN_TIME,
    BTN_CLOCK,
    BTN_ENCODER_UP,
    BTN_ENCODER_DOWN,
    BTN_COOK_COMBO,
    BTN_COOK_CONVECTION,
    BTN_COOK_MICROWAVE
} button_t;

void pushButton(button_t button);

#endif
