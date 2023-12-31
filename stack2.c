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
Status myinit(Stack2* pStack){
    pStack->pBase = (StackElem2*)malloc(sizeof(StackElem2)*4);
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
void myfree(Stack2* pStack){
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
void clear(Stack2 *pStack){
    assert(pStack);

    pStack->pTop = pStack->pBase;
}

/**
*判断栈是否为空
*/
Bool empty(Stack2* pStack){
    assert(pStack);
    
    return pStack->pTop == pStack->pBase ? TRUE: FALSE;
}
   
/**
*求栈的长度
*/
int length(Stack2 *pStack){
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
Status get_top(Stack2* pStack,StackElem2* pElem){
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
Status push(Stack2 *pStack,StackElem2* pElem){
    assert(pStack);

    if (pStack->pTop - pStack->pBase == pStack->size){
    StackElem2* newstack = (StackElem2*)realloc(pStack->pBase, 2*pStack->size*sizeof(StackElem2));
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
Status pop(Stack2* pStack,StackElem2* pElem){
    assert(pStack);

    if (empty(pStack)) {
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
Status traverse(Stack2 *pStack,Status (*visit)(StackElem2*)){
    assert(pStack);

    for (StackElem2* i = pStack->pBase ;i < pStack->pTop ; i++){
    Status result = visit(i);
    if (result != ERROR){
    return ERROR;
    }
}
    return OK;
}