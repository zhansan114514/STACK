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

    while (1) {
        char *input = readline("请输入表达式> ");
        char result[100];
        double answer;

        if (strcmp(input, "help") == 0) {
            printf(YELLOW"+代表将两数相加\n"NONE);
            printf(YELLOW"-代表将两数相减\n"NONE);
            printf(YELLOW"*代表将两数相乘\n"NONE);
            printf(YELLOW"/代表将两数相除\n"NONE);
            printf("括号代表优先计算括号里面的内容\n");
        } else {
            if (input[0] != '\0') {
                int i = change_expression(input, result);
                if (i == OK) {
                    answer = calculate(result);
                    add_history(input);
                    free(input);
                    printf(RED"结果为：%g\n"NONE, answer);

                    if (option_t == 1) {
                        fprintf(output, "结果为：%g\n", answer);
                        fflush(output);
                    }
                } else if (i == ERROR) {
                    exit(1);
                }
            }
        }
    }

    if (option_t == 1) {
        fclose(output);
    }

    return 0;
}
