#include <buttons.h>

void pushButton(button_t button)
{
    setButtonState(button, 1);
    CyDelay(20);
    setButtonState(button, 0);
    CyDelay(20);
}

void setButtonState(button_t button, uint8 value)
{
    switch(button) {
        case BTN_POPCORN:
            Popcorn_Write(value);
            break;         
        case BTN_BEVERAGE:
            Beverage_Write(value);
            break;
        case BTN_REHEAT:
            Reheat_Write(value);
            break;
        case BTN_EXPRESS:
            Express_Write(value);
            break;
        case BTN_COMBINATION:
            Combination_Write(value);
            break;
        case BTN_CONVECTION_BAKE:
            ConvBake_Write(value);
            break;
        case BTN_TIME_COOK:
            TimeCook_Write(value);
            break;
        case BTN_POWER:
            Power_Write(value);
            break;
        case BTN_DEFROST:
            Defrost_Write(value);
            break;
        case BTN_ENTER:
            Enter_Write(value);
            break;
        case BTN_START:
            StartPause_Write(value);
            break;
        case BTN_CLEAR:
            Clear_Write(value);
            break;
        case BTN_MENU_COOK:
            MenuCook_Write(value);
            break;
        case BTN_OPTIONS:
            Options_Write(value);
            break;
        case BTN_CLOCK_AMPM:
            ClockAmPm_Write(value);
            break;
        case BTN_TIMER:
            Timer_Write(value);
            break;
        case BTN_INCREMENT:
            Increment_Write(value);
            break;
        case BTN_DECREMENT:
            Decrement_Write(value);
            break;
    }
}
