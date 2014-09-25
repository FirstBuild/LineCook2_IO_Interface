#include <project.h>
#include <main.h>
#include <actions.h>

int main()
{
    action_t action;
    char params[10];

    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        action = waitForInstruction(&params);
        executeAction(action, &params);
    }
}
