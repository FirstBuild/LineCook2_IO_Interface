#include <main.h>
#include <actions.h>

int main()
{
    action_t action;
    uint8 params[10];
    
    // Set time to 8:30 PM
    setClock(73800);

    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        action = waitForInstruction(&params);
        executeAction(action, &params);
    }
}
