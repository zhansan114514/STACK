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

#define RED "\033[0;32;31m"
#define NONE "\033[m"
#define YELLOW "\033[1;33m"

#define DEBUG_MODE 0

int main(int argc, char *argv[]) {
    int opt;
    int option_t = 0;
    char *name = NULL; 
    FILE *output = NULL;

    while ((opt = getopt(argc, argv, "t:")) != -1 ) {
        switch (opt){
        case 't':
            name = argv[2];
        output = fopen(name, "w");
        if (output == NULL) {
            perror("无法打开输出文件");
            exit(1);
            break;
        }
        option_t = 1;
        default:
            break;
        
        }
    }

    MODE mode = decimal;

    while (1) {
        char *input = readline("请输入表达式> ");
        add_history(input);
        char result[100];
        double answer;

        if (strcmp(input, "help") == 0) {
            printf(YELLOW"+代表将两数相加\n"NONE);
            printf(YELLOW"-代表将两数相减\n"NONE);
            printf(YELLOW"*代表将两数相乘\n"NONE);
            printf(YELLOW"/代表将两数相除\n"NONE);
            printf(YELLOW"==代表将两数进行比较,两者相等输出1,两者不相等输出0\n"NONE);
            printf(YELLOW"!=代表将两数进行比较,两者不相等输出1,两者相等输出0\n"NONE);
            printf(YELLOW">=代表将两数进行比较,前者比后者大或两者相等输出1,否则输出0\n"NONE);
            printf(YELLOW"<=代表将两数进行比较,前者比后者小或两者相等输出1,否则输出0\n"NONE);
            printf(YELLOW">代表将两数进行比较,前者比后者大,否则输出0\n"NONE);
            printf(YELLOW"<代表将两数进行比较,前者比后者小,否则输出0\n"NONE);
            printf(YELLOW"&&代表将两表达式的结果进行比较,两者都成立输出1,否则输出0\n"NONE);
            printf(YELLOW"||代表将两数进行比较,两者至少有一个成立输出1,否则输出0\n"NONE);
            printf(YELLOW"括号代表优先计算括号里面的内容\n"NONE);
            printf(YELLOW"当需要使用负数的时候，需要将负数包含在括号内进行规范表示\n"NONE);
            printf(YELLOW"输入B以切换二进制模式,进行二进制计算\n"NONE);
            printf(YELLOW"输入H以切换十六进制模式,进行十六进制计算\n"NONE);
            printf(YELLOW"二进制和十六进制模式支持无符号整型的+ - * / ()运算\n"NONE);
            printf(YELLOW"二进制模式支持按位运算& | ^\n"NONE);
            printf(YELLOW"&将两个数字的每个位进行比较,只有当两个相应位都为1时,结果位才为1,否则为0\n"NONE);
            printf(YELLOW"|也是对两个数字的每个位进行比较,只要两个相应位中的任何一个位为1,结果位就为1\n"NONE);
            printf(YELLOW"^也是对两个数字的每个位进行比较,但只有当两个相应位不相同时,结果位才为1,否则为0\n"NONE);
            printf(YELLOW"该程序支持命令行参数“-t”将输出结果导入某一目标文件中\n"NONE);
        } else if(strcmp(input, "D") == 0) {
            printf("计算器切换到十进制\n");
            mode = decimal;
        } else if(strcmp(input, "B") == 0) {
            printf("计算器切换到二进制\n");
            mode = binary;
        } else if(strcmp(input, "H") == 0) {
            printf("计算器切换到十六进制\n");
            mode = hex;
        } else if (mode == decimal){
            if (input[0] != '\0' && input[0] !='\n') {
                Status i = decimal_change(input, result);
                if (i == OK) {

                    #ifdef DEBUG_MODE
                        printf("后缀表达式为:%s\n", result);
                        
                    #endif
                    
                    Status h = decimal_calculate(result, &answer);
                    if (h == OK){
                    printf(RED"结果为：%g\n"NONE, answer);
                    }

                    if (option_t == 1 && h == OK) {
                        fprintf(output, "结果为：%g\n", answer);
                        fflush(output);
                    } else if(option_t == 1 && h == ERROR) {
                        fprintf(output, "错误的表达式\n");
                        fflush(output);
                    }
                } else if(i == ERROR){
                    if(option_t == 1){
                        fprintf(output, "错误的表达式\n");
                        fflush(output);
                    }
                }
            } else {
                printf("错误的表达式\n");
                if(option_t == 1) {
                        fprintf(output, "错误的表达式\n");
                        fflush(output);
                    }
            }
            free(input);
        } else if (mode == hex){
            if (input[0] != '\0' && input[0] !='\n') {
                Status i = hex_change(input, result);
                if (i == OK) {

                    #ifdef DEBUG_MODE
                        printf("后缀表达式为:%s\n", result);
                        
                    #endif
                    
                    Status h = hex_calculate(result, &answer);
                    unsigned int finalanswer = (unsigned int)answer;
                    if(h == OK){
                    printf(RED"结果为：%X\n"NONE, finalanswer);
                    }

                    if (option_t == 1 && h == OK) {
                        fprintf(output, "结果为：%X\n", finalanswer);
                        fflush(output);
                    } else if(option_t == 1 && h == ERROR) {
                        fprintf(output, "错误的表达式\n");
                        fflush(output);
                    }
                } else if(i == ERROR){
                    if(option_t == 1){
                        fprintf(output, "错误的表达式\n");
                        fflush(output);
                    }
                }
                    
            } else {
                printf("错误的表达式\n");
                if(option_t == 1) {
                        fprintf(output, "错误的表达式\n");
                        fflush(output);
                    }
            }
            free(input);
        } else if (mode == binary){
            int finalanswer;
            if (input[0] != '\0' && input[0] !='\n') {
                Status i = binary_change(input, result);
                if (i == OK) {

                    #ifdef DEBUG_MODE
                        printf("后缀表达式为:%s\n", result);
                        
                    #endif
                    
                     Status h = binary_calculate(result, &answer);
                    finalanswer = binary_transform(answer);
                    free(input);
                    if(h == OK){
                    printf(RED"结果为：%d\n"NONE, finalanswer);
                    }

                    if (option_t == 1 && h == OK) {
                        fprintf(output, "结果为：%d\n", finalanswer);
                        fflush(output);
                    } else if(option_t == 1 && h == ERROR) {
                        fprintf(output, "错误的表达式\n");
                        fflush(output);
                    }
                } else if(i == ERROR){
                    if(option_t == 1){
                        fprintf(output, "错误的表达式\n");
                        fflush(output);
                    }
                }   
            } else {
                printf("错误的表达式\n");
                if(option_t == 1) {
                        fprintf(output, "错误的表达式\n");
                        fflush(output);
                    }
            }
            free(input);
        }
    }
    if (option_t == 1) {
        fclose(output);
    }

    return 0;
    
} 
