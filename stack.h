#ifndef STACK_H
#define STACK_H

typedef char StackElem;
typedef double StackElem2;
typedef enum {
    OK,
    ERROR
} Status;

typedef enum {
    FALSE,
    TRUE
} Bool;

typedef enum {
    binary,
    hex,
    decimal
} MODE;

typedef struct {
    StackElem* pBase;
    StackElem* pTop;
    int size;
} Stack;

typedef struct {
    StackElem2* pBase;
    StackElem2* pTop;
    int size;
} Stack2;

Status init_stack(Stack* pStack);
void stack_free(Stack* pStack);
void stack_clear(Stack *pStack);
Bool is_empty(Stack* pStack);
int stack_length(Stack *pStack);
Status stack_get_top(Stack* pStack,StackElem* pElem);
Status stack_push(Stack *pStack,StackElem* pElem);
Status stack_pop(Stack* pStack,StackElem* pElem);
Status stack_traverse(Stack *pStack,Status (*visit)(StackElem*));
Status myinit(Stack2* pStack);
void myfree(Stack2* pStack);
void clear(Stack2 *pStack);
Bool empty(Stack2* pStack);
int length(Stack2 *pStack);
Status get_top(Stack2* pStack,StackElem2* pElem);
Status push(Stack2 *pStack,StackElem2* pElem);
Status pop(Stack2* pStack,StackElem2* pElem);
Status traverse(Stack2 *pStack,Status (*visit)(StackElem2*));
Status decimal_change(const char* expression, char* result);
int decimal_precedence(char op);
double decimal_calculate(char *result);
int mypow(int base, int exponent);
int binary_change(char* expression, char* result);
int binary_transform(double answer);
int hex_change(char* expression, char* result);
int binary_precedence(char c);
double binary_calculate(char *result);
int hex_precedence(char op);
double hex_calculate(char *result);

#endif
