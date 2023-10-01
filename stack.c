#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <assert.h>
#include <string.h>

/**
*对栈进行初始化
*-init函数对栈做初始化操作，也就是为栈的成员变量赋初值。参
*数pStack是指向栈的指针。如果初始化成功，返回OK；如果失败，返
*回ERROR。在为栈的成员变量pBase和pTop赋初值之前，需要为栈元素分配
*内存空间。
*/
Status init_stack(Stack* pStack){
    pStack->pBase = (StackElem*)malloc(sizeof(StackElem)*4);
    if(!pStack->pBase){
        printf("内存分配错误\n");
        return ERROR;
    }
    pStack->size = 4;
    pStack->pTop = pStack->pBase;
    return OK;
}

/**
*释放栈元素的内存
*-free函数释放栈元素的内存。参数pStack是指向栈的指针
*/
void stack_free(Stack* pStack){
    assert(pStack);

    free(pStack->pBase);
    pStack->pTop = NULL;
    pStack->size = 0;
}
/**
*清空栈
*-clear函数把pStack指向的栈中的数据元素清空。要清空栈内的数据元
素，其实并不需要真的把那些数据删除，只要把栈顶指针移到栈底即可。
*/
void stack_clear(Stack *pStack){
    assert(pStack);

    pStack->pTop = pStack->pBase;
}

/**
*判断栈是否为空
*/
Bool is_empty(Stack* pStack){
    assert(pStack);
    
    return pStack->pTop == pStack->pBase ? TRUE: FALSE;
}
   
/**
*求栈的长度
*/
int stack_length(Stack *pStack){
    assert(pStack);

    int length = pStack->pTop - pStack->pBase;
    return length;
}

/**
*取栈顶元素
*-get_top函数读取栈顶元素。参数pStack是栈指针，pElem是数据元素指
*针，读取的栈顶元素存入*pElem 中。如果成功，返回OK；如果失败，返
*回ERROR。这个函数不改变栈顶指针的值。
*/
Status stack_get_top(Stack* pStack,StackElem* pElem){
    assert(pStack);
    if (pStack->pBase == pStack->pTop){
        return ERROR;
    }
    
    *pElem = *(pStack->pTop - 1);
    if (pElem != NULL){
        return OK;
    }else{
        return ERROR;
    }
    
}

/**
*入栈
*-push函数把pElem指向的数据元素压入pStack指向的栈。如果成功，返
*回OK；如果失败，返回ERROR。
*/
Status stack_push(Stack *pStack,StackElem* pElem){
    assert(pStack);

    if (pStack->pTop - pStack->pBase == pStack->size){
    StackElem* newstack = (StackElem*)realloc(pStack->pBase, 2*pStack->size*sizeof(StackElem));
    if (newstack == NULL){
        return ERROR;
    }
    pStack->pTop = pStack->pBase + pStack->size;
    pStack->size = 2*pStack->size;
    pStack->pBase = newstack;
    }
    *pStack->pTop = *pElem;
    pStack->pTop++;
    return OK;
}

/**
*出栈
*-pop函数弹出栈顶元素，pStack是栈指针，弹出的元素存入pElem指向的
*内存中。如果成功，返回OK；如果失败，返回ERROR。
*/
Status stack_pop(Stack* pStack,StackElem* pElem){
    assert(pStack);

    if (is_empty(pStack)) {
        return ERROR;
    }
    *pElem = *(pStack->pTop - 1);
    pStack->pTop--;
    if(pElem == NULL){
        return ERROR;
    }
    return OK;
}

/**
*遍历栈
*-traverse函数遍历由pStack所指向的栈，对栈中的每个数据元素执
*行visit操作。如果成功，返回OK；如果失败，返回ERROR。其中visit是
*函数指针，它的参数是数据元素的指针，返回值是Status类型的。
*/
Status stack_traverse(Stack *pStack,Status (*visit)(StackElem*)){
    assert(pStack);

    for (StackElem* i = pStack->pBase ;i < pStack->pTop ; i++){
    Status result = visit(i);
    if (result != ERROR){
    return ERROR;
    }
}
    return OK;
}


//中缀表达式变后缀表达式
Status change_expression(const char* expression, char* result){
    int i = 0;
    int j = 0;
    char c;
    Stack stack;
    init_stack(&stack);
    //printf("%s\n", expression);
    for (i = 0; expression[i] != '\0'; i++){
        char c = expression[i];
        if((c >= '0' && c<= '9')){
            for(;expression[i] >= '0' && expression[i] <= '9'; i++ ){
                result[j++] = expression[i];
            }
            result[j++] = ' ';
            i--;
        } else if(c == '('){
            stack_push(&stack, &c);
        } else if (c == ')') {
            while (*(stack.pTop-1) != '(') {
                char element;
                stack_pop(&stack,&element);
                result[j++] = element;
                result[j++] = ' ';
                }
                char k;
                stack_pop(&stack,&k);
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!is_empty(&stack) &&  precedence(c) <= precedence(*stack.pTop)) {
                char element;
                stack_pop(&stack, &element);
                result[j++] = element;
            }
            stack_push(&stack, &c);
        } else if (c == ' '){
            continue;

        } else if (expression[i] == '.'){
            result[--j] = '.';
            result[j++] = '.';
        } else {
            printf("表达式错误\n");
            exit(-1);
        }
        
    }
     while (!is_empty(&stack)) {
        stack_pop(&stack, &c);
        result[j++] = c;
        result[j++] = ' ';
     }
    result[j] = '\0';
    stack_clear(&stack);
    stack_free(&stack);
    return OK;
}
    


//计算运算符的权重
int precedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return 0;
}



//计算后缀表达式
double calculate(char *result) {
    int i = 0;
    Stack2 stack;
    myinit(&stack);
    double C;
    char* c = strtok(result ," ");
    for(; c != NULL ; c = strtok(NULL, " ")){
        if(c[0] >= '0' && c[0] <= '9'){
             double C = atof(c);
            push(&stack , &C);
            //printf("%s\n", c);
        } else if(*c == '+' || *c == '-' || *c == '*' || *c == '/'){
            double b;
            pop(&stack, &b);
            double a;
            pop(&stack, &a);
            double answer;
            switch (*c) {
                case '+':
                    answer = a + b;
                    break;
                case '-':
                    answer = a - b;
                    break;
                case '*':
                    answer = a * b;
                    break;
                case '/':
                    if(b == 0.0){
                        printf("错误\n");
                        return 0;
                    }
                    answer = a / b;
                    break;
                default:
                printf("错误\n");
                return 0;
            }
            push(&stack, &answer);
        } 
        
    }

    StackElem2 finalResult;
    pop(&stack, &finalResult);
    clear(&stack);
    return finalResult;
}