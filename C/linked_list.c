#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int data;
	struct node *next;
}node;
void addToList(node *head , node *temp){
	if(!head){
	printf("The list is empty");
	return ;
	}
	if(!temp){
	return ;
	}
	node *ptr = head; 
	while(ptr){
		if(!ptr->next){
			ptr->next=temp; 
			break;
		}
		ptr=ptr->next ;
	}
}

void printLL(node *head){
	if(!head){
	printf("The linked list is empty");
	return ;
	}
	printf("printing out the current state of the linked list \n");
	node *ptr = head; 
	while(ptr){
		printf("(%d) -> ",ptr->data );
		if(!ptr->next){
			break; 
		}
		ptr=ptr->next ;
	}
	printf("\n");
	return ; 
}
int main(){
	node *head = (node*)malloc(sizeof(node)); 
	while(1){
		printf("Please enter an integer to inset into the linked list :\n" );
		char string[256];
		scanf( "%s" , string);
		int num=atoi(string);
		printf("%s",string);
		if(num==0){
			printf( "\x1b[31m please enter a non zero value \x1b[0m \n");
			continue; 
		}
		if(!head->data){
			head->data=num ;		
			head->next=NULL;
			printLL(head);
			continue;
		}
		printf("You entered %d, adding your node to the linked list \n",num);
		node *temp = malloc(sizeof(struct node) );  
		temp->next = NULL;   
		temp->data = num;	
		addToList(head,temp);
		printLL(head); 
	}

//	printf("Exited Linked List Program");
	printf( "\x1b[31m Exited Linked List Program \x1b[0m \n");
	return 0;
}
