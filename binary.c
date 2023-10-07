#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "stack.h"
#include <assert.h>
#include <unistd.h>
#include <math.h>
//#include "stack.c"
//#include "stack2.c"


int binary_change(char* expression, char* result){ 
    int i = 0;
    int j = 0;
    char c;
    Stack stack;
    init_stack(&stack);
    //printf("%s\n", expression);
    for (; expression[i] != '\0' || expression[i] == ' ' ; i++){
        c = expression[i];
        char str[100];
        char p[100];
        if((c >= '0' && c<= '1')){
            int cnt = 0;
            int q = 0;
            str[cnt++] = c;
            for(;expression[i] >= '0' && expression[i] <= '1'; i++ ){
                str[cnt++] = expression[i];
            }
            int cnt2 = cnt - 1;
            int sum = 0;
            cnt = 0;
            for(; cnt2 != 0; cnt++){
                q = str[cnt + 1] - '0';
                sum = sum + mypow(2, cnt2 - 1)*q;
                cnt2--;
            }
            sprintf(p, "%d", sum);
            cnt = 0;
            for(; p[cnt] != '\0'; cnt++){
                result[j++] = p[cnt];
            }
            result[j++] = ' ';
            i--;
        } else if(c == '('){
            stack_push(&stack, &c);
            if(expression[i + 1] == '-'){
                result[j++] = '0';
                result[j++] = ' ';
            } else if(expression[i + 1] == ')'){
                printf("未知的表达式\n");
                stack_clear(&stack);
                stack_free(&stack);
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
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '|' || c == '&' || c == '^') {
            if (c == '-' && i == 0  ){
                result[j++] = '0';
                result[j++] = ' ';
            }
            while (!is_empty(&stack) &&  binary_precedence(c) <= binary_precedence(*(stack.pTop - 1))) {
                char element;
                stack_pop(&stack, &element);
                result[j++] = element;
                result[j++] = ' ';
            }
            stack_push(&stack, &c);
        } else if (c == ' '){
            continue;

        } else if(expression[i] == '\n'){
            break;

        } else {
            printf("未知的表达式\n");
            stack_clear(&stack);
            stack_free(&stack);
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


//因为嫌麻烦所以编写了一个pow
int mypow(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
}


//将十进制结果转化为二进制结果
int binary_transform(double answer){
    int number = (int)answer;
    int sum = 0;
    int i;
    int base = 1;
    while(number > 0){
        i = number % 2;
        sum = sum + base*i;
        number = number/2;
        base = base*10;
    }

    return sum;
}

//计算运算符的权重
int binary_precedence(char c) {
    if (c == '+' || c == '-')
        return 4;
    if (c == '*' || c == '/')
        return 5;
    if (c == '&')
        return 3;
    if (c == '^')
        return 2;
    if (c == '|')
        return 1;
    return 0;
}


//计算后缀表达式
Status binary_calculate(char *result, double* finalResult) {
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
        } else if(*c == '+' || *c == '-' || *c == '*' || *c == '/' || *c == '&' || *c == '|' || *c == '^'){
            double b;
            pop(&stack, &b);
            unsigned int B = (unsigned int)b;
            double a;
            pop(&stack, &a);
            unsigned int A = (unsigned int)a;
            double answer;
            unsigned int ANSWER;
            switch (*c) {
                case '+':
                    ANSWER = A + B;
                    break;
                case '-':
                    ANSWER = A - B;
                    break;
                case '*':
                    ANSWER = A * B;
                    break;
                case '/':
                    if(B == 0){
                        printf("错误\n");
                        clear(&stack);
                        myfree(&stack);
                        return ERROR;
                    }
                    ANSWER = A / B;
                    break;
                case '&':
                    ANSWER = A & B;
                    break;
                case '^':
                    ANSWER = A ^ B;
                    break;
                case '|':
                    ANSWER = A | B;
                    break;
                default:
                printf("错误\n");
                clear(&stack);
                myfree(&stack);
                return OK;
            }
            answer = (double)ANSWER;
            push(&stack, &answer);
        } 
        
    }

    pop(&stack, finalResult);
    clear(&stack);
    myfree(&stack);
    return OK;
}



