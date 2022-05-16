#ifndef pushswap_H
#define pushswap_H
#include <touch.h>
#include <ctrl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <kernel.h>

typedef struct s_stack
{
    int *elements;
    int taille;
} t_stack;

void	pusha(t_stack *stacka, t_stack *stackb);
void	pushb(t_stack *stacka, t_stack *stackb);
void	reversea(t_stack *stacka);
void	reverseb(t_stack *stackb);
void	reverses(t_stack *stacka, t_stack *stackb);
void	rotatea(t_stack *stacka);
void	rotateb(t_stack *stackb);
void	rotates(t_stack *stacka, t_stack *stackb);
void	swapa(t_stack *stacka);
void	swapb(t_stack *stackb);
void	swaps(t_stack *stacka, t_stack *stackb);
void    ps_showstacks(t_stack *stacka, t_stack *stackb);
void    ps_clearstacks(t_stack *stacka, t_stack *stackb);
int	    ps_issorted(t_stack *stack);
void    bubblesort(t_stack *stacka, t_stack *stackb);
void	ps_customsort(t_stack *stacka, t_stack *stackb);
void    pause();
#endif