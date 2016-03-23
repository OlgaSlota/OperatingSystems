/*
* Author: Słota Olga
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "liblist.h"


 node * create_list() {
     node * head = NULL;
     return head;
 }
 
 void destroy( node ** head){
     node * current =*head;
     while(current){
         if(current->previous)
             free(current->previous);
       
         if(!(current->next)){ //last element
            free(current);
            break;
         }   
         current = current->next;
     }
 }
 
 node * search ( node * head ,char *name, char *last){
     node * current = head;
    // while(current&&((strcmp(current->p->lastname, last)!=0)||(strcmp(current->p->name, name)!=0)))
    // {
     //    current= current->next;
    // }
    // return current;
     
     while(current)
 {
 if((strcmp(current->p->lastname, last)==0)&&(strcmp(current->p->name, name)==0))
     return current; // return the matching node.
 current=current->next; // otherwise, move on
 }
 return NULL;
}
     
     
     

 
 void insert(node ** head , person * per){
     
         node * new;
         new= (node*)malloc(sizeof(node));
         new->p = (person*)malloc(sizeof(person*));
         new->p =per;
         new->next = new->previous = NULL;
         if(*head==NULL){
             *head = new;
        }
         else {
             new->next = *head;
             (*head)->previous = new;
             *head=new;
         }
        
     
 }

 void rem(node ** head , person * per){
     node * old ;
     old = search(*head,per->name,per->lastname);
     if(old){
         if(old->next==NULL && old->previous == NULL){
             head = NULL;
         }
         else if(old->previous == NULL){
             *head = old->next;
             (*head)->previous = NULL;
         }
         else if(old->next == NULL){
             (old->previous)->next = NULL;
         }
         else{
             (old->previous)->next = old->next;
             (old->next)->previous = old->previous;
         }
         free(old);
     }
 }
 person * create_person(char *name, char * lastname , char * born , char * email, char * phone , char * address){

     person *new= (person *)malloc(sizeof(person));
   
     strcpy(new->address, address);
     strcpy(new->born, born);
     strcpy(new->lastname, lastname);
     strcpy(new->name,name);
     strcpy(new->phone,phone);
     strcpy(new->email,email);
   
      return new;
 }
 node *split( node *head)
{
     node *fast = head,*slow = head;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    node *temp = slow->next;
    slow->next = NULL;
    return temp;
}
 
 node *merge(node *first,  node *second)
{
     if (!first)
        return second;
    if (!second)
        return first;
   
    if (strcmp(first->p->lastname , second->p->lastname)<0)
    {
        first->next = merge(first->next,second);
        first->next->previous = first;
        first->previous = NULL;
        return first;
    }
     if (strcmp(first->p->lastname , second->p->lastname)>0)
    {
        second->next = merge(first,second->next);
        second->next->previous = second;
        second->previous = NULL;
        return second;
    }
     else{
        if (strcmp(first->p->name , second->p->name)<0)
    {
        first->next = merge(first->next,second);
        first->next->previous = first;
        first->previous = NULL;
        return first;
    }
       else{
            
        second->next = merge(first,second->next);
        second->next->previous = second;
        second->previous = NULL;
        return second;
         
       }
     }
}
 
// Function to do merge sort
 node *mergeSort( node *head)
{
    if (!head || !head->next)
        return head;
    node *second = split(head);
    head = mergeSort(head);
    second = mergeSort(second);
    return merge(head,second);
}

 void print_helper(char tab[] , int size){
     for( int i=0 ; i< size ; i++)
         if(tab[i]!='\0')
        printf("%c",tab[i]);
     printf(",");
 }
void print( node *head)
{
     node *temp = head;
    printf("Your list\n");
    while (temp)
    {
        printf(" [ ");
        
        print_helper(temp->p->lastname,20);
        print_helper(temp->p->name,20);
        print_helper(temp->p->born,10);
        print_helper(temp->p->email,40);
        print_helper(temp->p->phone,10);
         for( int i=0 ; i< 40 ; i++)
         if(temp->p->address[i]!='\0')
        printf("%c",(temp->p->address)[i]);
         
        printf(" ]\n");
        temp= temp->next;
    }  
}

void swap(int *A, int *B)
{
    int temp = *A;
    *A = *B;
    *B = temp;
}

