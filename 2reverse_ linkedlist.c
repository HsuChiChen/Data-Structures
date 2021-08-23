#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct node{
char data;
struct node *next;
} *head = NULL;

struct node *make_node(char data){
struct node *new = (struct node *)malloc(sizeof(struct node));
new->next = NULL; new->data = data;
return new;
}

void push(char data){
struct node *new_node = make_node(data);
new_node->next = head;
head = new_node;
}

void print_list(){
struct node *cur = head;
while(cur){
printf("%c", cur->data);
cur = cur->next;
}
printf("\n");
}

void reverse_list(){
if(head == NULL || head->next == NULL)
return;
struct node *prev = NULL, *cur = head, *next;
while(cur){
next = cur->next;
cur->next = prev;
prev = cur;
cur = next;
}
head = prev;
}

void clear(){
head = NULL;
}
int main(){
	char temp[20];
	int i;
	while(scanf("%[^\n]%*c",temp)==1){
		int length = strlen(temp);
		char string[length];
		for(i=0;i<length;i++){
			string[i] = temp[i];
		}
		i = length-1;
		while(i>=0){
			push(string[i--]);
		}
		//char string[]="ok,peko";
		//int i=sizeof(string)-2;
		//printf("%d",i);
		//while(i>=0){
		//	push(string[i--]);
		//}
		printf("Given Linked list is: ");
		print_list();
	
		reverse_list();
	
		printf("Reversed Linked list is: ");
		print_list();
		clear();
		printf("\n\n");
		}
	printf("AH HA HA HA HA Kon peko Kon peko Kon peko\n");
	return 0;
}

