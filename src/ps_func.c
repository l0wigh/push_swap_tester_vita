#include "push_swap.h"

void	push(t_stack *stack, int element)
{
	int taille;

	taille = stack->taille;
	stack->taille = taille + 1;
	if (taille == 0)
	{
		stack->elements[0] = element;
		return ;
	}
	while (taille >= 0)
	{
		stack->elements[taille + 1] = stack->elements[taille];
		taille--;
	}
	stack->elements[0] = element;
	return ;
}

void	pusha(t_stack *stacka, t_stack *stackb)
{
	if (stackb->taille > 0)
	{
		push(stacka, stackb->elements[0]);
		stackb->taille = stackb->taille - 1;
		if (stackb->taille > 0)
		{
			memmove(stackb->elements, stackb->elements + 1, stackb->taille * sizeof(int));
		}
	}
}

void	pushb(t_stack *stacka, t_stack *stackb)
{
	if (stacka->taille > 0)
	{
		push(stackb, stacka->elements[0]);
        stackb->elements[0] = stackb->elements[0];
		stacka->taille = stacka->taille - 1;
		if (stacka->taille > 0)
		{
			memmove(stacka->elements, stacka->elements + 1, stacka->taille * sizeof(int));
		}
	}
}

void	reversea(t_stack *stacka)
{
	int		i;
	int		tmp;
	int		taille;

	taille = stacka->taille;
	i = 0;
	tmp = stacka->elements[taille - 1];
	while (i < taille - 1)
	{
		stacka->elements[taille - 1 - i] = stacka->elements[taille - 2 - i];
		i++;
	}
	stacka->elements[0] = tmp;
	return ;
}

void	reverseb(t_stack *stackb)
{
	int		i;
	int		tmp;
	int		taille;

	taille = stackb->taille;
	i = 0;
	tmp = stackb->elements[taille - 1];
	while (i < taille - 1)
	{
		stackb->elements[taille - 1 - i] = stackb->elements[taille - 2 - i];
		i++;
	}
	stackb->elements[0] = tmp;
	return ;
}

void	reverses(t_stack *stacka, t_stack *stackb)
{
	reversea(stacka);
	reverseb(stackb);
	return ;
}

void	rotatea(t_stack *stacka)
{
	int		i;
	int		tmp;
	int		taille;

	taille = stacka->taille;
	i = 0;
	tmp = stacka->elements[0];
	while (i < taille - 1)
	{
		stacka->elements[i] = stacka->elements[i + 1];
		i++;
	}
	stacka->elements[taille - 1] = tmp;
	return ;
}

void	rotateb(t_stack *stackb)
{
	int		i;
	int		tmp;
	int		taille;

	taille = stackb->taille;
	i = 0;
	tmp = stackb->elements[0];
	while (i < taille - 1)
	{
		stackb->elements[i] = stackb->elements[i + 1];
		i++;
	}
	stackb->elements[taille - 1] = tmp;
	return ;
}

void	rotates(t_stack *stacka, t_stack *stackb)
{
	rotatea(stacka);
	rotateb(stackb);
	return ;
}

void	swapa(t_stack *stacka)
{
	int tmp;

	if (stacka->taille > 1)
	{
		tmp = stacka->elements[0];
		stacka->elements[0] = stacka->elements[1];
		stacka->elements[1] = tmp;
	}
	return ;
}

void	swapb(t_stack *stackb)
{
	int tmp;

	if (stackb->taille > 1)
	{
		tmp = stackb->elements[0];
		stackb->elements[0] = stackb->elements[1];
		stackb->elements[1] = tmp;
	}
	return ;
}

void	swaps(t_stack *stacka, t_stack *stackb)
{
	swapa(stacka);
	swapb(stackb);
	return ;
}

void bubblesort(t_stack *stacka, t_stack *stackb)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < stacka->taille - 1)
    {
        while (j < stacka->taille - i - 1)
        {
            if (stacka->elements[0] > stacka->elements[1])
            {
                if (ps_issorted(stacka))
                    return;
                ps_clearstacks(stacka, stackb);
                swapa(stacka);
                ps_showstacks(stacka, stackb);
                sceKernelDelayThread(0.2*1000000);
            }
            if (ps_issorted(stacka))
                return;
            ps_clearstacks(stacka, stackb);
            rotatea(stacka);
            ps_showstacks(stacka, stackb);
            sceKernelDelayThread(0.2 * 1000000);
            j++;
        }
        i++;
    }
    ps_clearstacks(stacka, stackb);
    rotatea(stacka);
    ps_showstacks(stacka, stackb);
    sceKernelDelayThread(0.2 * 1000000);
    if (ps_issorted(stacka))
        return ;
    bubblesort(stacka, stackb);
}

int    ps_checksmaller(t_stack *stacka)
{
    int smaller;
    int pos_smaller;
    int i;

    pos_smaller = 0;
    i = 0;
    smaller = stacka->elements[i];
    while (i < stacka->taille)
    {
        if (smaller > stacka->elements[i])
        {
            smaller = stacka->elements[i];
            pos_smaller = i;
        }
        i++;
    }
    return pos_smaller;
}

void	ps_customsort(t_stack *stacka, t_stack *stackb)
{
    int i;
    int smaller;

    i = 0;
    smaller = ps_checksmaller(stacka);
    while (i < smaller)
    {
        ps_clearstacks(stacka, stackb);
        rotatea(stacka);
        ps_showstacks(stacka, stackb);
        sceKernelDelayThread(0.2*1000000);
        i++;
    }
    ps_clearstacks(stacka, stackb);
    pushb(stacka, stackb);
    ps_showstacks(stacka, stackb);
    sceKernelDelayThread(0.2 * 1000000);
    if (stacka->taille == 0)
    {
        i = 0;
        while (i < stackb->taille)
        {
            ps_clearstacks(stacka, stackb);
            pusha(stacka, stackb);
            ps_showstacks(stacka, stackb);
            sceKernelDelayThread(0.2 * 1000000);
        }
    }
    else
        ps_customsort(stacka, stackb);
}