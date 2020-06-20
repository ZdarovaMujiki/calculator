typedef struct list
{
	double data;
	struct list *next;
} List;
typedef struct varlist
{
	char* name;
	double value;
	struct list *next;
	struct list *last;
} VarList;
typedef struct stack
{
	List *top;
} Stack;
void push(double a, Stack *S);
void makenull(Stack  *S);
int empty(Stack *S);
double pop(Stack *S);
double top(Stack *S);
Stack * create();
void *add(VarList *variables, char *str);