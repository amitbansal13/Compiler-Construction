#include "parsetree.h"
#include "stack.h"

Stack createStack(){
	Stack s = (Stack)malloc(sizeof(struct stack));
	s->top=NULL;
	return s;
}

Stack pop(Stack s){
	if(s->top==NULL)
		return s;
	stack_node *temp = s->top;
	s->top=temp->next;
	free(temp);
	return s;
}

Stack push(Stack s,TreeNode t){
	stack_node *new_node = (stack_node*)malloc(sizeof(stack_node));
	new_node->t=t;
	new_node->next=s->top;
	s->top=new_node;	
	return s;
}

TreeNode top(Stack s){
	if(s->top==NULL)
		return NULL;
	return s->top->t;
}

bool isEmpty(Stack s){
	if(s->top==NULL)
		return true;
	return false;
}

/*
void printStack(Stack s){
	printf("printing\n");
	stack_node *temp = s->top;
	while(temp!=NULL){
		printf("%d\n",temp->t);
		temp=temp->next;
	}
}
*/
