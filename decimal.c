#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "stack.h"
#include <assert.h>
#include <unistd.h>
//#include "stack.c"
//#include "stack2.c"

//中缀表达式变后缀表达式
Status decimal_change(const char* expression, char* result){
    int i = 0;
    int j = 0;
    char c;
    Stack stack;
    init_stack(&stack);
    //printf("%s\n", expression);
    for (; expression[i] != '\0' || expression[i] == ' ' ; i++){
        char c = expression[i];
        if((c >= '0' && c<= '9')){
            int number = i;
            for(;expression[number] >= '0' && expression[number] <= '9'; number++ ){
                result[j++] = expression[number];
            }
            result[j++] = ' ';
            i = number - 1;
        } else if(c == '('){
            stack_push(&stack, &c);
            if(expression[i + 1] == '-'){
                result[j++] = '0';
                result[j++] = ' ';
            } else if(expression[i + 1] == ')'){
                printf("未知的表达式\n");
                return ERROR;
            }
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
            if (c == '-' && i == 0  ){
                printf("错误\n");
                return ERROR;
            }
            while (!is_empty(&stack) &&  decimal_precedence(c) <= decimal_precedence(*(stack.pTop - 1))) {
                char element;
                stack_pop(&stack, &element);
                result[j++] = element;
                result[j++] = ' ';
            }
            stack_push(&stack, &c);
        } else if (c == ' '){
            continue;

        } else if (expression[i] == '.'){
            result[--j] = '.';
            result[j++] = '.';
        } else if(expression[i] == '\n'){
            break;

        } else if(c == '!' || c == '=' || c == '>' || c == '&' || c == '<' || c == '|' ){
            while (!is_empty(&stack) &&  decimal_precedence(c) <= decimal_precedence(*(stack.pTop - 1))) {
                char element;
                stack_pop(&stack, &element);
                result[j++] = element;
                result[j++] = ' ';
            }
            if(c == '>' && expression[i+1] == '='){
                c = '}';
                ++i;
            } else if(c == '<' && expression[i+1] == '='){
                c = '{';
                ++i;
            } else if(c == '!' && expression[i+1] == '='){
                ++i;
            } else if(c == '=' && expression[i+1] == '='){
                ++i;
            } else if(c == '&' && expression[i+1] == '&'){
                ++i;
            } else if(c == '|' && expression[i+1] == '|'){
                ++i;
            }
            stack_push(&stack, &c);
        } else {
            printf("未知的表达式\n");
            return ERROR;
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
int decimal_precedence(char c) {
    if (c == '+' || c == '-')
        return 5;
    if (c == '*' || c == '/')
        return 6;
    if (c == '>' || c == '<')
        return 4;
    if (c == '!' || c == '=')
        return 3;
    if (c == '&' )
        return 2;
    if (c == '|')
        return 1;
    return 0;
}



//计算后缀表达式
Status decimal_calculate(char *result, double* finalResult) {
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
        } else if(*c == '+' || *c == '-' || *c == '*' || *c == '/' || *c == '>' || *c == '<' || *c == '|' || *c == '&' || *c == '}' || *c == '{'){
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
                case '<':
                    answer = a < b;
                    break;
                case '>':
                    answer = a > b;
                    break;
                case '{':
                    answer = a <= b;
                    break;
                case '}':
                    answer = a >= b;
                    break;
                case '&':
                    answer = a && b;
                    break;
                case '|':
                    answer = a || b;
                    break;
                case '/':
                    if(b == 0){
                        printf("错误\n");
                        return ERROR;
                    }
                    answer = a / b;
                    break;
                default:
                printf("错误\n");
                return ERROR;
            }
            push(&stack, &answer);
        } 
        
    }

    pop(&stack, finalResult);
    clear(&stack);
    myfree(&stack);
    return OK;
}