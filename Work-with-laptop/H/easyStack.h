#pragma once
#include <iostream>
#include <cstring>
#include<stdio.h>
#include<stdlib.h>

namespace easyStack{
    typedef struct data{
        int x;
    }Data;


    typedef struct element{
        Data data;
        struct element* previous;
    }Element;


    typedef struct stack{
        Element* peek;
    }Stack;


    void addStack(Stack* stack, Data data){

        Element* el = (Element*)malloc(sizeof(Element));
        el->data = data;
        el->previous = stack->peek;
        stack->peek = el;
        return;
        
    }

    Data popStack(Stack* stack){
        if (stack->peek == NULL){
            exit(1);
        }
        Data el ;
        el = stack->peek->data;
        Element* oldptr = stack->peek;
        stack->peek = stack->peek->previous;
        free(oldptr);
        return el;
    }
}
