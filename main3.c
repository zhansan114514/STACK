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
//#define DEBUG_MODE 0

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
        Status h;

        if (strcmp(input, "help") == 0) {
            printf(YELLOW"+代表将两数相加\n"NONE);
            printf(YELLOW"-代表将两数相减\n"NONE);
            printf(YELLOW"*代表将两数相乘\n"NONE);
            printf(YELLOW"/代表将两数相除\n"NONE);
            printf("括号代表优先计算括号里面的内容\n");
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
            if (input[0] != '\0') {
                int i = decimal_change(input, result);
                if (i == OK) {

                    #ifdef DEBUG_MODE
                        printf("后缀表达式为:%s\n", result);
                        
                    #endif
                    
                    h = decimal_calculate(result, &answer);
                    free(input);
                    if(h != ERROR){
                    printf(RED"结果为：%g\n"NONE, answer);
                    }

                    if (option_t == 1) {
                        fprintf(output, "结果为：%g\n", answer);
                        fflush(output);
                    }
                }
            }
        } else if (mode == hex){
            if (input[0] != '\0') {
                int i = hex_change(input, result);
                if (i == OK) {

                    #ifdef DEBUG_MODE
                        printf("后缀表达式为:%s\n", result);
                        
                    #endif
                    
                    h = hex_calculate(result, &answer);
                    unsigned int finalanswer = (unsigned int)answer;
                    free(input);
                    if(h != ERROR){
                    printf(RED"结果为：%X\n"NONE, finalanswer);
                    }

                    if (option_t == 1) {
                        fprintf(output, "结果为：%X\n", finalanswer);
                        fflush(output);
                    }
                }
                    
            }
        } else if (mode == binary){
            int finalanswer;
            if (input[0] != '\0') {
                int i = binary_change(input, result);
                if (i == OK) {

                    #ifdef DEBUG_MODE
                        printf("后缀表达式为:%s\n", result);
                        
                    #endif
                    
                    h = binary_calculate(result, &answer);
                    finalanswer = binary_transform(answer);
                    free(input);
                    if(h != ERROR){
                    printf(RED"结果为：%d\n"NONE, finalanswer);
                    }

                    if (option_t == 1) {
                        fprintf(output, "结果为：%d\n", finalanswer);
                        fflush(output);
                    }
                }     
            }
        }
    }
    if (option_t == 1) {
        fclose(output);
    }

    return 0;
    
} 
