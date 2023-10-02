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

int main()
{
    int ret = system("make");
    assert(ret != -1);
    ret = system("./myprogram -t answer.txt < test1.txt");
    assert(ret != -1);
    system("diff -y -w result.txt answer.txt");
    return 0;
}