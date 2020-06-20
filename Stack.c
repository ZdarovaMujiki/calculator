#include <stdio.h>
#include <string.h>
#include "Stack.h"

void push(double a, Stack *S)
{
	List *p;
	p = (List *)malloc(sizeof (List));
	p->data = a;
	p->next = S->top;
	S->top = p;
}

void makenull(Stack  *S)
{
	List *p;
	while (S->top)
	{
		p = S->top;
		S->top = p->next;
		free(p);
	}
}

int empty(Stack *S)
{
	return (S->top == NULL);
}

double pop(Stack *S)
{
	double a;
	List *p;
	p = S->top;
	a = p->data;
	S->top = p->next;
	free(p);
	return a;
}

double top(Stack *S)
{
	if (S->top)
		return (S->top->data);
	else
		return 0;
}

Stack * create()
{
	Stack * S;
	S = (Stack *)malloc(sizeof (Stack));
	S->top = NULL;
	return S;
}

void *add(VarList *variables, char *str)
{
	VarList *cur = variables, *add;
	if (cur->name == NULL)
	{
		cur->next = NULL;
		cur->name = str;
		printf("%s = ", str);
		if (scanf("%lf", &cur->value) != 1)
		{
			printf("Unexpected value");
			exit(0);
		}
		return;
	}
	while (cur->next)
	{
		if (!strcmp(cur->name, str)) return;
		cur = cur->next;
	}
	if (!strcmp(cur->name, str)) return;
	add = (VarList*)malloc(sizeof(VarList));
	add->next = NULL;
	add->name = str;
	printf("%s = ", str);
	if (scanf("%lf", &add->value) != 1)
	{
		printf("Unexpected value");
		exit(0);
	}
	cur->next = add;
}