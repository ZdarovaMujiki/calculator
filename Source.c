#include <stdio.h>
#include "Stack.h"
#include "Calculation.h"

int main(unsigned int argc, char** argv)
{
	char *post;
	VarList *variables = (VarList*)malloc(sizeof(VarList));
	variables->name = NULL;
	variables->next = NULL;
	int i, lenght, symbols = 0, unar = 1, unarCount = 0;
	if (Processing(argv[1], argc, variables))
	{
		return 0;
	}
	for (i = 0; argv[1][i] != '\0'; i++)
	{
		if ((argv[1][i] >= '0' && argv[1][i] <= '9') || (argv[1][i] >= 'a' && argv[1][i] <= 'z')) unar = 0;
		else
		if (argv[1][i] == '(') unar = 1;
		else
		if (argv[1][i] == '-' && unar)
		{
			argv[1][i] = '_';
			unarCount++;
		}
		else
		if (argv[1][i] == '+' || argv[1][i] == '-' || argv[1][i] == '/' || argv[1][i] == '*')
		{
			symbols++;
		}
	}
	lenght = i + symbols * 2 + unarCount * 5;
	post = Convert(argv[1], lenght);
	printf("%g", Calculate(post, variables));
	return 0;
}