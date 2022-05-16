#include "push_swap.h"
#include <framework/debugScreen.h>

void pause()
{
    sceKernelDelayThread(0.5*1000000);
    return ;
}

int	ps_issorted(t_stack *stack)
{
	int i;
	int smallest;

	i = 1;
	smallest = stack->elements[0];
	while(i < stack->taille)
	{
		if (smallest > stack->elements[i])
			return 0;
		smallest = stack->elements[i];
		i++;
	}
	return 1;
}

t_stack *ps_createstack(int elements[], int taille)
{
    t_stack *stack;
    int i;

    i = 1;
    stack = (t_stack*)malloc(sizeof(t_stack));
    stack->taille = taille;
    stack->elements = (int*)malloc(sizeof(int) * taille);
    while (i <= taille)
    {
        stack->elements[i - 1] = elements[i - 1];
        i++;
    }
    return (stack);
}

void ps_clearstacks(t_stack *stacka, t_stack *stackb)
{
    int i;
    int positions[6] = { 80, 130, 190, 250, 310, 370 };
    SceChar8 print[255];

    i = 0;
    psvDebugScreenPrintf("Stack A", 420, 630, SCE_COLOR_RED, SCE_DBGFONT_FONTSIZE_LARGE);
    while (i < stacka->taille)
    {
        sprintf(print, "%d", stacka->elements[i]);
        psvDebugScreenTextClear(print, positions[i], 680, SCE_DBGFONT_FONTSIZE_LARGE);
        i++;
    }
    i = 0;
    psvDebugScreenPrintf("Stack B", 420, 780, SCE_COLOR_GREEN, SCE_DBGFONT_FONTSIZE_LARGE);
    while (i < stackb->taille)
    {
        sprintf(print, "%d", stackb->elements[i]);
        psvDebugScreenTextClear(print, positions[i], 830, SCE_DBGFONT_FONTSIZE_LARGE);
        i++;
    }
}

void ps_showstacks(t_stack *stacka, t_stack *stackb)
{
    int i;
    int sorted;
    int positions[6] = { 80, 130, 190, 250, 310, 370 };
    SceChar8 print[255];

    i = 0;
    psvDebugScreenPrintf("Stack A", 420, 630, SCE_COLOR_RED, SCE_DBGFONT_FONTSIZE_LARGE);
    while (i < stacka->taille)
    {
        sprintf(print, "%d", stacka->elements[i]);
        psvDebugScreenPrintf(print, positions[i], 680, SCE_COLOR_RED, SCE_DBGFONT_FONTSIZE_LARGE);
        i++;
    }
    i = 0;
    psvDebugScreenPrintf("Stack B", 420, 780, SCE_COLOR_GREEN, SCE_DBGFONT_FONTSIZE_LARGE);
    while (i < stackb->taille)
    {
        sprintf(print, "%d", stackb->elements[i]);
        psvDebugScreenPrintf(print, positions[i], 830, SCE_COLOR_GREEN, SCE_DBGFONT_FONTSIZE_LARGE);
        i++;
    }
    sorted = ps_issorted(stacka);
    if (sorted && stacka->taille > 0 && stackb->taille == 0)
        psvDebugScreenPrintf("Sorted", 460, 640, SCE_COLOR_RED, SCE_DBGFONT_FONTSIZE_LARGE);
    else
        psvDebugScreenTextClear("Sorted", 460, 640, SCE_DBGFONT_FONTSIZE_LARGE);
}

void showBasicStuff()
{
    int i;

    i = 80;

    // Print Stack A commands
    psvDebugScreenPrintf("PA",  60,  90, SCE_COLOR_RED, SCE_DBGFONT_FONTSIZE_LARGE);
    psvDebugScreenPrintf("SA",  180, 90, SCE_COLOR_RED, SCE_DBGFONT_FONTSIZE_LARGE);
    psvDebugScreenPrintf("RA",  300, 90, SCE_COLOR_RED, SCE_DBGFONT_FONTSIZE_LARGE);
    psvDebugScreenPrintf("RRA", 420, 80, SCE_COLOR_RED, SCE_DBGFONT_FONTSIZE_LARGE);

    // Print Stack B commands
    psvDebugScreenPrintf("PB",  60,  240,  SCE_COLOR_GREEN, SCE_DBGFONT_FONTSIZE_LARGE);
    psvDebugScreenPrintf("SB",  180, 240,  SCE_COLOR_GREEN, SCE_DBGFONT_FONTSIZE_LARGE);
    psvDebugScreenPrintf("RB",  300, 240,  SCE_COLOR_GREEN, SCE_DBGFONT_FONTSIZE_LARGE);
    psvDebugScreenPrintf("RRB", 420, 230,  SCE_COLOR_GREEN, SCE_DBGFONT_FONTSIZE_LARGE);

    // Print Stack A and B commands
    psvDebugScreenPrintf("SS",  180, 390,  SCE_COLOR_YELLOW, SCE_DBGFONT_FONTSIZE_LARGE);
    psvDebugScreenPrintf("RR",  300, 390,  SCE_COLOR_YELLOW, SCE_DBGFONT_FONTSIZE_LARGE);
    psvDebugScreenPrintf("RRR", 420, 380,  SCE_COLOR_YELLOW, SCE_DBGFONT_FONTSIZE_LARGE);

    // Print custom sorting commands
    psvDebugScreenPrintf("X : Reset Stacks | O : Bubble Sort | [] : Custom Sort", 520, 60,  SCE_COLOR_PURPLE, SCE_DBGFONT_FONTSIZE_LARGE);

    // Print Stack Separators
    while (i <= 420)
    {
        psvDebugScreenPrintf("|", i, 755, SCE_COLOR_PURPLE, SCE_DBGFONT_FONTSIZE_LARGE);
        i = i + 20;
    }
    i = 80;
    while (i <= 420)
    {
        psvDebugScreenPrintf("|", i, 600, SCE_COLOR_PURPLE, SCE_DBGFONT_FONTSIZE_LARGE);
        i = i + 20;
    }
    i = 80;
    while (i <= 420)
    {
        psvDebugScreenPrintf("|", i, 900, SCE_COLOR_PURPLE, SCE_DBGFONT_FONTSIZE_LARGE);
        i = i + 20;
    }

    return ;
}

void ps_resetstack(t_stack *stacka, t_stack *stackb, int elements[], int taille)
{
    ps_clearstacks(stacka, stackb);
    free(stacka->elements);
    free(stackb->elements);
    free(stacka);
    free(stackb);
    stacka = ps_createstack(elements, taille);
    stackb = ps_createstack(NULL, 0);
    ps_showstacks(stacka, stackb);
    pause();
    return ;
}

int main()
{
    FILE *in_file = fopen("ux0://data/push_swap/numbers.txt", "r"); // read only
    if (!in_file)
        return 0;
    t_stack *stacka;
    t_stack *stackb;
    int     elements[255];
    int     i;
    int     reading;
    SceTouchData touch[SCE_TOUCH_PORT_MAX_NUM];
    SceTouchData touch_old[SCE_TOUCH_PORT_MAX_NUM];
    SceCtrlData ctrl;

    i = 0;
    while (fscanf(in_file, "%d", &reading) == 1)
    {
        elements[i] = reading;
        i++;
    }
    stacka = ps_createstack(elements, i);
    stackb = ps_createstack(NULL, 0);
    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, 1);
    sceTouchEnableTouchForce(SCE_TOUCH_PORT_FRONT);
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_DIGITALONLY);

    psvDebugScreenInit();
    showBasicStuff();
    ps_showstacks(stacka, stackb);
    while(1)
    {
        sceCtrlPeekBufferPositive(0, &ctrl, 1);
        memcpy(touch_old, touch, sizeof(touch_old));
        int port;
        if (ctrl.buttons == SCE_CTRL_CROSS)
            ps_resetstack(stacka, stackb, elements, i);
        if (ctrl.buttons == SCE_CTRL_SELECT)
            return 0;
        if (ctrl.buttons == SCE_CTRL_CIRCLE)
            bubblesort(stacka, stackb);
        if (ctrl.buttons == SCE_CTRL_SQUARE)
            ps_customsort(stacka, stackb);
        for (port = 0; port < SCE_TOUCH_PORT_MAX_NUM; port++)
        {
            sceTouchPeek(port, &touch[port], 1);
            if (touch[0].reportNum == 1)
            {
                // Stack A commands
                if (touch[0].report[0].x < 340)
                {
                    if (touch[0].report[0].y < 240)
                    {
                        ps_clearstacks(stacka, stackb);
                        pusha(stacka, stackb);
                        ps_showstacks(stacka, stackb);
                        pause();
                        break;
                    }
                    if (touch[0].report[0].y > 240 && touch[0].report[0].y < 480)
                    {
                        ps_clearstacks(stacka, stackb);
                        swapa(stacka);
                        ps_showstacks(stacka, stackb);
                        pause();
                        break;
                    }
                    if (touch[0].report[0].y > 480 && touch[0].report[0].y < 720)
                    {
                        ps_clearstacks(stacka, stackb);
                        rotatea(stacka);
                        ps_showstacks(stacka, stackb);
                        pause();
                        break;
                    }
                    if (touch[0].report[0].y > 720 && touch[0].report[0].y < 960)
                    {
                        ps_clearstacks(stacka, stackb);
                        reversea(stacka);
                        ps_showstacks(stacka, stackb);
                        pause();
                        break;
                    }
                }
                // Stack B commands
                if (touch[0].report[0].x > 340 && touch[0].report[0].x < 640)
                {
                    if (touch[0].report[0].y < 240)
                    {
                        ps_clearstacks(stacka, stackb);
                        pushb(stacka, stackb);
                        ps_showstacks(stacka, stackb);
                        pause();
                        break;
                    }
                    if (touch[0].report[0].y > 240 && touch[0].report[0].y < 480)
                    {
                        ps_clearstacks(stacka, stackb);
                        swapb(stackb);
                        ps_showstacks(stacka, stackb);
                        pause();
                        break;
                    }
                    if (touch[0].report[0].y > 480 && touch[0].report[0].y < 720)
                    {
                        ps_clearstacks(stacka, stackb);
                        rotateb(stackb);
                        ps_showstacks(stacka, stackb);
                        pause();
                        break;
                    }
                    if (touch[0].report[0].y > 720 && touch[0].report[0].y < 960)
                    {
                        ps_clearstacks(stacka, stackb);
                        reverseb(stackb);
                        ps_showstacks(stacka, stackb);
                        pause();
                        break;
                    }
                }
                // Stack A and B commands
                if (touch[0].report[0].x > 640 && touch[0].report[0].x < 940)
                {
                    if (touch[0].report[0].y > 240 && touch[0].report[0].y < 480)
                    {
                        ps_clearstacks(stacka, stackb);
                        swaps(stacka, stackb);
                        ps_showstacks(stacka, stackb);
                        pause();
                        break;
                    }
                    if (touch[0].report[0].y > 480 && touch[0].report[0].y < 720)
                    {
                        ps_clearstacks(stacka, stackb);
                        rotates(stacka, stackb);
                        ps_showstacks(stacka, stackb);
                        pause();
                        break;
                    }
                    if (touch[0].report[0].y > 720 && touch[0].report[0].y < 960)
                    {
                        ps_clearstacks(stacka, stackb);
                        reverses(stacka, stackb);
                        ps_showstacks(stacka, stackb);
                        pause();
                        break;
                    }
                }
            }
        }
    }
}