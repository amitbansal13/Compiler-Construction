/* GROUP Number = 20
Name-Amit Bansal ID Number- 2016A7PS0140P
Name- Vedant Patwary ID Number-2016A7PS0031P
Name- Abhimanyu Singh Shekhawat ID Number- 2016A7PS0112P
Name- Abhilash Neog ID Number - 2016A7PS0004P*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct stack_node{
	TreeNode t;
	struct stack_node *next;
}stack_node;

struct stack{
	struct stack_node *top;
	//int size;
};

typedef struct stack *Stack;

bool isEmpty(Stack s);
Stack push(Stack s,TreeNode t);
Stack pop(Stack s);
Stack createStack();
TreeNode top(Stack s);
