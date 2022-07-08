#include "push_swap.h"

int	get_smallest(int *liste, int taille)
{
	int	smallest;
	int	i;

	smallest = liste[0];
	i = 1;
	while (i < taille)
	{
		if (liste[i] < smallest)
			smallest = liste[i];
		i++;
	}
	return (smallest);
}

int	get_biggest(int *liste, int taille)
{
	int	biggest;
	int	i;

	biggest = liste[0];
	i = 1;
	while (i < taille)
	{
		if (liste[i] > biggest)
			biggest = liste[i];
		i++;
	}
	return (biggest);
}

int	ps_issorted_int(int *stack, int taille)
{
	int	e;
	int	smallest;

	e = 0;
	smallest = stack[0];
	while (++e < taille)
	{
		if (smallest > stack[e])
			return (0);
		smallest = stack[e];
	}
	return (1);
}

int	ps_issorted_better(t_stack *stack)
{
	int	e;
	int	smallest;

	e = 0;
	smallest = stack->elements[0];
	while (++e < stack->taille)
	{
		if (smallest > stack->elements[e])
			return (0);
		smallest = stack->elements[e];
	}
	return (1);
}

int	*bubblesort_tmp(int *numbers, int arrsize)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	j = 0;
	while (i < arrsize - 1)
	{
		while (j < arrsize - i - 1)
		{
			if (numbers[j] > numbers[j + 1])
			{
				temp = numbers[j];
				numbers[j] = numbers[j + 1];
				numbers[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	if (!ps_issorted_int(numbers, arrsize))
		bubblesort_tmp(numbers, arrsize);
	return (numbers);
}

int	push_to_b(t_stack *stacka, t_stack *stackb, int sorted, int x, int *actions)
{
	int	i;
	int	taille;

	i = 0;
	taille = stacka->taille;
	taille -= x;
	while (i < taille)
	{
		if (stacka->elements[0] >= sorted)
		{
			x++;
			ps_clearstacks(stacka, stackb);
			ps_clearcounter(actions);
			pushb(stacka, stackb);
			actions++;
			ps_showstacks(stacka, stackb);
			ps_showcounter(actions);
			sceKernelDelayThread(0.2 * 1000000);
		}
		else
		{
			ps_clearstacks(stacka, stackb);
			ps_clearcounter(actions);
			rotatea(stacka);
			actions++;
			ps_showstacks(stacka, stackb);
			ps_showcounter(actions);
			sceKernelDelayThread(0.2 * 1000000);
		}
		i++;
	}
	return (x);
}

void	sortb(t_stack *stacka, t_stack *stackb, int *actions)
{
	int	taille;
	int	elem;

	while (stackb->taille > 0)
	{
		taille = stackb->taille;
		elem = stackb->elements[0];
		if (elem == get_smallest(stackb->elements, taille))
		{
			ps_clearstacks(stacka, stackb);
			ps_clearcounter(actions);
			pusha(stacka, stackb);
			actions++;
			ps_showstacks(stacka, stackb);
			ps_showcounter(actions);
			sceKernelDelayThread(0.2 * 1000000);

			ps_clearstacks(stacka, stackb);
			ps_clearcounter(actions);
			rotatea(stacka);
			actions++;
			ps_showstacks(stacka, stackb);
			ps_showcounter(actions);
			sceKernelDelayThread(0.2 * 1000000);
		}
		else if (elem == get_biggest(stackb->elements, taille))
		{
			ps_clearstacks(stacka, stackb);
			ps_clearcounter(actions);
			pusha(stacka, stackb);
			actions++;
			ps_showstacks(stacka, stackb);
			ps_showcounter(actions);
			sceKernelDelayThread(0.2 * 1000000);
		}
		else
		{
			ps_clearstacks(stacka, stackb);
			ps_clearcounter(actions);
			rotateb(stackb);
			actions++;
			ps_showstacks(stacka, stackb);
			ps_showcounter(actions);
			sceKernelDelayThread(0.2 * 1000000);
		}
	}
	return ;
}

void	last_push_to_b(t_stack *stacka, t_stack *stackb, int j, int *actions)
{
	int	x;

	x = 0;
	while (x < j)
	{
		ps_clearstacks(stacka, stackb);
		ps_clearcounter(actions);
		pushb(stacka, stackb);
		actions++;
		ps_showstacks(stacka, stackb);
		ps_showcounter(actions);
		sceKernelDelayThread(0.2 * 1000000);
		x++;
	}
	return ;
}

void	infinity(t_stack *stacka, t_stack *stackb, int *sorted, int mode, int *actions)
{
	int	t;

	t = stacka->taille - 1;
	while (1)
	{
		if (stacka->elements[t] == sorted[t])
			break ;
		if (mode == 0)
		{
            ps_clearstacks(stacka, stackb);
			ps_clearcounter(actions);
			rotatea(stacka);
			actions++;
			ps_showstacks(stacka, stackb);
			ps_showcounter(actions);
            sceKernelDelayThread(0.2 * 1000000);
		}
		else
		{
            ps_clearstacks(stacka, stackb);
			ps_clearcounter(actions);
			reversea(stacka);
			actions++;
			ps_showstacks(stacka, stackb);
			ps_showcounter(actions);
            sceKernelDelayThread(0.2 * 1000000);
		}
	}
	return ;
}

void	better_sort(t_stack *stacka, t_stack *stackb, int *actions)
{
	int	i;
	int	coef;
	int	*sorted;
	int	j;

	i = 0;
	coef = 2;
	sorted = bubblesort_tmp(stacka->tmp, stacka->taille);
	if (stacka->taille >= 100)
		coef += stacka->taille / 100 + 1;
	j = stacka->taille / coef;
	while (coef-- > 1)
	{
		i = push_to_b(stacka, stackb, sorted[j * coef], i, actions);
		sortb(stacka, stackb, actions);
		if (coef > 1)
			infinity(stacka, stackb, sorted, 0, actions);
	}
	infinity(stacka, stackb, sorted, 1, actions);
	last_push_to_b(stacka, stackb, j, actions);
	sortb(stacka, stackb, actions);
	while (!ps_issorted_better(stacka))
	{
            ps_clearstacks(stacka, stackb);
			ps_clearcounter(actions);
            reversea(stacka);
			actions++;
            ps_showstacks(stacka, stackb);
			ps_showcounter(actions);
            sceKernelDelayThread(0.2 * 1000000);

	}
	return ;
}