#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct stack_node{
	int t;
	struct stack_node *next;
}stack_node;

struct stack{
	struct stack_node *top;
	//int size;
};

typedef struct stack *Stack;

