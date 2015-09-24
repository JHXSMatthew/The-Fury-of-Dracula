#include <stdio.h>
#include <stdlib.h>
#include "linkList.h"
#include <assert.h>

typedef struct node{
	Node next;
	int data;
	int total;
}node;

typedef struct list{
	Node first;
}list;


// new list

List newList(){
	List returnValue;
	returnValue = (List) malloc (sizeof(list));
    returnValue->first = NULL;
	return returnValue;
}


void setValue(List list,int index,int data){
	int i;
	Node current;
	current = list->first;
	assert(current != NULL);
	if(!index == 0){
		for (i=0; i < index;i++ ){
			assert (current ->next != NULL);
			current = current->next;
		}
	}
	current->data = data;

}


// append to first
void append(List list,int data){
	Node newNode =(Node) malloc(sizeof(node));
	newNode->data = data;
	newNode->next = list->first;
	list->first = newNode;
//    printf("LinkList -> Node append, value %d \n", newNode->data);
}


//return total amounts of elements

int totalAmont(List list){
	if(list->first ==NULL){
		return 0;
	}
	Node current = list->first;
	int i = 1;
	while(current->next != NULL){
		current=current->next;
		i++;
	}
	return i;

}

//return specific element at certain position

int getValue(List list,int index){
	assert(list->first != NULL);
	Node current = list->first;
	int i;
	for(i = 0 ; i < index ; i++){
		current = current->next;

	}
	return current->data;


}

void freeList(List list){
	Node current = list->first;
	free (list);
	Node freeTemp;
	while(current ->next != NULL){
		freeTemp = current;
		current = current->next;
 //       printf("LinkList -> Node freed, value %d ,Address %p\n", freeTemp->data , freeTemp);
		free(freeTemp);
        
	}
//	free (current);


}
/*
int checkFirstSix(List list, int data){
	if(list->first == NULL){
		return 0;
	}
	int i;
	Node current = list->first;
	for(i=0;i < 6 ; i++){
		if(current == NULL){
			return 0;
		}
		current = current->next;
		if(){

		}
	}



}
*/
