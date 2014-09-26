#include <buttons.h>

void pushButton(button_t button)
{
    setButtonState(button, 1);
    CyDelay(BUTTON_ON_MS);
    setButtonState(button, 0);
    CyDelay(BUTTON_OFF_MS);
}

void encoderDecrement()
{
	encoderButton(BTN_INCREMENT, BTN_DECREMENT);
}

void encoderIncrement()
{
	encoderButton(BTN_DECREMENT, BTN_INCREMENT);
}

void encoderButton(button_t firstSwitch, button_t secondSwitch)
{
	setButtonState(firstSwitch, 1);
    CyDelay(ENCODER_ON_MS / 2);
    setButtonState(secondSwitch, 1);
	CyDelay(ENCODER_ON_MS / 2);
	setButtonState(firstSwitch, 0);
	CyDelay(ENCODER_ON_MS / 2);
	setButtonState(secondSwitch, 0);
    CyDelay(ENCODER_ON_MS);
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
