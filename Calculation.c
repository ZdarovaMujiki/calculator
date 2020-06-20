#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"
#include "Calculation.h"

double Exp(double a, int b)
{
	double _n = 1;
	for (int j = 1; j <= b; j++)
	{
		_n *= a;
	}
	return _n;
}

double Calculate(char *str, VarList *variables)
{
	Stack *digits = create();
	char *variable;
	int i, j, rank;
	double n, a, b;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			n = str[i] - '0';
			while (str[i + 1] >= '0' && str[i + 1] <= '9')
			{
				n *= 10;
				n += str[i + 1] - '0';
				i++;
			}
			if (str[i + 1] == '.')
			{
				i++;
				rank = 1;
				for (i; str[i + 1] >= '0' && str[i + 1] <= '9'; rank++, i++)
				{
					n += (Exp(0.1, rank) * (str[i + 1] - '0'));
				}
				if (str[i + 1] == '.')
				{
					printf("Unexpected second dot");
					exit(0);
				}
			}
			push(n, digits);
		}
		else
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			variable = (int*)malloc(sizeof(int)* 21);
			for (j = 0; str[i] >= 'a' && str[i] <= 'z'; i++, j++)
			{
				variable[j] = str[i];
			}
			variable[j] = '\0';
			VarList *cur = variables;
			while (strcmp(cur->name, variable))
			{
				cur = cur->next;
			}
			push(cur->value, digits);
		}
		switch (str[i])
		{
			case '+':
			{
						b = pop(digits);
						a = pop(digits);
						push(a + b, digits);
						break;
			}
			case '-':
			{
						b = pop(digits);
						a = pop(digits);
						push(a - b, digits);
						break;
			}
			case '*':
			{
						b = pop(digits);
						a = pop(digits);
						push(a * b, digits);
						break;
			}
			case '/':
			{
						b = pop(digits);
						a = pop(digits);
						if (b == 0)
						{
							printf("Division by zero");
							exit(0);
						}
						push(a / b, digits);
						break;
			}
			case '_':
			{
						a = pop(digits);
						push(-a, digits);
						break;
			}
		}
	}
	return digits->top->data;
}

char *Convert(char *term, int leng)
{
	Stack *stack = create();
	char *post;
	int i, j = 0;
	post = (char*)malloc(sizeof(char)* leng);
	for (i = 0; term[i] != '\0'; i++)
	{
		if (term[i] >= 'a' && term[i] <= 'z' || term[i] >= '0' && term[i] <= '9')
		{
			for (i; term[i] >= '0' && term[i] <= '9' || term[i] >= 'a' && term[i] <= 'z' || term[i] == '.'; i++, j++)
			{
				post[j] = term[i];
			}
			post[j] = ' ';
			i--;
			j++;
		}
		else
		{
			switch (term[i])
			{
			case '(':
			{
						push(term[i], stack);
						break;
			}
			case ')':
			{
						while (stack->top->data != '(')
						{
							post[j] = pop(stack);
							j++;
							post[j] = ' ';
							j++;
						}
						pop(stack);
						break;
			}
			case '+':
			{
						if (stack->top)
						{
							while (stack->top->data != '(' && !empty(stack))
							{
								post[j] = pop(stack);
								j++;
								post[j] = ' ';
								j++;
								if (!stack->top)
								{
									break;
								}
							}
						}
						push(term[i], stack);
						break;
			}
			case '-':
			{
						if (stack->top)
						{
							while (stack->top->data != '(' && !empty(stack))
							{
								post[j] = pop(stack);
								j++;
								post[j] = ' ';
								j++;
								if (!stack->top)
								{
									break;
								}
							}
						}
						push(term[i], stack);
						break;
			}
			case '/':
			{
						if (stack->top)
						{
							while (stack->top->data == '*' || stack->top->data == '/' || stack->top->data == '_')
							{
								post[j] = pop(stack);
								j++;
								post[j] = ' ';
								if (!stack->top)
								{
									break;
								}
							}
						}
						push(term[i], stack);
						break;
			}
			case '*':
			{
						if (stack->top)
						{
							while (stack->top->data == '*' || stack->top->data == '/' || stack->top->data == '_')
							{
								post[j] = pop(stack);
								j++;
								post[j] = ' ';
								if (!stack->top)
								{
									break;
								}
							}
						}
						push(term[i], stack);
						break;
			}
			case '_':
			{
						push(term[i], stack);
						break;
			}
			case ' ':
			{
						break;
			}
			default:
			{
					   printf("Unexpected symbol (%c)", term[i]);
					   exit(0);
			}
			}
		}
	}
	while (!empty(stack))
	{
		post[j] = pop(stack);
		j++;
		post[j] = ' ';
		j++;
	}
	post[j - 1] = '\0';
	printf("");
	return post;
}

int Processing(char *str, int amount, VarList *variables)
{
	int i, j, brackets = 0;

	char *variable;
	if (amount > 2)
	{
		printf("Unexpected space");
		return 1;
	}
	if (strlen(str) > 500)
	{
		printf("Expression is too long (>=500 symbols)");
		return 1;
	}

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			if ((str[i - 1] >= '0' && str[i - 1] <= '9') || (str[i + 1] >= '0' && str[i + 1] <= '9'))
			{
				printf("Digit attached to a variable");
				return 1;
			}
			variable = (char*)malloc(sizeof(char) * 21);
			for (j = 0; str[i] >= 'a' && str[i] <= 'z'; i++, j++)
			{
				variable[j] = str[i];
				if (j == 20)
				{
					printf("Variable is too long (>=20 letters)");
					return 1;
				}
			}
			i--;
			variable[j] = '\0';
			add(variables, variable);
		}
		else
		if (str[i] == '(')
		{
			brackets++;
		}
		else
		if (str[i] == ')')
		{
			brackets--;
		}
		else
		if (!(str[i] >= '0' && str[i] <= '9') && !(str[i] == '.' || str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*'))
		{
			printf("Unexpected symbol (%c) at position (%d)", str[i], i);
			return 1;
		}
	}

	if (brackets < 0)
	{
		printf("Unexpected close bracket(s)");
		return 1;
	}
	if (brackets > 0)
	{
		printf("Unexpected open bracket(s)");
		return 1;
	}
	return 0;
}