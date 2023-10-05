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
                exit(-1);
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
                result[j++] = '0';
                result[j++] = ' ';
            }
            while (!is_empty(&stack) &&  precedence(c) <= precedence(*(stack.pTop - 1))) {
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





